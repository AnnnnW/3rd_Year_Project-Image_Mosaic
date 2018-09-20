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

String readpath = "/Users/wangannan/Image_Mosaic/IMG/Input/";
String savepath = "/Users/wangannan/Image_Mosaic/IMG/Output/";

int main()
{
    Mat srcImage = imread(readpath + "testing_image.jpg");             // Load the image
    Mat tempImage;
    if (!srcImage.data)
    {
        printf("Can't read the file, please check the path and try again.\n");
        return -1;
    }
    namedWindow("Original Image", WINDOW_AUTOSIZE);              // name a window and decide the window size
    imshow("Original Image", srcImage);         //Show the image, with the window name "Original Image"
    
    resize(srcImage,tempImage,Size(100,100),0,0,INTER_LINEAR);      //resize the srcimage to a certain fix size 100 * 100
    
    imwrite(savepath + "Result.jpg", tempImage);            // write an image as an output file
    Mat resultImage = imread("Result.jpg");     // print out the result image in a new window
    if (!resultImage.data)
    {
        printf("Can't read the file, please check the path and try again.\n");
        return -1;
    }
    namedWindow("Result Image", WINDOW_AUTOSIZE);
    imshow("Result Image", resultImage);
    
    waitKey(0);                                 // Wait for any key to be pressed to exit
    return 0;
}
