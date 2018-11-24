//
//  CarColorPlateLocation.hpp
//  CarPlateRecognize
//
//  Created by liuxiang on 2017/7/30.
//  Copyright © 2017年 liuxiang. All rights reserved.
//

#ifndef ImgPlateMatches_hpp
#define ImgPlateMatches_hpp

class ImgPlateMatches{
public:
    ImgPlateMatches();
    ~ImgPlateMatches();
    double matches(Mat src,Mat dst);
};

#endif /* ImgPlateMatches_hpp */
