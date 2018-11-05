//
//  TileAnalyser.cpp
//  Image_Mosaic
//
//  Created by WangAnnan on 22/10/2018.
//  Copyright © 2018 WangAnnan. All rights reserved.
//

#include "TileAnalyser.hpp"

int TileAnalyser(string readpath, string defaultpath)
{
    struct dirent *ptr;
    DIR *dir;
    string path = readpath + "Resource/";
    dir = opendir(path.c_str());
    vector<string> tiles;
    vector<Vec3b> averages;
    int rgbArray[SIZE][RGB];
    if ((ptr = readdir(dir)) == NULL)
    {
        printf("Nothing in this directory!\n");
        return -1;
    } // if
    
    Mat tempImg;
    dir = opendir(path.c_str());
    
    while ((ptr = readdir(dir)) != NULL)
    {
        if (ptr -> d_name[0] == '.')
            continue;
        tiles.push_back(ptr -> d_name); //add the d_name to the end of the vector

        tempImg = imread(path + ptr -> d_name);
        tempImg = tileResizer(tempImg, 9, 9);
        imwrite(readpath + "Resizer/" + ptr -> d_name, tempImg);
        
        readPixel(SIZE, rgbArray, tempImg, 0, 0, 9);
        
        averages.push_back(averageValue(SIZE, rgbArray));

    } // while
    
    // 写入文件
    writter(ptr, dir, tiles, averages, readpath, defaultpath);
    return 0;
} // ImageAnalysis

int writter(struct dirent *ptr, DIR *dir, vector<string> tiles, vector<Vec3b> averages, string path, string defaultpath)
{
    ofstream outfile;
    outfile.open(defaultpath + "data.csv", ios::out | ios::trunc);          // If the file exist, then set the length to 0 then open
    outfile << "Name,B,G,R,H"  << endl; // 4 columns represent: name, B, G and R value

    for (int i = 1; i < tiles.size(); i++)
    {
        if (outfile.is_open())
        {
            outfile << tiles[i] << "," << (int)averages[i][0]  << "," << (int)averages[i][1]  << "," << (int)averages[i][2] << endl;
        } //if
        else
        {
            cout << "Cannot open the file" << endl;
        } // else
    } //for
    outfile.close();
    closedir(dir);
    cout << "Data.csv file has been created." << endl;
    return 0;
} // writter

Mat tileResizer(Mat targetImg, int col, int row)
{
    Mat tempImg;
    resize(targetImg, tempImg, Size(row, col));
    return tempImg;
} // resizer