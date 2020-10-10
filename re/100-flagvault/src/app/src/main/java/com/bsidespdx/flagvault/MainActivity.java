package com.bsidespdx.flagvault;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import org.w3c.dom.Text;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onDecrypt(View view) {
        EditText passwordView = (EditText)findViewById(R.id.vaultPasswordEntry);
        TextView resultView = (TextView)findViewById(R.id.vaultResult);
        String password = passwordView.getText().toString();
        String result = "Invalid vault password provided";
        if (VaultManager.CheckPassword(password)) {
            result = VaultManager.DecryptFlag(password);
        }

        resultView.setText(result);
    }
}