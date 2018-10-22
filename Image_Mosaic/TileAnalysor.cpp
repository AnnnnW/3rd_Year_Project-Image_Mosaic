//
//  TileAnalysor.cpp
//  Image_Mosaic
//
//  Created by WangAnnan on 22/10/2018.
//  Copyright © 2018 WangAnnan. All rights reserved.
//

#include "TileAnalysor.hpp"

int TileAnalysor(String readpath, String defaultpath)
{
    struct dirent *ptr;
    DIR *dir;
    String path = readpath + "Resource";
    dir = opendir(path.c_str());
    vector<String> tiles;
    if ((ptr = readdir(dir)) == NULL)
    {
        printf("Nothing in this directory!\n");
        return -1;
    } // if
    readImgName(ptr, dir, tiles, readpath, defaultpath);
    
    Mat temp, resized;
    dir = opendir(path.c_str());
    while ((ptr = readdir(dir)) != NULL)
    {
        temp = imread(path + ptr -> d_name);
//        cout << path + ptr -> d_name << endl;
//        resized = resizer(temp, 9, 9);
//        imwrite(readpath + "Resizer" + ptr -> d_name, resized);
    } // while
    
    return 0;
} // ImageAnalysis

//int readImgName(String readpath, String defaultpath)
int readImgName(struct dirent *ptr, DIR *dir, vector<String> tiles, String path, String defaultpath)
{
    while ((ptr = readdir(dir)) != NULL)
    {
        //skip "." and ".."
        if (ptr -> d_name[0] == '.')
            continue;
        tiles.push_back(ptr -> d_name); //add the d_name to the end of the vector
    } // while
    
    ofstream outfile;
    outfile.open(defaultpath + "data.csv");
    
    for (int i = 1; i < tiles.size(); i++)
    {
        if (outfile.is_open())
        {
            outfile << tiles[i] << endl;
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
} // readImgName

Mat resizer(Mat targetImg, int col, int row)
{
//    int temp;
    Mat tempImg;
//    if (col > 900)
//    {
//        temp = (int)col / 800;
//        col = (int)col / temp;
//    } // if
//
//    if (row > 1400)
//    {
//        temp = row / 1300;
//        row = (int) row / temp;
//    } // if
    
    resize(targetImg, tempImg, Size(row, col));
    return tempImg;
} // resizer
