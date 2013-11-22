#ifndef LOCALGRAPHICSLIB_H
#define LOCALGRAPHICSLIB_H
#include "ImageIO.h"
int LoadGLTextures(ImageIO* the_image,GLuint* texture );	
typedef struct						
{
	bool	active;					
	float	life;					
	float	fade;					
	float	r;						
	float	g;						
	float	b;						
	float	x;						
	float	y;						
	float	z;						
	float	xi;						
	float	yi;						
	float	zi;						
	float	xg;						
	float	yg;						
	float	zg;						
} particles;							// Particles Structure

#endif