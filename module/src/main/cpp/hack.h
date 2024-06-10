#ifndef HACK_H
#define HACK_H
#include <jni.h>
#include <android/log.h>

static int   enable_hack;
int.         isGame(JNIEnv *env, jstring appDataDir);
static char  *game_data_dir = NULL;
void         *hack_thread(void *arg);

#define LOG_TAG "MODTAG"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#define HOOKAF(ret, func, ...) \
    ret (*orig##func)(__VA_ARGS__); \
    ret my##func(__VA_ARGS__)

#endif // HACK_H
