//
//  ImageAnalysis.cpp
//  Image_Mosaic
//
//  Created by WangAnnan on 08/10/2018.
//  Copyright © 2018 WangAnnan. All rights reserved.
//

#include "ImageAnalysis.hpp"

int readImgName(String readpath, String defaultpath)
{
    struct dirent *ptr;
    DIR *dir;
    string path = readpath + "Resource";
    dir = opendir(path.c_str());
    vector<string> imgs;
    cout << "file name" << endl;
    if ((ptr = readdir(dir)) == NULL)
    {
        printf("Nothing in this directory!\n");
        return -1;
    }
    
    while ((ptr = readdir(dir)) != NULL)
    {
        //skip "." and ".."
        if (ptr -> d_name[0] == '.')
            continue;
        imgs.push_back(ptr -> d_name); //add the d_name to the end of the vector
    }
    
    ofstream outfile;
    outfile.open(defaultpath + "data.csv");
    
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
    cout << "Data.csv file has successfully saved." << endl;
    return 0;
}
