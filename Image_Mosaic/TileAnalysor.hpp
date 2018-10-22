//
//  TileAnalysor.hpp
//  Image_Mosaic
//
//  Created by WangAnnan on 22/10/2018.
//  Copyright © 2018 WangAnnan. All rights reserved.
//

#ifndef TileAnalysor_hpp
#define TileAnalysor_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <dirent.h>

using namespace cv;
using namespace std;

int TileAnalysor(String readpath, String defaultpath);
int readImgName(struct dirent *ptr, DIR *dir, vector<String> tiles, String readpath, String defaultpath);
Mat resizer(Mat targetImg, int col, int row);
#endif /* TileAnalysor_hpp */
