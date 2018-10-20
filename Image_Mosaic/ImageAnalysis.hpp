//
//  ImageAnalysis.hpp
//  Image_Mosaic
//
//  Created by WangAnnan on 08/10/2018.
//  Copyright © 2018 WangAnnan. All rights reserved.
//

#ifndef ImageAnalysis_hpp
#define ImageAnalysis_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <dirent.h>

using namespace cv;
using namespace std;

int readImgName(String readpath, String defaultpath);

#endif /* ImageAnalysis_hpp */
