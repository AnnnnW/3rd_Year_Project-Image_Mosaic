//
//  main.cpp
//  Image_Mosaic
//
//  Created by WangAnnan on 2018/9/7.
//  Copyright © 2018年 WangAnnan. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;                             //包含cv命名空间

int main()
{
    Mat srcImage = imread("/Users/wangannan/Desktop/IMG_6064.jpg");             // Load the image
    imshow("Original Image", srcImage);         //Show the image, with the window name ""Original Image
    waitKey(0);                                 // Wait for any key to be pressed
    return 0;
}
