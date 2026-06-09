#include "Includes/obfuscate.h"
#include "Menu/Menu.hpp"
#include "Utils.hpp"
#include "Includes/Logger.h"

// Fallback JNI exports for static registration
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
}

int RegisterMenu(JNIEnv *env) {
    const char* menuClassName = OBFUSCATE("com/android/support/Menu");
    jclass clazz = env->FindClass(menuClassName);
    if (!clazz) {
        LOGE("Can't find Menu class");
        return JNI_ERR;
    }

    const char* iconName = OBFUSCATE("Icon");
    const char* iconSig = OBFUSCATE("()Ljava/lang/String;");
    const char* iconWebName = OBFUSCATE("IconWebViewData");
    const char* iconWebSig = OBFUSCATE("()Ljava/lang/String;");
    const char* isLoadedName = OBFUSCATE("IsGameLibLoaded");
    const char* isLoadedSig = OBFUSCATE("()Z");
    const char* initName = OBFUSCATE("Init");
    const char* initSig = OBFUSCATE("(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V");
    const char* settingsName = OBFUSCATE("SettingsList");
    const char* settingsSig = OBFUSCATE("()[Ljava/lang/String;");
    const char* featuresName = OBFUSCATE("GetFeatureList");
    const char* featuresSig = OBFUSCATE("()[Ljava/lang/String;");

    JNINativeMethod methods[] = {
            {iconName,    iconSig,    reinterpret_cast<void *>(Icon)},
            {iconWebName, iconWebSig, reinterpret_cast<void *>(IconWebViewData)},
            {isLoadedName, isLoadedSig, reinterpret_cast<void *>(isGameLibLoaded)},
            {initName,    initSig,    reinterpret_cast<void *>(Init)},
            {settingsName, settingsSig, reinterpret_cast<void *>(SettingsList)},
            {featuresName, featuresSig, reinterpret_cast<void *>(GetFeatureList)},
    };

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0) {
        LOGE("Can't register Menu natives");
        return JNI_ERR;
    }
    return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
    const char* prefsClassName = OBFUSCATE("com/android/support/Preferences");
    jclass clazz = env->FindClass(prefsClassName);
    if (!clazz) {
        LOGE("Can't find Preferences class");
        return JNI_ERR;
    }

    const char* changesName = OBFUSCATE("Changes");
    const char* changesSig = OBFUSCATE("(Landroid/content/Context;ILjava/lang/String;IJZLjava/lang/String;)V");

    JNINativeMethod methods[] = {
            {changesName, changesSig, reinterpret_cast<void *>(Changes)},
    };

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0) {
        LOGE("Can't register Preferences natives");
        return JNI_ERR;
    }
    return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
    const char* mainClassName = OBFUSCATE("com/android/support/Main");
    jclass clazz = env->FindClass(mainClassName);
    if (!clazz) {
        LOGE("Can't find Main class");
        return JNI_ERR;
    }

    const char* checkPermName = OBFUSCATE("CheckOverlayPermission");
    const char* checkPermSig = OBFUSCATE("(Landroid/content/Context;)V");

    JNINativeMethod methods[] = {
            {checkPermName, checkPermSig, reinterpret_cast<void *>(CheckOverlayPermission)},
    };

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0) {
        LOGE("Can't register Main natives");
        return JNI_ERR;
    }

    return JNI_OK;
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    if (RegisterMenu(env) != JNI_OK) return JNI_ERR;
    if (env->ExceptionCheck()) { env->ExceptionDescribe(); env->ExceptionClear(); }

    if (RegisterPreferences(env) != JNI_OK) return JNI_ERR;
    if (env->ExceptionCheck()) { env->ExceptionDescribe(); env->ExceptionClear(); }

    if (RegisterMain(env) != JNI_OK) return JNI_ERR;
    if (env->ExceptionCheck()) { env->ExceptionDescribe(); env->ExceptionClear(); }

    return JNI_VERSION_1_6;
}
