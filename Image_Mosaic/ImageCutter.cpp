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
    
    int mosaicArray[SIZE][RGB];
    
    for (i = 4; i < height - 4; i+=9)
        for (j = 4; j < width - 4; j+=9)
        {
            temp = 0;
            pixelX = i - 4;     // start from the first pixel for the 3 * 3 filter
            pixelY = j - 4;

            for (k = 0; k < SIZE; k++)
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

            average = averageValue(SIZE, mosaicArray);

            pixelX = i - 4;     // the first pixel for the 3 * 3 filter
            pixelY = j - 4;
            temp = 0;

            for (k = 0; k < SIZE; k++)
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
}
