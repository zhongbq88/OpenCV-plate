
#include "common.h"
const float inlier_threshold = 2.5f; // Distance threshold to identify inliers
const float nn_match_ratio = 0.8f;   // Nearest neighbor matching ratio
const float homography = 1.8f;

ImgPlateMatches::ImgPlateMatches(){
    
}

ImgPlateMatches::~ImgPlateMatches(){
    
}

double ImgPlateMatches::matches(Mat img1,Mat img2){

    //-- 初始化
    vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptors_1, descriptors_2;
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    Ptr<DescriptorMatcher> matcher  = DescriptorMatcher::create ( "BruteForce-Hamming" );

    //-- 第一步:检测 Oriented FAST 角点位置
    detector->detect ( img1,keypoints_1 );
    detector->detect ( img2,keypoints_2 );

    //-- 第二步:根据角点位置计算 BRIEF 描述子
    descriptor->compute ( img1, keypoints_1, descriptors_1 );
    descriptor->compute ( img2, keypoints_2, descriptors_2 );
   /* if(descriptors_1.type == descriptors_2.type &&
            descriptors_1.cols == descriptors_2.cols){

    }*/
    Mat outimg1;
    drawKeypoints( img1, keypoints_1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
    outimg1.release();

    //-- 第三步:对两幅图像中的BRIEF描述子进行匹配，使用 Hamming 距离
    vector<DMatch> matches;
    matcher->match ( descriptors_1, descriptors_2, matches );

    /*//-- 第四步:匹配点对筛选
    double min_dist=10000, max_dist=0;

    //找出所有匹配之间的最小距离和最大距离, 即是最相似的和最不相似的两组点之间的距离
    for ( int i = 0; i < descriptors_1.rows; i++ )
    {
        double dist = matches[i].distance;
        if ( dist < min_dist ) min_dist = dist;
        if ( dist > max_dist ) max_dist = dist;
    }*/

    double max_y = 0;
    double min_y = 0;
    for ( int i = 0; i < keypoints_1.size(); i++ )
    {
        if(max_y==0){
            min_y =max_y = keypoints_1[i].pt.y;
        }else{
            if(keypoints_1[i].pt.y>max_y){
                max_y = keypoints_1[i].pt.y;
            }else if(keypoints_1[i].pt.y<min_y){
                min_y = keypoints_1[i].pt.y;
            }
        }
    }
    //LOGI("keypoints_1 max_y %f,%f,%f",max_y,min_y,min_y/max_y);
    double distance1_y = max_y-min_y;
    for ( int i = 0; i < keypoints_2.size(); i++ )
    {
        if(max_y==0){
            min_y =max_y = keypoints_2[i].pt.y;
        }else{
            if(keypoints_2[i].pt.y>max_y){
                max_y = keypoints_2[i].pt.y;
            }else if(keypoints_2[i].pt.y<min_y){
                min_y = keypoints_2[i].pt.y;
            }
        }
    }
    double distance2_y = max_y-min_y;
    //LOGI("keypoints_2  max_y %f,%f,%f",max_y,min_y,min_y/max_y);
    double match = 0;
    if(distance2_y>distance1_y){
        match = distance1_y/distance2_y;
    }else{
        match = distance2_y/distance1_y;
    }
   // LOGI("match 1:                      \t%f", match);
    if(match<0.4){
        return match;
    }

    //-- 第五步:绘制匹配结果
   /* Mat img_match;
    //Mat img_goodmatch;
    drawMatches ( img1, keypoints_1, img2, keypoints_2, matches, img_match );
    imwrite("/sdcard/test100.jpg", img_match);
    img_match.release();*/
    double match2 = keypoints_1.size() * 1.0 / keypoints_2.size();
    if(match2>1){
        match2 = keypoints_2.size() * 1.0 / keypoints_1.size();
    }
    //LOGI("match:                      \t%f", match2);
    return (match+match2)/2;
}

/*vector<KeyPoint> kpts1, kpts2;
   Mat desc1, desc2;

   Ptr<AKAZE> akaze = AKAZE::create();
   akaze->detectAndCompute(img1, noArray(), kpts1, desc1);
   akaze->detectAndCompute(img2, noArray(), kpts2, desc2);

   BFMatcher matcher(NORM_HAMMING);
   vector< vector<DMatch> > nn_matches;
   matcher.knnMatch(desc1, desc2, nn_matches, 2);

   vector<KeyPoint> matched1, matched2, inliers1, inliers2;
   vector<DMatch> good_matches;
   for(size_t i = 0; i < nn_matches.size(); i++) {
       DMatch first = nn_matches[i][0];
       float dist1 = nn_matches[i][0].distance;
       float dist2 = nn_matches[i][1].distance;

       if(dist1 < nn_match_ratio * dist2) {
           matched1.push_back(kpts1[first.queryIdx]);
           matched2.push_back(kpts2[first.trainIdx]);
       }
   }

   for(unsigned i = 0; i < matched1.size(); i++) {
       Mat col = Mat::ones(3, 1, CV_64F);
       col.at<double>(0) = matched1[i].pt.x;
       col.at<double>(1) = matched1[i].pt.y;

       col = homography * col;
       col /= col.at<double>(2);
       double dist = sqrt( pow(col.at<double>(0) - matched2[i].pt.x, 2) +
                           pow(col.at<double>(1) - matched2[i].pt.y, 2));

       if(dist < inlier_threshold) {
           int new_i = static_cast<int>(inliers1.size());
           inliers1.push_back(matched1[i]);
           inliers2.push_back(matched2[i]);
           good_matches.push_back(DMatch(new_i, new_i, 0));
       }
   }
   Mat res;
   drawMatches(img1, inliers1, img2, inliers2, good_matches, res);
   imwrite("/sdcard/test100.jpg", res);


   double inlier_ratio = inliers1.size() * 1.0 / matched1.size();
   LOGI("# Inliers Ratio:                      \t%f", inlier_ratio);
   return inlier_ratio;*/
