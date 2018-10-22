//
//  main.cpp
//  Image_Mosaic
//
//  Created by WangAnnan on 2018/9/7.
//  Copyright © 2018年 WangAnnan. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "ImageCutter.hpp"
#include "TileAnalysor.hpp"

using namespace cv;                             //包含cv命名空间
using namespace std;

String defaultpath = "/Users/wangannan/Image_Mosaic/IMG/";
String readpath = defaultpath + "Input/";
String savepath = defaultpath + "Output/";

int main()
{
    Mat targetImage = imread(readpath + "testing_image.jpg");             // Load the image
//    Mat targetImage = imread(readpath + "C3FDFBFA-AFE0-4F06-8093-8C8C005D6B75-1277-000000D003A7E724_tmp.jpg");             // Load the image

    Mat tempImage;
    if (!targetImage.data)
    {
        printf("Can't read the file, please check the path and try again.\n");
        return -1;
    }
//    namedWindow("Original Image", WINDOW_AUTOSIZE);              // name a window and decide the window size
//    imshow("Original Image", targetImage);         //Show the image, with the window name "Original Image"
    
    ImageCutter(targetImage);
    
//    imwrite(savepath + "Result.jpg", tempImage);            // write an image as an output file
//    Mat resultImage = imread("Result.jpg");     // print out the result image in a new window
//    if (!resultImage.data)
//    {
//        printf("Can't read the file, please check the path and try again.\n");
//        return -1;
//    }
//    namedWindow("Result Image", WINDOW_AUTOSIZE);
//    imshow("Result Image", tempImage);
    

    
    //read the image name and output a file
    TileAnalysor(readpath, defaultpath);
    
    waitKey(0);                                 // Wait for any key to be pressed to exit
    return 0;
}
