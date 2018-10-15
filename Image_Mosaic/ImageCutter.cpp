//
//  ImageCutter.cpp
//  Image_Mosaic
//
//  Created by WangAnnan on 08/10/2018.
//  Copyright © 2018 WangAnnan. All rights reserved.
//

#include "ImageCutter.hpp"

vector<Mat> hsvSplit;

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
    
//    Mat hsvImg = hsvTrans(tempImg);
    
    int height = tempImg.cols;
    int width = tempImg.rows;
    
    //mosaic target image
    mosaicFilter(tempImg, height, width);
    
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

Mat hsvTrans(Mat targetImg)
{
    Mat hsvImg;
    
    // lower bound and higher bound for hue, saturation and value
//    int iLowH = 0;
//    int iHighH = 180;
//    int iLowS = 0;
//    int iHighS = 255;
//    int iLowV = 0;
//    int iHighV = 255;
    
//    vector<Mat> hsvSplit;
    cvtColor(targetImg, hsvImg, COLOR_BGR2HSV);     // transform rgb image to hsv image
    
    // make a histogram for the hsv value
    split(hsvImg, hsvSplit);
    equalizeHist(hsvSplit[2], hsvSplit[2]);
    merge(hsvSplit, hsvImg);    // merge the array of hsvImg and hsvSplit together
    
//    Mat threshouldedImg;
//    inRange(hsvImg, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), threshouldedImg);
    
    imshow("hsv", hsvImg);
    return hsvImg;
}

void mosaicFilter(Mat targetImg, int height, int width)
{
    int i, j, k, start, temp, centre;
    
    int mosaicArray[8][3];

    for (i = 1; i < height - 1; i++)
        for (j = 1; j < width - 1; j++)
        {
            centre = i * width + j;     // the centre of the 3 * 3 filter, which is the 5th
            start = centre - width - 1;     // the first pixel for the 3 * 3 filter
            temp = 0;
            
            for (k = 0; k < 9; k++)
            {
//                mosaicArray[k] = hsvSplit[start + temp];
                mosaicArray[k][0] = targetImg.at<Vec3b>(j, i)[0];       // B
                mosaicArray[k][1] = targetImg.at<Vec3b>(j, i)[1];       // G
                mosaicArray[k][2] = targetImg.at<Vec3b>(j, i)[2];       // R
                temp++;
                if (temp == 3)      // if the first 3 in a row has added to the array, then jump to the next row
                {
                    temp = 0;
                    start = start + width;
                } // if
            } // for
        } // for
    
//    int average = averageValue(mosaicArray);
} // mosaicFilter

// avarage value of the 9 pixels
//int averageValue(int mosaicArray)
//{
//    int sum, average;
//    for (int i = 0; i < mosaicArray.size(); i++)
//    {
//        sum = sum + mosaicArray[i];
//    }
//    
//    sum /= mosaicArray.size();
//    
//    return average;
//}

// mediam value among the 9 pixels
int medianValue(vector<Mat> mosaicArray)
{
    return 0;
}
