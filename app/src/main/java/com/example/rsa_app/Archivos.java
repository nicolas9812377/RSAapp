package com.example.rsa_app;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;


import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class Archivos extends AppCompatActivity {
    private static final int FILE_SELECT_CODE = 0;
    TextView txtpath,textView3;
    Button btn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_archivos);
        txtpath = findViewById(R.id.txtpath);
        textView3 = findViewById(R.id.textView3);
        btn = findViewById(R.id.btna);
        Button btnbuscar = findViewById(R.id.btnBuscar);
        btnbuscar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M){
                    //Verifica permisos para Android 6.0+
                    checkExternalStoragePermission();
                }
                Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
                intent.setType("*/*");
                startActivityForResult(Intent.createChooser(intent, "Choose File"), FILE_SELECT_CODE);

            }
        });

        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    //imprimir(Conector.encodeBase64File(txtpath.getText().toString()));
                    String bs = Conector.encodeBase64File(txtpath.getText().toString());
                    String[] listap = txtpath.getText().toString().split("\\.");
                    //Conector.toFile(bs,listap[0]+" base64."+listap[1]);
                    //textView3.setText(bs);

                    String enc = Conector.crypt(bs.replaceAll("\n",""));
                    double [] metricas = Conector.memory();
                    Conector.wcsv(1,bs.length(),0,metricas[1],metricas[0]);
                    String dec = Conector.decrypt(enc);
                    metricas = Conector.memory();
                    Conector.wcsv(1,bs.length(),1,metricas[1],metricas[0]);
                    Conector.decoderBase64File(dec,listap[0]+" encriptado."+listap[1]);
                    imprimir("acabo");
                    //
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

    }
    void imprimir(String msg){ Toast.makeText(this," "+msg,Toast.LENGTH_LONG).show(); }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case FILE_SELECT_CODE:
                if (resultCode == RESULT_OK) {
                    Uri uri = data.getData();
                    String path = FileUtils.getPath(this.getBaseContext(), uri);
                    txtpath.setText(path);
                    btn.setEnabled(true);
                }
                break;
        }
        super.onActivityResult(requestCode, resultCode, data);
    }


    private void checkExternalStoragePermission() {
        int permissionCheck = ContextCompat.checkSelfPermission(
                this, Manifest.permission.WRITE_EXTERNAL_STORAGE);
        if (permissionCheck != PackageManager.PERMISSION_GRANTED) {
            Log.i("Mensaje", "No se tiene permiso para leer.");
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 225);
        } else {
            Log.i("Mensaje", "Se tiene permiso para leer!");
        }
    }
}