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
    else
    {
        tempImg = targetImage;
    } //else
    
    imshow("Resized", tempImg);
    
//    Mat hsvImg = hsvTrans(tempImg);
    
    int height = tempImg.cols;
    int width = tempImg.rows;
    
    //mosaic target image
    mosaicFilter(tempImg, height, width);
    imshow("Mosaic", tempImg);
    imwrite("/Users/wangannan/Image_Mosaic/IMG/Output/9*9.jpg", tempImg);
    printf("Mosaic target file has finished.\n" );
    
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

int mosaicFilter(Mat targetImg, int height, int width)
{
    printf("Add the filter onto the target image....\n");
    
    int i, j, k, pixelX, pixelY, temp;
    Vec3b average;
    
    int mosaicArray[81][3];

    for (i = 1; i < height - 4; i+=8)
        for (j = 1; j < width - 4; j+=8)
        {
            temp = 0;
            pixelX = i - 1;     // start from the first pixel for the 3 * 3 filter
            pixelY = j - 1;

            for (k = 0; k < 81; k++)
            {
                mosaicArray[k][0] = (int)targetImg.at<Vec3b>(pixelY, pixelX + temp).val[0];       // B
                mosaicArray[k][1] = (int)targetImg.at<Vec3b>(pixelY, pixelX + temp).val[1];       // G
                mosaicArray[k][2] = (int)targetImg.at<Vec3b>(pixelY, pixelX + temp).val[2];       // R
                temp++;
                if (temp == 9)      // if the first 3 in a row has added to the array, then jump to the next row
                {
                    temp = 0;
                    pixelY++;
                } // if
            } // for
            
            average = averageValue(mosaicArray);

            pixelX = i - 1;     // the first pixel for the 3 * 3 filter
            pixelY = j - 1;
            temp = 0;
            
            for (k = 0; k < 81; k++)
            {
                targetImg.at<Vec3b>(pixelY, pixelX + temp) = average;
                temp++;
                if (temp == 9)      // if the first 3 in a row has added to the array, then jump to the next row
                {
                    temp = 0;
                    pixelY++;
                } // if
            } // for
            
        } // for
    return 0;
} // mosaicFilter

// avarage value of the 9 pixels
Vec3b averageValue(int mosaicArray[81][3])
{
    int bSum = 0;
    int gSum = 0;
    int rSum = 0;

    for (int i = 0; i < 81; i++)
    {
        bSum = bSum + mosaicArray[i][0];
        gSum = gSum + mosaicArray[i][1];
        rSum = rSum + mosaicArray[i][2];
    }
    
    bSum = (int)bSum / 81;
    gSum = (int)gSum / 81;
    rSum = (int)rSum / 81;
    
//    printf("average rgb: {%i, %i, %i}", rSum, bSum, gSum);
    Vec3b average = {(unsigned char)bSum, (unsigned char)gSum, (unsigned char)rSum};
    
    return average;
}

// mediam value among the 9 pixels
int medianValue(vector<Mat> mosaicArray)
{
    return 0;
}
