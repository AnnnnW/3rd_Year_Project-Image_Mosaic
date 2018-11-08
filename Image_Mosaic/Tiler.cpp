//
//  Tiler.cpp
//  Image_Mosaic
//
//  Created by WangAnnan on 08/10/2018.
//  Copyright © 2018 WangAnnan. All rights reserved.
//

#include "Tiler.hpp"
#include "TileAnalyser.hpp"
#include "ImageCutter.hpp"

int Tiler(Mat targetImg, string readpath, string defaultpath, string savepath)
{
    string path = readpath + "Resource/";
    string filePath = defaultpath + "data.csv";

    vector<string> tiles;
    vector<Vec3b> averages;
    vector<int> hue;

    reader(filePath, tiles, averages, hue);

    Mat tempImg = targetImg, bestFitTile;
    
    int i = 0, j = 0, pixelX = 0, pixelY = 0, bestFitIndex;
    int height = tempImg.rows;
    int width = tempImg.cols;
    
    Vec3b averageRGB;
    
    for (i = 4; i < width - 4; i+=9)
    {
        for (j = 4; j < height - 4; j+=9)
        {
            pixelX = i;
            pixelY = j;
            averageRGB = tempImg.at<Vec3b>(pixelY,pixelX);
            
            bestFitIndex = compareHue(averageRGB, hue);
            bestFitTile = findBestFitTile(readpath, bestFitIndex, tiles);

            pixelX = i - 4;     // the first pixel for the 3 * 3 filter
            pixelY = j - 4;

            tileReplacement(SIZE, tempImg, bestFitTile, pixelY, pixelX, 9);
        } // for
    } // for
    
    int extraW = i - 5 ;
    int extraH = j - 5;
    int size;
    
    // when the width cannot be exactly divided by 9
    if (width % 9 != 0)
    {
        size = (width - extraW) * 9;
        
        for (j = 4; j < height - 4; j += 9)
        {
            pixelX = extraW;
            pixelY = j;
            
            averageRGB = tempImg.at<Vec3b>(pixelY,pixelX);
            bestFitIndex = compareHue(averageRGB, hue);
            bestFitTile = findBestFitTile(readpath, bestFitIndex, tiles);

            pixelX = extraW;
            pixelY = j - 4;

            tileReplacement(size, tempImg, bestFitTile, pixelY, pixelX, (width - extraW));
        } // for
    } // if
    
    if (height % 9 != 0)
    {
        size = (height - extraH) * 9;
        
        for (i = 4; i < width; i += 9)
        {
            pixelX = i - 4;
            pixelY = extraH;
            
            
            averageRGB = tempImg.at<Vec3b>(pixelY,pixelX);
            bestFitIndex = compareHue(averageRGB, hue);
            bestFitTile = findBestFitTile(readpath, bestFitIndex, tiles);

            pixelX = i - 4;
            pixelY = extraH;

            tileReplacement(size, tempImg, bestFitTile, pixelY, pixelX,9);

        } // for
    } // if
    
    imshow("Result", tempImg);
    imwrite(savepath + "result.jpg", tempImg);
    printf("The result picture has been created.\n");

    
    return 0;
} // Tiler

void reader(string filePath, vector<string> &tiles, vector<Vec3b> &averages, vector<int> &hue)
{
    ifstream data(filePath);
    
    if (!data)
    {
        printf("Can't open the file.");
        exit(EXIT_FAILURE);
    }
    string line;
    string word;
    Vec3b average;
    int count = -1;
    
    if (count == -1)// get rid of the first title line in data.csv
    {
        getline(data, line);
        count++;
    } // if
    while(getline(data, line))
    {
        stringstream parsing(line);
        while (getline(parsing, word, ','))
        {
            if (count == 0)
            {
                tiles.push_back(word);
                count++;
            } // if
            else if (count == 1)
            {
                average[0] = stoi(word);
                count++;
            } // else if
            else if (count == 2)
            {
                average[1] = stoi(word);
                count++;
            } // else if
            else if (count == 3)
            {
                average[2] = stoi(word);
                averages.push_back(average);
                count++;
            } // else if
            else if (count == 4)
            {
                hue.push_back(stoi(word));
                count = 0;
            } // else if
        } // while
    } // while
    
} // reader

int compareHue(Vec3b averageRGB, vector<int> hue)
{
    int averageHue = (int)hsvTrans(averageRGB)[0] * 2;
    
    int temp, currentMin = 360, bestFitIndex = 0;
    
    for (int i = 0; i < hue.size(); i++)
    {
        temp = abs(hue[i] - averageHue);        // stored as an absolute value, need to be none-negative
        if (currentMin > temp)
        {
            currentMin = temp;
            bestFitIndex = i;
        } // if
    } // for
    
    return bestFitIndex;
} // compareHue

Mat findBestFitTile(string readPath, int bestFitIndex, vector<string> tiles)
{
    Mat tile = imread(readPath + "Resizer/" + tiles[bestFitIndex]);
    return tile;
}

void tileReplacement(int size, Mat targetImg, Mat tile, int pixelY, int pixelX, int breakpoint)
{
        int temp = 0, i = 0;
    
        for (int k = 0; k < size; k++)
        {
            targetImg.at<Vec3b>(pixelY, pixelX + temp) = tile.at<Vec3b>(i, temp);
            temp++;
            if (temp == breakpoint)
            {
                temp = 0;
                i++;
                pixelY++;
            } // if
        } // for
} // tileReplacement
