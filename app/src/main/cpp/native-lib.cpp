#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "rsa.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_rsa_1app_Conector_crypt(JNIEnv *env, jclass clazz, jstring texto) {
    char * c = (char*)env->GetStringUTFChars(texto,0);
    env->ReleaseStringUTFChars(texto,c);

    char * r = cifrarTexto(c);

    //char * d = descifrarTexto(r);
    return env->NewStringUTF(r);
}