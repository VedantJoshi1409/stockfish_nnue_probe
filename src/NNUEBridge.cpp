#include "NNUEBridge.h"
#include <iostream>

#include "probe.h"
#include "bitboard.h"
#include "position.h"
#include "evaluate.h"
#include "misc.h"
#include "types.h"
#include "nnue/nnue_architecture.h"

using namespace Stockfish;

JNIEXPORT void JNICALL Java_NNUEBridge_init
(JNIEnv *env, jclass this_class, jstring workingDirectory, jstring bigNet, jstring smallNet) {

const char *dir = env->GetStringUTFChars(workingDirectory, NULL);
const char *big = env->GetStringUTFChars(bigNet, NULL);
const char *small = env->GetStringUTFChars(smallNet, NULL);

Probe::init(dir, big, small);

env->ReleaseStringUTFChars(workingDirectory, dir);
env->ReleaseStringUTFChars(bigNet, big);
env->ReleaseStringUTFChars(smallNet, small);
}

JNIEXPORT jint JNICALL Java_NNUEBridge_eval
        (JNIEnv * env, jclass this_class, jstring javaFen) {
const char *fen = env->GetStringUTFChars(javaFen, NULL);

int eval = Probe::eval(fen);

env->ReleaseStringUTFChars(javaFen, fen);

return eval;
}