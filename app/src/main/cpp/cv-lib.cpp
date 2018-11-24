#include "common.h"
#include <jni.h>
#include <android/log.h>
#include <android/bitmap.h>


extern "C" {

ImgPlateRecgize *imgPlateRecgize = 0;
ImgPlateMatches *matches = 0;

void bitmap2Mat(JNIEnv *env, jobject bitmap, Mat &dst) {
    AndroidBitmapInfo info;
    void *pixels = 0;
    //获得bitmap信息
    CV_Assert(AndroidBitmap_getInfo(env, bitmap, &info) >= 0);
    //必须是 rgba8888 rgb565
    CV_Assert(info.format == ANDROID_BITMAP_FORMAT_RGBA_8888);
    //lock 获得数据
    CV_Assert(AndroidBitmap_lockPixels(env, bitmap, &pixels) >= 0);
    CV_Assert(pixels);
    dst.create(info.height, info.width, CV_8UC3);
    //LOGI("bitmap2Mat: RGBA_8888 bitmap -> Mat");
    Mat tmp(info.height, info.width, CV_8UC4, pixels);
    cvtColor(tmp, dst, COLOR_RGBA2BGR);
    // cvtColor(dst, dst, COLOR_RGBA2RGB);
    tmp.release();
    AndroidBitmap_unlockPixels(env, bitmap);
}


void mat2Bitmap(JNIEnv *env, Mat &src, jobject bitmap) {
    AndroidBitmapInfo info;
    void *pixels = 0;
    LOGI("nMatToBitmap");
    CV_Assert(AndroidBitmap_getInfo(env, bitmap, &info) >= 0);
    /*CV_Assert(info.format == ANDROID_BITMAP_FORMAT_RGBA_8888);
    CV_Assert(src.dims == 2 && info.height == (uint32_t) src.rows &&
              info.width == (uint32_t) src.cols);
    CV_Assert(src.type() == CV_8UC1 || src.type() == CV_8UC3 || src.type() == CV_8UC4);*/
    CV_Assert(AndroidBitmap_lockPixels(env, bitmap, &pixels) >= 0);
    CV_Assert(pixels);
    Mat tmp(info.height, info.width, CV_8UC4, pixels);
    if (src.type() == CV_8UC1) {
        LOGI("nMatToBitmap: CV_8UC1 -> RGBA_8888");
        cvtColor(src, tmp, COLOR_GRAY2RGBA);
    } else if (src.type() == CV_8UC3) {
        LOGI("nMatToBitmap: CV_8UC3 -> RGBA_8888");
        cvtColor(src, tmp, COLOR_BGR2RGBA);
    } else if (src.type() == CV_8UC4) {
        LOGI("nMatToBitmap: CV_8UC4 -> RGBA_8888");
        src.copyTo(tmp);
    }
    AndroidBitmap_unlockPixels(env, bitmap);
    return;

}

JNIEXPORT void JNICALL
Java_com_zbq_opencv_CVUtil_init(JNIEnv *env, jobject instance) {

    imgPlateRecgize = new ImgPlateRecgize();
    matches = new ImgPlateMatches();
}

JNIEXPORT void JNICALL
Java_com_zbq_opencv_CVUtil_release(JNIEnv *env, jobject instance) {
    if (imgPlateRecgize)
        delete imgPlateRecgize;
}

JNIEXPORT jint JNICALL
Java_com_zbq_opencv_CVUtil_imgPlate(JNIEnv *env, jobject instance, jstring inPath, jstring outPath, jint count) {
    const char *path = env->GetStringUTFChars(outPath, 0);
    const char *in = env->GetStringUTFChars(inPath, 0);
    Mat src = imread(in,COLOR_RGBA2BGR);
   // bitmap2Mat(env, bitmap, src);
    if(!imgPlateRecgize){
        imgPlateRecgize = new ImgPlateRecgize();
    }
    int ret = -1;
    try{
        ret = imgPlateRecgize->plateRecognize(src,path,count);
    }catch(exception &err){
    }
    jthrowable err = env->ExceptionOccurred();
    if (err != NULL){
        env->ExceptionClear();
        ret = -1;
    }
    src.release();
    env->ReleaseStringUTFChars(outPath, path);
    env->ReleaseStringUTFChars(inPath, in);
    return ret;
}

JNIEXPORT jdouble JNICALL
Java_com_zbq_opencv_CVUtil_matches(JNIEnv *env, jobject instance,
                                                      jobject bitmap, jobject out) {
    Mat src;
    Mat dst;
    bitmap2Mat(env, bitmap, src);
    bitmap2Mat(env, out, dst);
    if(!matches){
        matches = new ImgPlateMatches();
    }
    double ret = 0;
    try{
        ret = matches->matches(src, dst);
    }catch(exception &err){
    }
    jthrowable err = env->ExceptionOccurred();
    if (err != NULL){
        env->ExceptionClear();
        return 0;
    }
    src.release();
    dst.release();
    return ret;
}

JNIEXPORT jstring JNICALL
Java_com_zbq_opencv_CVUtil_bitwiseNot(JNIEnv *env, jobject instance, jobject bitmap, jstring outPath) {
    const char *path = env->GetStringUTFChars(outPath, 0);
    Mat src;
    Mat dst;
    bitmap2Mat(env, bitmap, src);
    bitwise_not(src, dst, noArray());
    imwrite(path, dst);
    src.release();
    dst.release();
    jthrowable err = env->ExceptionOccurred();
    if (err != NULL){
        env->ExceptionClear();
        return outPath;
    }
    return env->NewStringUTF(path);
}

}