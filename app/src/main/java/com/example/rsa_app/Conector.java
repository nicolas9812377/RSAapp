package com.example.rsa_app;

public class Conector {
    static {
        try {
            System.loadLibrary("native-lib");
        } catch (Throwable e) {
            e.printStackTrace();
        }
    }

    public native static String crypt(String txt);
}
