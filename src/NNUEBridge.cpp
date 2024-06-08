#include "NNUEBridge.h"
#include <iostream>

#include "probe.h"

using namespace Stockfish;

JNIEXPORT void JNICALL Java_NNUEBridge_init
(JNIEnv *env, jclass this_class, jstring bigNet, jstring smallNet) {

const char *big = env->GetStringUTFChars(bigNet, NULL);
const char *small = env->GetStringUTFChars(smallNet, NULL);

Probe::init(big, small);

env->ReleaseStringUTFChars(bigNet, big);
env->ReleaseStringUTFChars(smallNet, small);
}

JNIEXPORT jint JNICALL Java_NNUEBridge_evalFen
        (JNIEnv * env, jclass this_class, jstring javaFen) {
const char *fen = env->GetStringUTFChars(javaFen, NULL);

int eval = Probe::eval(fen);

env->ReleaseStringUTFChars(javaFen, fen);

return eval;
}

JNIEXPORT jint JNICALL Java_NNUEBridge_evalArray
        (JNIEnv * env, jclass this_class, jintArray pieceBoard, jint side, jint rule50) {
    jint *board = env->GetIntArrayElements(pieceBoard, NULL);
    bool c_side = side == 0;
    int c_rule50 = (int) rule50;

    int eval = Probe::eval((int*)board, c_side, c_rule50);

    env->ReleaseIntArrayElements(pieceBoard, board, 0);

    return eval;
}