//
//  ImageIO.h
//  Resolution
//
//  Created by Tabitha Peck on 7/23/13.
//  Copyright (c) 2013 Tabitha Peck. All rights reserved.
//

#ifndef __Resolution__ImageIO__
#define __Resolution__ImageIO__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Filter.h"
#define GLUT_DISABLE_ATEXIT_HACK
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif
using namespace std;

class ImageIO{
public:
    ImageIO(int w, int h, int max);
    ImageIO(const char* file_name);
    ~ImageIO(void);
    void writeImage(const char* file_name);
    int getWidth();
    int getHeight();
    float*** getImage();
    float* getImageDisplayArray();
    ImageIO* removeRed();
	ImageIO* grayScale();
	/* function definition for edge detection*/
	ImageIO* edgeDetection();
	/* function definition for image sharpening */
	ImageIO* sharpenFilter();
	//ImageIO* blur(Filter* f);

private:
    char magic_number[2];
    int width;
    int height;
    int max;
    float*** image;
    float* imageDisplayArray;

};

#endif /* defined(__Resolution__ImageIO__) */
