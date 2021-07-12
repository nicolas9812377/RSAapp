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

/*
#include <jni.h>
#include <string.h>
#include <stdlib.h>
#include "rsa.h"

#define TARGET_CLASS "com/example/rsa_app/Conector"
#define TARGET_CRYPT "crypt"
#define TARGET_CRYPT_SIG "(Ljava/lang/String;)Ljava/lang/String;"

JNIEXPORT jstring JNICALL android_native_aes(JNIEnv *env, jclass clazz,
                                                jstring texto) {
    char * g = (char*) (*env)->GetStringUTFChars(env,texto,NULL);


    char * buff = (char*) malloc(1024);
    memset(buff, 0, 1024);

    (*env)->ReleaseStringUTFChars(env,texto,g);

    cifrarTexto(g,buff);
    jstring resp = (*env)->NewStringUTF(env,buff);

    free(g);
    free(buff);
    return resp;

}


static const JNINativeMethod gMethods[] = { { TARGET_CRYPT, TARGET_CRYPT_SIG, android_native_aes } };

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }

    jclass clazz = (*env)->FindClass(env, TARGET_CLASS);
    if (!clazz) {
        return -1;
    }

    if ((*env)->RegisterNatives(env, clazz, gMethods,
                                sizeof(gMethods) / sizeof(gMethods[0])) != JNI_OK) {
        return -1;
    }

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return;
    }
}
 */