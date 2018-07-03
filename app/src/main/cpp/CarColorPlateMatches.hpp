//
//  CarColorPlateLocation.hpp
//  CarPlateRecognize
//
//  Created by liuxiang on 2017/7/30.
//  Copyright © 2017年 liuxiang. All rights reserved.
//

#ifndef CarColorPlateMatches_hpp
#define CarColorPlateMatches_hpp

class CarColorPlateMatches{
public:
    CarColorPlateMatches();
    ~CarColorPlateMatches();
    int matches(Mat src,Mat dst);
};

#endif /* CarColorPlateMatches_hpp */
