//
//  main.cpp
//  Image_Mosaic
//
//  Created by WangAnnan on 2018/9/7.
//  Copyright © 2018年 WangAnnan. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <vector>
#include <string>
#include <dirent.h>

#include "Resize.hpp"
#include "ImageDetail.hpp"

using namespace cv;                             //包含cv命名空间
using namespace std;

String defaultpath = "/Users/wangannan/Image_Mosaic/IMG/";
String readpath = defaultpath + "Input/";
String savepath = defaultpath + "Output/";

int readImgName()
{
    struct dirent *ptr;
    DIR *dir;
    string path = readpath + "Resource";
    dir = opendir(path.c_str());
    vector<string> imgs;
    cout << "file name" << endl;
    while ((ptr = readdir(dir)) != NULL)
    {
        //skip "." and ".."
        if (ptr -> d_name[0] == '.')
            continue;
        imgs.push_back(ptr -> d_name); //add the d_name to the end of the vector
    }
    
    ofstream outfile;
    outfile.open(defaultpath + "data.csv", ofstream::app);      //if the file doesnt exist, create a file;otherwise, add to the end of the file
    
    for (int i = 1; i < imgs.size(); i++)
    {
        if (outfile.is_open())
        {
            outfile << imgs[i] << endl;
        } //if
        else
        {
            cout << "Cannot open the file" << endl;
        } // else
    } //for
    outfile.close();
    closedir(dir);
    return 0;
}


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
    
//    resize(srcImage,tempImage,Size(100,100),0,0,INTER_LINEAR);      //resize the srcimage to a certain fix size 100 * 100
//
//    imwrite(savepath + "Result.jpg", tempImage);            // write an image as an output file
//    Mat resultImage = imread("Result.jpg");     // print out the result image in a new window
//    if (!resultImage.data)
//    {
//        printf("Can't read the file, please check the path and try again.\n");
//        return -1;
//    }
//    namedWindow("Result Image", WINDOW_AUTOSIZE);
//    imshow("Result Image", resultImage);
    
    //read the image name and output a file
    readImgName();
    waitKey(0);                                 // Wait for any key to be pressed to exit
    return 0;
}
