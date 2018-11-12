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
#include "TileAnalyser.hpp"
#include "Tiler.hpp"

using namespace cv;                             //包含cv命名空间
using namespace std;

string defaultpath = "/Users/wangannan/Image_Mosaic/IMG/";
string readpath = defaultpath + "Input/";
string savepath = defaultpath + "Output/";

int main()
{
    Mat targetImage = imread(readpath + "testing_image.jpg");             // Load the image
//    Mat targetImage = imread(readpath + "C3FDFBFA-AFE0-4F06-8093-8C8C005D6B75-1277-000000D003A7E724_tmp.jpg");             // Load the image

    if (!targetImage.data)
    {
        printf("Can't read the file, please check the path and try again.\n");
        return -1;
    }
    
    ImageCutter(targetImage);
    
    //read the image name and output a file
    TileAnalyser(readpath, defaultpath);
    
    Mat mosaicImage = imread(readpath + "9*9Cutter.jpg");             // Load the image

    Tiler(mosaicImage, readpath, defaultpath, savepath);
    
    
    if(waitKey(0))                                 // Wait for any key to be pressed to exit
    {
        printf("The program is successfully exited by keyboard interruption :) \n");
    }
    return 0;
}
