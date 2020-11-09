package edu.msu.cassett8.puzzle;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;

public class PuzzleActivity extends AppCompatActivity {

    private PuzzleView getPuzzleView() {
        return this.findViewById(R.id.puzzleView);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu_puzzle, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
//
        if(item.getItemId() == R.id.menu_shuffle) {
            getPuzzleView().getPuzzle().shuffle();
            return true;
        }
        else
        {
            return super.onOptionsItemSelected(item);
        }
    }

    @Override
    protected void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        setContentView(R.layout.activity_puzzle);

        if(bundle != null) {
            // We have saved state
            getPuzzleView().loadInstanceState(bundle);
        }

    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle bundle) {
        super.onSaveInstanceState(bundle);

        getPuzzleView().saveInstanceState(bundle);
    }
}