package com.example.rsa_app;

import android.util.Base64;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;

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

    /**
     * Convertir el archivo en una cadena base64
     * @param ruta ruta del archivo
     * @return
     * @throws Exception
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
}
