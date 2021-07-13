package com.example.rsa_app;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class Texto extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_texto);

        EditText txttexto = findViewById(R.id.txttexto);
        EditText txtencr = findViewById(R.id.txtencr);
        EditText txtdes = findViewById(R.id.txtdes);

        Button btn = findViewById(R.id.button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String cryptado = Conector.crypt(txttexto.getText().toString());
                txtencr.setText(cryptado);
                txtdes.setText(Conector.decrypt(cryptado));
            }
        });

        txttexto.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                if(txttexto.getText().length() == 0){
                    btn.setEnabled(false);
                }else {
                    btn.setEnabled(true);
                }
            }
        });

    }
}