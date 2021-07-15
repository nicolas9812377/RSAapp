package com.example.rsa_app;

import android.util.Base64;
import android.util.Log;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Conector {
    static {
        try {
            System.loadLibrary("native-lib");
        } catch (Throwable e) {
            e.printStackTrace();
        }
    }

    public native static String crypt(String txt);
    public native static String decrypt(String txt);
    public native static double[] memory();

    /**
     * Convertir el archivo en una cadena base64
     * param ruta del archivo
     * return
     * throws Exception
     */
    public static String encodeBase64File(String path) throws Exception {
        File file = new File(path);
        FileInputStream inputFile = new FileInputStream(file);
        byte[] buffer = new byte[(int)file.length()];
        inputFile.read(buffer);
        inputFile.close();
        return Base64.encodeToString(buffer,Base64.DEFAULT);
    }
    /**
     * Guarde el archivo con decodificación de caracteres base64
     * @param base64Code
     * @param targetPath
     * @throws Exception
     */
    public static void decoderBase64File(String base64Code,String targetPath) throws Exception {
        byte[] buffer = Base64.decode(base64Code,Base64.DEFAULT);
        FileOutputStream out = new FileOutputStream(targetPath);
        out.write(buffer);
        out.close();

    }
    /**
     * Guarde los caracteres base64 en un archivo de texto
     * @param base64Code
     * @param targetPath
     * @throws Exception
     */
    public static void toFile(String base64Code,String targetPath) throws Exception {
        byte[] buffer = base64Code.getBytes();
        FileOutputStream out = new FileOutputStream(targetPath);
        out.write(buffer);
        out.close();
    }
    public static String nombre = "";
    //Runtime r=Runtime.getRuntime();
    public static void wcsv(int id,long tamArch,int ende, double tiempo, double memoria ){
        File file = new File("/storage/emulated/0/Download/datos-"+((id == 0)?"texto":"archivos")+".csv");

        try {
            // if file doesnt exists, then create it
            if (!file.exists()) {
                file.createNewFile();
            }

            FileWriter fw = new FileWriter(file.getAbsoluteFile(),true);
            BufferedWriter bw = new BufferedWriter(fw);
            bw.write(nombre+","+tamArch+","+ ende+","+tiempo+","+memoria);
            bw.newLine();
            bw.close();

        } catch (IOException e) {
            //new Texto().imprimir(e.getMessage()+"");
            e.printStackTrace();
        }

    }

    public static float leer(int id, int col, int keysize, int ende){
        File file = new File("/storage/emulated/0/Download/datos-"+((id == 0)?"texto":"archivos")+".csv");
        int cont = 0;
        try
        {
            BufferedReader fin = new BufferedReader(new FileReader(file.getAbsoluteFile()));
            String line = fin.readLine();
            float acum = 0;
            while (line != null){
                String[] linea = line.split(",");
                if (keysize == Integer.parseInt(linea[3]) && ende == Integer.parseInt(linea[2])) {
                    acum += Float.parseFloat(linea[col]);
                    cont++;
                }
                line = fin.readLine();
            }

            fin.close();
            return (cont != 0)?acum/cont:0;
        }
        catch (Exception ex)
        {
            Log.e("Ficheros", "Error al leer fichero desde memoria interna "+ ex.getMessage());
        }
        return -1;
    }
}
