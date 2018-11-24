

#ifndef ImgPlateRecgnize_hpp
#define ImgPlateRecgnize_hpp

//typedef void (*svmCallback)(const cv::Mat& image, cv::Mat& features);

class ImgPlateRecgize {
public:
    ImgPlateRecgize();

    ~ImgPlateRecgize();

    int plateRecognize(Mat src,const char* out_path,int count);
private:
    ImgColorPlateLocation *color_plate_location;
};

#endif /* ImgPlateRecgnize_hpp */
