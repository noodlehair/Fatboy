//
//  ImageIO.cpp
//  Resolution
//
//  Created by Tabitha Peck on 7/23/13.
//  Copyright (c) 2013 Tabitha Peck. All rights reserved.
//  based on code from stack overflow: http://stackoverflow.com/questions/2693631/read-ppm-file-and-store-it-in-an-array-coded-with-c


#include "ImageIO.h"
#define GLUT_DISABLE_ATEXIT_HACK



ImageIO::ImageIO(int w, int h, int m){
    width = w;
    height = h;
    max = m;
    image = new float**[height];
    for(int i = 0; i < height; i++){
        image[i] = new float*[width];
        for(int j = 0; j < width; j++){
            image[i][j] = new float[3];
            image[i][j][0] = 0;
            image[i][j][1] = 0;
            image[i][j][2] = 0;
        }
    }
    imageDisplayArray = NULL;
}

ImageIO::ImageIO(const char* file_name){
    
    FILE* file;
    char buff[16];
    float r, g, b;
    
    file = fopen(file_name, "r"); // open file for reading
    
    if(!file){
        fprintf(stderr, "Unable to open file %s", file_name);
        exit(1);
    }
    
    fscanf(file, "%s%*[^\n]%*c", magic_number); //read magic number and white space
    if(magic_number[0] != 'P' || magic_number[1] != '3'){
        printf("Incorrect file type");
        exit(1);
    }
    
    //check for comments
    fscanf(file, "%s", buff);
    while (strncmp(buff, "#", 1) == 0) {
        fscanf(file, "%s%*[^\n]%*c", buff);
    }
    
    if (fscanf(file, "%d %d %d", &width, &height, &max) != 3) {
        fprintf(stderr, "Invalid image size (error loading '%s')\n", file_name);
        exit(1);
    }
    
    image = new float **[height];
    for(int i = 0; i < height; i++) {
        image[i] = new float *[width];
        for(int j = 0; j<width; j++){
            image[i][j] = new float[3];
            if(fscanf(file, "%f %f %f", &r, &g, &b) != 3){
                fprintf(stderr, "Invalid pixel reading\n");
                exit(1);
            }
            image[i][j][0] = r/255;
            image[i][j][1] = g/255;
            image[i][j][2] = b/255;
        }
    }
    
    fclose(file);
    imageDisplayArray = NULL;
}

ImageIO::~ImageIO(void){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            delete [] image[i][j];
        }
        delete [] image[i];
    }
    delete [] image;
    
    delete [] imageDisplayArray;
}

ImageIO* ImageIO::removeRed(){
    ImageIO* red = new ImageIO(width, height, max);
    //your code goes here
	
	  
	 red->magic_number[0] = magic_number[0];
	 red->magic_number[1] = magic_number[1];
	 red->magic_number[2] = '\0';
    for(int i = 0; i< height; i++) {
        for(int j = 0; j<width; j++){
            red->image[i][j][0] =0;
			red->image[i][j][1] =image[i][j][1];
			red->image[i][j][2] =image[i][j][2];
        }
    }
    
    return red;
}

ImageIO* ImageIO::grayScale(){
	 ImageIO* gs = new ImageIO(width, height, max);
	 gs->magic_number[0] = magic_number[0];
	 gs->magic_number[1] = magic_number[1];
	 gs->magic_number[2] = '\0';
    //your code goes here
    for(int i = height-1; i>=0; i--) {
        for(int j = 0; j<width; j++){
			float val = image[i][j][0] * 0.2126 + image[i][j][1] * 0.7251+ image[i][j][2] * 0.0722;
            gs->image[i][j][0] = val;
			gs->image[i][j][1] = val;
			gs->image[i][j][2] = val;
        }
    }
    
    return gs;

}
/*
 *This function performs simple edge detection using a filter matrix
 * For this we apply the filter to the image by performing convolution. So each pixel of the image is treated with the center 
 * element of the matrix while its adjacent elements aligned and treated with the rest of the filter matrix.
 *
 */
