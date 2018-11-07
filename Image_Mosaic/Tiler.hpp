//
//  Tiler.hpp
//  Image_Mosaic
//
//  Created by WangAnnan on 08/10/2018.
//  Copyright © 2018 WangAnnan. All rights reserved.
//

#ifndef Tiler_hpp
#define Tiler_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

int Tiler(string readpath, string defaultpath);
void reader(string filePath, vector<string> tiles, vector<Vec3b> averages, vector<int> hue);
Mat hsvTrans(Mat targetImg);

#endif /* Tiler_hpp */
