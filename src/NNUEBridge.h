/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class NNUEBridge */

#ifndef _Included_NNUEBridge
#define _Included_NNUEBridge
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     NNUEBridge
 * Method:    init
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_NNUEBridge_init
  (JNIEnv *, jclass, jstring, jstring);

/*
 * Class:     NNUEBridge
 * Method:    evalFen
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_NNUEBridge_evalFen
  (JNIEnv *, jclass, jstring);

/*
 * Class:     NNUEBridge
 * Method:    evalArray
 * Signature: ([III)I
 */
JNIEXPORT jint JNICALL Java_NNUEBridge_evalArray
  (JNIEnv *, jclass, jintArray, jint, jint);

#ifdef __cplusplus
}
#endif
#endif
