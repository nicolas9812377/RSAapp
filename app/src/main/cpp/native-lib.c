#include <jni.h>
#include "rsa.h"
#include <string.h>
#include <stdlib.h>
#include "memcount.h"
#include <time.h>
double tiempo;
double memoria;
JNIEXPORT jstring JNICALL
Java_com_example_rsa_1app_Conector_crypt(JNIEnv *env, jclass clazz, jstring texto) {
    char * g = (char*) (*env)->GetStringUTFChars(env,texto,NULL);

    size_t tam  = strlen(g);
    char* buff = (char*) malloc(tam);
//    (*env)->ReleaseStringUTFChars(env,texto,g);
    memset(buff, 0, tam);
    clock_t t;
    t=clock();
    cifrarTexto(g,buff);
    t=clock() - t;
    memoria = mem_total();
    tiempo = ((float)t/CLOCKS_PER_SEC);
    return (*env)->NewStringUTF(env,buff);
}

JNIEXPORT jstring JNICALL
Java_com_example_rsa_1app_Conector_decrypt(JNIEnv *env, jclass clazz, jstring texto) {
    char * g = (char*) (*env)->GetStringUTFChars(env,texto,NULL);

    size_t tam  = strlen(g);
    char* buff = (char*) malloc(tam);
    (*env)->ReleaseStringUTFChars(env,texto,g);
    memset(buff, 0, tam);
    clock_t t;
    t=clock();
    descifrarTexto(g,buff);
    t=clock() - t;
    memoria = mem_total();
    tiempo = ((float)t/CLOCKS_PER_SEC);
    return (*env)->NewStringUTF(env,buff);
}

JNIEXPORT jdoubleArray JNICALL
Java_com_example_rsa_1app_Conector_memory(JNIEnv *env, jclass clazz) {
    jdouble resp[] = {memoria,tiempo};
    jdoubleArray outJNIArray = (*env)->NewDoubleArray(env, 2);
    (*env)->SetDoubleArrayRegion(env, outJNIArray, 0 , 2, resp);
    return  outJNIArray;
}
