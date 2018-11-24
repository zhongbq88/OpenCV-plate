
#ifndef common_h
#define common_h


#define HEIGHT 36
#define WIDTH 136
#define MIN_HEIGHT 50
#define MIN_AREA 1500
#define MAX_R 3
#define MIN_H  35
#define MAX_H 77


#include<android/log.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
using namespace cv;
using namespace ml;
using namespace std;

#define TAG "ec-jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

#include "ImgPlateLocation.hpp"
#include "ImgColorPlateLocation.hpp"
#include "ImgPlateRecgnize.hpp"
#include "ImgPlateMatches.hpp"

#endif /* common_h */
