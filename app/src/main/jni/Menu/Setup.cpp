#include "Includes/obfuscate.h"
#include "Menu/Menu.hpp"
#include "Utils.hpp"
#include "Includes/Logger.h"

extern "C" {

JNIEXPORT jstring JNICALL
Java_com_android_support_Menu_Icon(JNIEnv *env, jobject thiz) {
    return Icon(env, thiz);
}

JNIEXPORT jstring JNICALL
Java_com_android_support_Menu_IconWebViewData(JNIEnv *env, jobject thiz) {
    return IconWebViewData(env, thiz);
}

JNIEXPORT jboolean JNICALL
Java_com_android_support_Menu_IsGameLibLoaded(JNIEnv *env, jobject thiz) {
    return isGameLibLoaded(env, thiz);
}

JNIEXPORT void JNICALL
Java_com_android_support_Menu_Init(JNIEnv *env, jobject thiz, jobject ctx, jobject title, jobject subtitle) {
    Init(env, thiz, ctx, title, subtitle);
}

JNIEXPORT jobjectArray JNICALL
Java_com_android_support_Menu_SettingsList(JNIEnv *env, jobject thiz) {
    return SettingsList(env, thiz);
}

JNIEXPORT jobjectArray JNICALL
Java_com_android_support_Menu_GetFeatureList(JNIEnv *env, jobject thiz) {
    return GetFeatureList(env, thiz);
}

JNIEXPORT void JNICALL
Java_com_android_support_Preferences_Changes(JNIEnv *env, jclass clazz, jobject obj,
                                             jint featNum, jstring featName, jint value,
                                             jlong Lvalue, jboolean boolean, jstring str) {
    Changes(env, clazz, obj, featNum, featName, value, Lvalue, boolean, str);
}

JNIEXPORT void JNICALL
Java_com_android_support_Main_CheckOverlayPermission(JNIEnv *env, jclass thiz, jobject ctx) {
    CheckOverlayPermission(env, thiz, ctx);
}

int RegisterMenu(JNIEnv *env) {
    jclass clazz = env->FindClass("com/android/support/Menu");
    if (!clazz) return JNI_ERR;

    JNINativeMethod methods[] = {
            {"Icon",            "()Ljava/lang/String;",                                                           reinterpret_cast<void *>(Icon)},
            {"IconWebViewData", "()Ljava/lang/String;",                                                           reinterpret_cast<void *>(IconWebViewData)},
            {"IsGameLibLoaded", "()Z",                                                                            reinterpret_cast<void *>(isGameLibLoaded)},
            {"Init",            "(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V", reinterpret_cast<void *>(Init)},
            {"SettingsList",    "()[Ljava/lang/String;",                                                          reinterpret_cast<void *>(SettingsList)},
            {"GetFeatureList",  "()[Ljava/lang/String;",                                                          reinterpret_cast<void *>(GetFeatureList)},
    };

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0) return JNI_ERR;
    return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
    jclass clazz = env->FindClass("com/android/support/Preferences");
    if (!clazz) return JNI_ERR;

    JNINativeMethod methods[] = {
            {"Changes", "(Landroid/content/Context;ILjava/lang/String;IJZLjava/lang/String;)V", reinterpret_cast<void *>(Changes)},
    };

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0) return JNI_ERR;
    return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
    jclass clazz = env->FindClass("com/android/support/Main");
    if (!clazz) return JNI_ERR;

    JNINativeMethod methods[] = {
            {"CheckOverlayPermission", "(Landroid/content/Context;)V", reinterpret_cast<void *>(CheckOverlayPermission)},
    };

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0) return JNI_ERR;
    return JNI_OK;
}

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) return JNI_ERR;

    if (RegisterMenu(env) != JNI_OK) return JNI_ERR;
    if (RegisterPreferences(env) != JNI_OK) return JNI_ERR;
    if (RegisterMain(env) != JNI_OK) return JNI_ERR;

    return JNI_VERSION_1_6;
}

}
