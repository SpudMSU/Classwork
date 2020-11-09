package edu.msu.cse476.cloudhatter;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.widget.Toast;

import androidx.fragment.app.DialogFragment;

import edu.msu.cse476.cloudhatter.Cloud.Cloud;
import edu.msu.cse476.cloudhatter.Cloud.Models.Hat;

public class DeletingDlg  extends DialogFragment  {

    private final static String ID = "id";
    private String name;
    /**
     * Id for the image we are loading
     */
    private String catId;

    /**
     * Set true if we want to cancel
     */
    private volatile boolean cancel = false;


    /**
     * Save the instance state
     */
    @Override
    public void onSaveInstanceState(Bundle bundle) {
        super.onSaveInstanceState(bundle);

        bundle.putString(ID, catId);
    }

    /**
     * Create the dialog box
     */
    @Override
    public Dialog onCreateDialog(Bundle bundle) {

        if(bundle != null) {
            catId = bundle.getString(ID);
        }

        cancel = false;

        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());

        // Set the title
        builder.setTitle(R.string.deleting);

        String areYouSure = getString(R.string.sure) + " " + name + "?";
        builder.setMessage(areYouSure);

        builder.setNegativeButton(android.R.string.cancel,
                new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int id) {
                        cancel = true;
                    }
                });


        builder.setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {

                delete();
            }
        });


        // Create the dialog box
        final AlertDialog dlg = builder.create();

        // Get a reference to the view we are going to load into
        final HatterView view = (HatterView)getActivity().findViewById(R.id.hatterView);

        return dlg;
    }


    public String getCatId() {
        return catId;
    }

    public void setCatId(String catId) {
        this.catId = catId;
    }


    public void setName(String name) {
        this.name = name;
    }

    public void delete()
    {
        if (!(getActivity() instanceof HatterActivity)) {
            return;
        }
        final HatterActivity activity = (HatterActivity) getActivity();
        final HatterView view = (HatterView) activity.findViewById(R.id.hatterView);
        new Thread(new Runnable() {

            @Override
            public void run() {
                // Create a cloud object and get the XML
                Cloud cloud = new Cloud();
                final boolean ok = cloud.deleteFromCloud(catId);
                if(ok)
                {
                    return;
                }
            }
        }).start();
    }
}
