//
//  common.h
//  CarPlateRecognize
//
//  Created by liuxiang on 2017/7/28.
//  Copyright © 2017年 liuxiang. All rights reserved.
//

#ifndef common_h
#define common_h

//自己训练的是144 33
//#define HEIGHT 33
//#define WIDTH 144

#define HEIGHT 36
#define WIDTH 136
#define MIN_HEIGHT 50
#define MIN_AREA 1500
#define MAX_R 3
#define MIN_H  35
#define MAX_H 77

//根据训练样本决定的
//列向量 宽
#define ANN_COLS 8
//行向量  高
#define ANN_ROWS 16



#include<android/log.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
using namespace cv;
using namespace ml;
using namespace std;

#define TAG "myDemo-jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

#include "CarPlateLocation.hpp"
#include "CarSobelPlateLocation.hpp"
#include "CarColorPlateLocation.hpp"
#include "CarPlateRecgnize.hpp"
#include "CarColorPlateMatches.hpp"

#endif /* common_h */
