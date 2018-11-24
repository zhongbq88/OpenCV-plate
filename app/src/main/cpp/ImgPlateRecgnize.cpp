
#include "common.h"
#include <sys/time.h>

ImgPlateRecgize::ImgPlateRecgize() {
    color_plate_location = new ImgColorPlateLocation;
}

ImgPlateRecgize::~ImgPlateRecgize() {
    if(color_plate_location){
        delete color_plate_location;
        color_plate_location = 0;
    }
}

long getCurrentTime()
{
    struct timeval xTime;
    gettimeofday(&xTime,NULL);
    return xTime.tv_sec;
}

int ImgPlateRecgize::plateRecognize(Mat src,const char* out_path,int count){
    char path[100];
    char fileName[50];
    vector< Mat > plates;
    vector< Mat > color_Plates;
    //使用颜色定位
    color_plate_location->plateLocate(src,color_Plates);
    plates.insert(plates.end(), color_Plates.begin(),color_Plates.end());
    for (auto plate:color_Plates) {
        plate.release();
    }
    //LOGI("count c:%d",plates.size());
    /*if(plates.size()==1){
        color_plate_location->plateLocate(src,color_Plates);
        plates.insert(plates.end(), color_Plates.begin(),color_Plates.end());
    }*/
    int index =0;
    int newMsg=0;
    bool colorMatched = false;
    //LOGI("count c:%d",count);
    //LOGI("test %d,%d",src.rows,src.cols);
    for (auto src :plates) {
        if(!colorMatched){
            Mat src_hsv;
            cvtColor(src, src_hsv, CV_BGR2HSV);
            //获得该行数据
            int row = 20;
            if(row>src_hsv.rows/4){
                row = src_hsv.rows/4;
            }
            //LOGI("%d,%d",src_hsv.rows,src_hsv.cols);
            uchar *p = src_hsv.ptr<uchar>(row);
            int col = src_hsv.cols/4;
            //int j = 14;
            for (int j=0; j < col; j += 3) {
                int H = int(p[j]);      // 0-180
                int S = int(p[j+ 1]);  // 0-255
                int V = int(p[j + 2]);  // 0-255
               // LOGI("H:%d,%d,%d",H,S,V);
                if (H > MIN_H && H < MAX_H) {
                    if ((S > 105 && S < 255) && (V > 95 && V < 255)) {
                        colorMatched = true;
                        index = 0;
                    }else{
                        colorMatched = false;
                    }
                }else if(S==0 && S==0 && V==255){
                    colorMatched = true;
                    index = 1;
                }
            }
            src_hsv.release();
            if(colorMatched){
                sprintf(fileName,"%ld_%d.jpg",(getCurrentTime()-newMsg),index);
                //LOGI("count:%s",fileName);
                sprintf(path,out_path,fileName);
                //LOGI("count2:%s",path);
                imwrite(path, src);
                count--;
                newMsg+=1;
                //LOGI("newMsg:%d",newMsg);
                if(count>0){
                    colorMatched = false;
                }
            }
        }
        src.release();
    }
    return newMsg;
}



