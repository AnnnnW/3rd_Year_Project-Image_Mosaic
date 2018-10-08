//
//  ImageCutter.cpp
//  Image_Mosaic
//
//  Created by WangAnnan on 08/10/2018.
//  Copyright © 2018 WangAnnan. All rights reserved.
//

#include "ImageCutter.hpp"

//Mat resizer(Mat targetImg, int col, int row);

int ImageCutter(Mat targetImage)
{
    Mat tempImg;
    int col = targetImage.cols;
    int row = targetImage.rows;
    
    //resize the target image size if the size is too large for the screen (i.e. 1440 * 900)
    if (col > 900 || row > 1400)
    {
        tempImg = resizer(targetImage, col, row);
    } // if
    
    imshow("Resized", tempImg);
    return 0;
}

Mat resizer(Mat targetImg, int col, int row)
{
    int temp;
    Mat tempImg;
    if (col > 900)
    {
        temp = (int)col / 800;
        col = (int)col / temp;
    } // if
    
    if (row > 1400)
    {
        temp = row / 1300;
        row = (int) row / temp;
    } // if
    
    resize(targetImg, tempImg, Size(row, col));
    return tempImg;
}