ImageIO* ImageIO::edgeDetection(){
	ImageIO* edge = new ImageIO(width, height, max);
	 edge->magic_number[0] = magic_number[0];
	 edge->magic_number[1] = magic_number[1];
	 edge->magic_number[2] = '\0';
	int filterw =3;
	int filterh =3;
	float filter[3][3] ={  0, -1,  0, -1, 4,  -1, 0, -1,  0}; //the edge detection matrix

	for(int x = 0; x < width; x++) 
		for(int y= 0; y < height; y++) { 
			double r = 0.0, g = 0.0, b = 0.0; 
            /* the convolution is cariied out below, for a 3x3 matrix we got from -1 to 1 so that 
			   the middle element's coordinates are 0,0*/
			for(int fx = -1*filterw / 2; fx <= filterw/2; fx++) 
				for(int fy = -1*filterh/2; fy <= filterh/2; fy++) { 
					int i = (y  + fy + height) % height;  // mod operations are performed to keep the values in limits of the matrix
					int j = (x  + fx + width) % width;
					r += image[i][j][0] * filter[fy +filterh/2][fx+filterw/2]; // some arthimetic to make fx and fy correspond to the indices of the filter matrix
					g += image[i][j][1] * filter[fy+filterh/2][fx+filterw/2]; 
					b += image[i][j][2] * filter[fy+filterh/2][fx+filterw/2]; 
				} 
         
        /* keep the r,g,b values in the range 0-255 both inclusive*/
		if(r < 0){
			edge->image[y][x][0]=0;
		} else if (r>255){
			edge->image[y][x][0]=255;
		}else{
			edge->image[y][x][0] = r;
		}
		
		if(g < 0){
			edge->image[y][x][1]=0;
		} else if (g>255){
			edge->image[y][x][1]=255;
		}else{
			edge->image[y][x][1] = g;
		}
		
		if(b < 0){
			edge->image[y][x][2]=0;
		} else if (b>255){
			edge->image[y][x][2]=255;
		}else{
			edge->image[y][x][2] = b;
		}	
    } 
	return edge;
}

/*
 * This function performs image sharpening using a sharpen filter matrix
 * For this we apply the sharpen filter to the image by performing convolution. So each pixel of the image is treated with the center 
 * element of the matrix while its adjacent elements aligned and treated with the rest of the filter matrix.
 * The filter in this case sharpens the edges more as compares to the rest of the image
 */
ImageIO* ImageIO::sharpenFilter(){
	ImageIO* sharp = new ImageIO(width, height, max);
	 sharp->magic_number[0] = magic_number[0];
	 sharp->magic_number[1] = magic_number[1];
	 sharp->magic_number[2] = '\0';
	int filterw =3;
	int filterh =3;
	float filter[3][3] ={  1, 1,  1, 1, -7,  1, 1, 1,  1}; //the sharpen filter matrix

	for(int x = 0; x < width; x++) 
		for(int y= 0; y < height; y++) { 
			double r = 0.0, g = 0.0, b = 0.0; 
            /* the convolution is cariied out below, for a 3x3 matrix we got from -1 to 1 so that 
			   the middle element's coordinates are 0,0*/
			for(int fx = -1*filterw / 2; fx <= filterw/2; fx++) 
				for(int fy = -1*filterh/2; fy <= filterh/2; fy++) { 
					int i = (y  + fy + height) % height;  // mod operations are performed to keep the values in limits of the matrix
					int j = (x  + fx + width) % width;
					r += image[i][j][0] * filter[fy +filterh/2][fx+filterw/2]; // some arthimetic to make fx and fy correspond to the indices of the filter matrix
					g += image[i][j][1] * filter[fy+filterh/2][fx+filterw/2]; 
					b += image[i][j][2] * filter[fy+filterh/2][fx+filterw/2]; 
				} 
         
        /* keep the r,g,b values in the range 0-255 both inclusive*/
		if(r < 0){
			sharp->image[y][x][0]=0;
		} else if (r>255){
			sharp->image[y][x][0]=255;
		}else{
			sharp->image[y][x][0] = r;
		}
		
		if(g < 0){
			sharp->image[y][x][1]=0;
		} else if (g>255){
			sharp->image[y][x][1]=255;
		}else{
			sharp->image[y][x][1] = g;
		}
		
		if(b < 0){
			sharp->image[y][x][2]=0;
		} else if (b>255){
			sharp->image[y][x][2]=255;
		}else{
			sharp->image[y][x][2] = b;
		}	
    } 
	return sharp;
}





int ImageIO::getWidth(){
    return width;
}

int ImageIO::getHeight(){
    return height;
}

float*** ImageIO::getImage(){
    return image;
}

float* ImageIO::getImageDisplayArray() {
    if(imageDisplayArray != NULL)
        return imageDisplayArray;
        
    imageDisplayArray = new float[width * height * 3];
	int k=0;
	//removeRed();
	//grayScale();
	for(int i = height-1; i>=0; i--) {
        
        for(int j = 0; j<width; j++){
          
           imageDisplayArray[k++]= image[i][j][0] ;
            imageDisplayArray[k++]=image[i][j][1] ;
            imageDisplayArray[k++]=image[i][j][2] ;
        }
    }
    
    return imageDisplayArray;
}

void ImageIO::writeImage(const char* file_name){
    FILE* file;
    file = fopen(file_name, "w");
    if(!file){
        fprintf(stderr, "Unable to open file %s", file_name);
        exit(1);
    }
	
		fprintf(file, "%s\n",magic_number);
		fprintf(file, "%d %d %d\n", width, height, max);
	
    // your code goes here
    for(int i = 0; i < height; i++) {
       
        for(int j = 0; j<width; j++){
           
            fprintf(file, "%d %d %d ", (int)(image[i][j][0]*255), (int)(image[i][j][1]*255),  (int)(image[i][j][2]*255));
                
     
        }
    }
    
    
    
    
    fclose(file);
    
}

