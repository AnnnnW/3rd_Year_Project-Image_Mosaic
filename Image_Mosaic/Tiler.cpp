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

int Tiler(string readpath, string defaultpath)
{
    string path = readpath + "Resource/";
    string filePath = defaultpath + "data.csv";

    vector<string> tiles;
    vector<Vec3b> averages;
    vector<int> hue;

    reader(filePath, tiles, averages, hue);
    
    return 0;
} // Tiler

void reader(string filePath, vector<string> tiles, vector<Vec3b> averages, vector<int> hue)
{
    ifstream data(filePath);
    
    if (!data)
    {
        printf("Can't open the file.");
        exit(EXIT_FAILURE);
    }
    string line;
    Vec3b average;
    int count = -1;
    
    if (count == -1)// get rid of the first title line in data.csv
    {
        getline(data, line);
        count++;
    } // if
    while(getline(data, line, ','))
    {
        if (count == 0)
        {
            tiles.push_back(line);
            count++;
        } // if
        else if (count == 1)
        {
            cout << line << endl;
            average[0] = stoi(line);
            count++;
        } // else if
        else if (count == 2)
        {
            average[1] = stoi(line);
            count++;
        } // else if
        else if (count == 3)
        {
            average[2] = stoi(line);
            averages.push_back(average);
            count++;
        } // else if
        else if (count == 4)
        {
            hue.push_back(stoi(line));
            count = 0;
        } // else if
    } // while
} // reader

