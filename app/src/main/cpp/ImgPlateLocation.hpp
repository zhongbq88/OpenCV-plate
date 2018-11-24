
#ifndef ImgPlateLocation_hpp
#define ImgPlateLocation_hpp


class ImgPlateLocation {
public:
    ImgPlateLocation();

    virtual ~ImgPlateLocation();

    virtual void plateLocate(Mat src, vector<Mat> &plates) = 0;

protected:
    void safeRect(Mat src, RotatedRect &rect, Rect2f &dst_rect);

    void rotation(Mat src, Mat &dst, Size rect_size, Point2f center, double angle);

    void tortuosity(Mat src,  vector<RotatedRect> &rects, vector<Mat> &dst_plates);

    int verifySizes(RotatedRect rotated_rect);

};

#endif /* ImgPlateLocation_hpp */
