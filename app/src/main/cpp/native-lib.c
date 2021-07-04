#include <jni.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "rsa.h"

#define TARGET_CLASS "com/example/rsa_app/Conector"
#define TARGET_CRYPT "crypt"
#define TARGET_CRYPT_SIG "(Ljava/lang/String;)[B"

JNIEXPORT jbyteArray JNICALL android_native_aes(JNIEnv *env, jclass clazz,
                                                jbyteArray jarray) {
  generarPrimos();
  return 0;
}


static const JNINativeMethod gMethods[] = { { TARGET_CRYPT, TARGET_CRYPT_SIG,(void*) android_native_aes } };

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
  JNIEnv* env = NULL;
  if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
    return -1;
  }

  jclass clazz = (*env)->FindClass(env, TARGET_CLASS);
  if (!clazz) {
    return -1;
  }
  //这里就是关键了，把本地函数和一个java类方法关联起来。不管之前是否关联过，一律把之前的替换掉！
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