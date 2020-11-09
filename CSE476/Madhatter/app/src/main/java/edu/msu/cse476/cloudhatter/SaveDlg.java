package edu.msu.cse476.cloudhatter;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.DialogFragment;

import edu.msu.cse476.cloudhatter.Cloud.Cloud;
import edu.msu.cse476.cloudhatter.Cloud.HatterService;
import edu.msu.cse476.cloudhatter.Cloud.Models.Hat;
import retrofit2.Retrofit;
import retrofit2.converter.simplexml.SimpleXmlConverterFactory;

public class SaveDlg extends DialogFragment {

    private AlertDialog dlg;

    private static final String BASE_URL = "https://facweb.cse.msu.edu/dennisp/cse476x/";

    private Retrofit retrofit = new Retrofit.Builder()
            .baseUrl(BASE_URL)
            .addConverterFactory(SimpleXmlConverterFactory.create())
            .build();

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());

        // Set the title
        builder.setTitle(R.string.save);

        LayoutInflater inflater = getActivity().getLayoutInflater();

        builder.setView(inflater.inflate(R.layout.name_dlg, null))
                .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int id) {
                        EditText editName = (EditText)dlg.findViewById(R.id.editName);
                        save(editName.getText().toString());
                    }
                })


                .setNegativeButton(android.R.string.cancel, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int id) {
                        // Cancel just closes the dialog box
                    }
                });

        dlg = builder.create();

        return dlg;
    }
    /**
     * Actually save the hatting
     * @param name name to save it under
     */
    private void save(final String name) {
        if (!(getActivity() instanceof HatterActivity)) {
            return;
        }
        final HatterActivity activity = (HatterActivity) getActivity();
        final HatterView view = (HatterView) activity.findViewById(R.id.hatterView);
        new Thread(new Runnable() {

            @Override
            public void run() {
                Cloud cloud = new Cloud();
                final boolean ok = cloud.saveToCloud(name, view);
                if(!ok) {
                    Toast.makeText(view.getContext(),
                            R.string.save_fail,
                            Toast.LENGTH_SHORT).show();

                }
            }
        }).start();
    }
}