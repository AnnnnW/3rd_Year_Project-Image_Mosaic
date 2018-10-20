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
    
    int height = tempImg.rows;
    int width = tempImg.cols;
    
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
    
    int i = 0, j = 0, pixelX = 0, pixelY = 0;
    Vec3b average;
    
    int mosaicArray[SIZE][RGB];
    
    for (i = 4; i < width - 4; i+=9)
    {
        for (j = 4; j < height - 4; j+=9)
        {
            pixelX = i - 4;     // start from the first pixel for the 3 * 3 filter
            pixelY = j - 4;
            
            readPixel(SIZE, mosaicArray, targetImg, pixelY, pixelX, 9);
            
            average = averageValue(SIZE, mosaicArray);
            
            pixelX = i - 4;     // the first pixel for the 3 * 3 filter
            pixelY = j - 4;
            
            writePixel(SIZE, average, targetImg, pixelY, pixelX, 9);
        } // for
    } // for
    
    int extraW = i - 5 ;         // if the number of pixels is less than 9, the width of the left pixels
    int extraH = j - 5;         // if the number of pixels is less than 9, the height of the left pixels
    int size;

    // when the width cannot be exactly divided by 9
    if (width % 9 != 0)
    {
        size = (width - extraW) * 9;
        int extraArrayW[size][RGB];
        
        for (j = 4; j < height - 4; j += 9)
        {
            pixelX = extraW;
            pixelY = j - 4;
            
            readPixel(size, extraArrayW, targetImg, pixelY, pixelX, (width - extraW));

            average = averageValue(size, extraArrayW);
            
            pixelX = extraW;
            pixelY = j - 4;
            
            writePixel(size, average, targetImg, pixelY, pixelX, (width - extraW));
        } // for
    } // if
    
    if (height % 9 != 0)
    {
        size = (height - extraH) * 9;
        int extraArrayH[size][RGB];
        
        for (i = 0; i < width; i += 9)
        {
            pixelX = i - 4;
            pixelY = extraH;
            
            readPixel(size, extraArrayH, targetImg, pixelY, pixelX, 9);
            
            average = averageValue(size, extraArrayH);
            
            pixelX = i - 4;
            pixelY = extraH;
            
            writePixel(size, average, targetImg, pixelY, pixelX, 9);
        } // for
    } // if
    return 0;
} // mosaicFilter

void readPixel(int size, int array[size][RGB], Mat targetImg, int pixelY, int pixelX, int breakpoint)
{
    int temp = 0;
    for (int k = 0; k < size; k++)
    {
        array[k][0] = (int)targetImg.at<Vec3b>(pixelY, pixelX + temp).val[0];       // B
        array[k][1] = (int)targetImg.at<Vec3b>(pixelY, pixelX + temp).val[1];       // G
        array[k][2] = (int)targetImg.at<Vec3b>(pixelY, pixelX + temp).val[2];       // R
        temp++;
        if (temp == breakpoint)      // if the first 3 in a row has added to the array, then jump to the next row
        {
            temp = 0;
            pixelY++;
        } // if
    } // for
} // readPixel

void writePixel(int size, Vec3b average, Mat targetImg, int pixelY, int pixelX, int breakpoint)
{
    int temp = 0;
    for (int k = 0; k < size; k++)
    {
        targetImg.at<Vec3b>(pixelY, pixelX + temp) = average;
        temp++;
        if (temp == breakpoint)      // if the first 3 in a row has added to the array, then jump to the next row
        {
            temp = 0;
            pixelY++;
        } // if
    } // for
} // writePixel

// avarage value of the 9 pixels
Vec3b averageValue( int size, int array[size][RGB])
{
    int bSum = 0;
    int gSum = 0;
    int rSum = 0;
    
    for (int i = 0; i < size; i++)
    {
        bSum = bSum + array[i][0];
        gSum = gSum + array[i][1];
        rSum = rSum + array[i][2];
    }
    
    bSum = (int)bSum / size;
    gSum = (int)gSum / size;
    rSum = (int)rSum / size;
    
    Vec3b average = {(unsigned char)bSum, (unsigned char)gSum, (unsigned char)rSum};
    
    return average;
} // averageValue
