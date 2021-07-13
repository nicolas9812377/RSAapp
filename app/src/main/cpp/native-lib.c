#include <jni.h>
#include "rsa.h"
#include <string.h>
#include <stdlib.h>

JNIEXPORT jstring JNICALL
Java_com_example_rsa_1app_Conector_crypt(JNIEnv *env, jclass clazz, jstring texto) {
    char * g = (char*) (*env)->GetStringUTFChars(env,texto,NULL);

    size_t tam  = strlen(g);
    char* buff = (char*) malloc(tam);
    (*env)->ReleaseStringUTFChars(env,texto,g);
    memset(buff, 0, tam);

    cifrarTexto(g,buff);
    return (*env)->NewStringUTF(env,buff);
}

JNIEXPORT jstring JNICALL
Java_com_example_rsa_1app_Conector_decrypt(JNIEnv *env, jclass clazz, jstring texto) {
    char * g = (char*) (*env)->GetStringUTFChars(env,texto,NULL);

    size_t tam  = strlen(g);
    char* buff = (char*) malloc(tam);
    (*env)->ReleaseStringUTFChars(env,texto,g);
    memset(buff, 0, tam);

    descifrarTexto(g,buff);
    return (*env)->NewStringUTF(env,buff);
}