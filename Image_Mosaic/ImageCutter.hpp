//
//  ImageCutter.hpp
//  Image_Mosaic
//
//  Created by WangAnnan on 08/10/2018.
//  Copyright © 2018 WangAnnan. All rights reserved.
//

#ifndef ImageCutter_hpp
#define ImageCutter_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat resizer(Mat targetImg, int col, int row);
int ImageCutter(Mat targetImage);
Mat hsvTrans(Mat targetImg);
Mat hsvTrans(Mat targetImg);
void mosaicFilter(Mat targetImg, int height, int width);
//int avarageValue(int mosaicArray);

#endif /* ImageCutter_hpp */
