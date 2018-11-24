
#ifndef ImgColorPlateLocation_hpp
#define ImgColorPlateLocation_hpp

class ImgColorPlateLocation:ImgPlateLocation{
public:
    ImgColorPlateLocation();
    ~ImgColorPlateLocation();
    void plateLocate(Mat src, vector<Mat > &sobel_Plates);
};

#endif /* ImgColorPlateLocation_hpp */
