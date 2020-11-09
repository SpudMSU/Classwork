package edu.msu.cse476.cloudhatter.Cloud;

import android.util.Log;
import android.util.Xml;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;
import android.widget.Toast;

import org.xmlpull.v1.XmlSerializer;

import java.io.IOException;
import java.io.StringWriter;
import java.util.ArrayList;

import edu.msu.cse476.cloudhatter.Cloud.Models.Catalog;
import edu.msu.cse476.cloudhatter.Cloud.Models.DeleteResult;
import edu.msu.cse476.cloudhatter.Cloud.Models.Hat;
import edu.msu.cse476.cloudhatter.Cloud.Models.Item;
import edu.msu.cse476.cloudhatter.Cloud.Models.LoadResult;
import edu.msu.cse476.cloudhatter.Cloud.Models.SaveResult;
import edu.msu.cse476.cloudhatter.HatterView;
import edu.msu.cse476.cloudhatter.R;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.simplexml.SimpleXmlConverterFactory;
import retrofit2.http.DELETE;

@SuppressWarnings("deprecation")
public class Cloud {
    private static final String MAGIC = "NechAtHa6RuzeR8x";
    private static final String USER = "cassett8";
    private static final String PASSWORD = "@SuperSpud69";
    private static final String BASE_URL = "https://facweb.cse.msu.edu/dennisp/cse476x/";
    public static final String CATALOG_PATH = "hatter-cat.php";
    public static final String SAVE_PATH = "hatter-save.php";
    public static final String DELETE_PATH = "hatter-delete.php";
    public static final String LOAD_PATH = "hatter-load.php";
    private static final String UTF8 = "UTF-8";

    private Retrofit retrofit = new Retrofit.Builder()
            .baseUrl(BASE_URL)
            .addConverterFactory(SimpleXmlConverterFactory.create())
            .build();


    /**
     * Save a hatting to the cloud.
     * This should be run in a thread.
     * @param name name to save under
     * @param view view we are getting the data from
     * @return true if successful
     */
    public boolean saveToCloud(String name, HatterView view) {
        name = name.trim();
        if(name.length() == 0) {
            return false;
        }

        // Create an XML packet with the information about the current image
        XmlSerializer xml = Xml.newSerializer();
        StringWriter writer = new StringWriter();

        try {
            xml.setOutput(writer);

            xml.startDocument("UTF-8", true);

            xml.startTag(null, "hatter");
            xml.attribute(null, "user", USER);
            xml.attribute(null, "pw", PASSWORD);
            xml.attribute(null, "magic", MAGIC);

            view.saveXml(name, xml);

            xml.endTag(null, "hatter");

            xml.endDocument();

        } catch (IOException e) {
            // This won't occur when writing to a string
            return false;
        }

        HatterService service = retrofit.create(HatterService.class);
        final String xmlStr = writer.toString();
        try {
            SaveResult result = service.saveHat(xmlStr).execute().body();
            if (result.getStatus() != null && result.getStatus().equals("yes")) {
                return true;
            }
            Log.e("SaveToCloud", "Failed to save, message = '" + result.getMessage() + "'");
            return false;
        } catch (IOException e) {
            Log.e("SaveToCloud", "Exception occurred while trying to save hat!", e);
            return false;
        }
    }

    public Hat openFromCloud(final String id) {
        HatterService service = retrofit.create(HatterService.class);
        try {
            Response<LoadResult> response = service.loadHat(USER, MAGIC, PASSWORD, id).execute();

            // check if request failed
            if (!response.isSuccessful()) {
                Log.e("OpenFromCloud", "Failed to load hat, response code is = " + response.code());
                return null;
            }

            LoadResult result = response.body();
            if (result.getStatus().equals("yes")) {
                return result.getHat();
            }

            Log.e("OpenFromCloud", "Failed to load hat, message is = '" + result.getMessage() + "'");
            return null;
        } catch (IOException e) {
            Log.e("OpenFromCloud", "Exception occurred while loading hat!", e);
            return null;
        }
    }

    public boolean deleteFromCloud(final String id) {
        HatterService service = retrofit.create(HatterService.class);
        try {
            Response<DeleteResult> response = service.deleteHat(USER, MAGIC, PASSWORD, id).execute();

            if (!response.isSuccessful()) {
                Log.e("DeleteFromCloud", "Failed to delete hat, response code is = " + response.code());
                return false;
            }

            DeleteResult result = response.body();
            if (result.getStatus().equals("yes")) {
                return false;
            }

            Log.e("OpenFromCloud", "Failed to delete hat, message is = '" + result.getMessage() + "'");
            return true;
        } catch (IOException e) {
            Log.e("OpenFromCloud", "Exception occurred while deleting hat!", e);
            return false;
        }
    }

    /**
     * An adapter so that list boxes can display a list of filenames from
     * the cloud server.
     */
    public static class CatalogAdapter extends BaseAdapter {

        /**
         * The items we display in the list box. Initially this is
         * null until we get items from the server.
         */

        private Catalog catalog = new Catalog("", new ArrayList(), "");


        private Retrofit retrofit = new Retrofit.Builder()
                .baseUrl(BASE_URL)
                .addConverterFactory(SimpleXmlConverterFactory.create())
                .build();

        // Create a GET query
        public Catalog getCatalog() throws IOException {
            HatterService service = retrofit.create(HatterService.class);
            return service.getCatalog(USER, MAGIC, PASSWORD).execute().body();
        }

        /**
         * Open a connection to a hatting in the cloud.
         * @param id id for the hatting
         * @return reference to an input stream or null if this fails
         */




        /**
         * Constructor
         */
        public CatalogAdapter(final View view) {
            // Create a thread to load the catalog
            new Thread(new Runnable() {

                @Override
                public void run() {
                    try {
                        catalog = getCatalog();

                        if (catalog.getStatus().equals("no")) {
                            String msg = "Loading catalog returned status 'no'! Message is = '" + catalog.getMessage() + "'";
                            throw new Exception(msg);
                        }

                        view.post(new Runnable() {

                            @Override
                            public void run() {
                                // Tell the adapter the data set has been changed
                                notifyDataSetChanged();
                            }

                        });
                    } catch (Exception e) {
                        // Error condition! Somethign went wrong
                        Log.e("CatalogAdapter", "Something went wrong when loading the catalog", e);
                        view.post(new Runnable() {
                            @Override
                            public void run() {
                                Toast.makeText(view.getContext(), R.string.catalog_fail, Toast.LENGTH_SHORT).show();
                            }
                        });
                    }
                }
            }).start();
        }

        @Override
        public int getCount() {
            return catalog.getItems().size();
        }

        public String getId(int pos)
        {
            return getItem(pos).getId();
        }
        @Override
        public Item getItem(int position) {
            return catalog.getItems().get(position);
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        @Override
        public View getView(int position, View view, ViewGroup parent) {
            if(view == null) {
                view = LayoutInflater.from(parent.getContext()).inflate(R.layout.catalog_item, parent, false);
            }

            TextView tv = (TextView)view.findViewById(R.id.textItem);
            tv.setText(catalog.getItems().get(position).getName());

            return view;
        }

    }
}
