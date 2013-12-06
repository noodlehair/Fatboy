#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "object.h"
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif

#define GLUT_DISABLE_ATEXIT_HACK
using namespace std;

    object::object(float r, float px, float py, float pz, 
        float cr, float cg, float cb):
      radius(r), position_x(px), position_y(py), position_z(pz), 
		  color_r(cr), color_g(cg), color_b(cb){};
 
 
    void object::draw(
        float ambient, float diffuse, float specular, float emission, float shininess,
		float bullit_x, float bullit_y, float bullit_z, bool* ifDraw, float angle, float lookAt_z, bool shoot){

        glPushMatrix();
         
        glTranslatef(position_x, position_y, position_z);
 
        GLfloat mat_ambient[]  = {ambient, ambient, ambient, 1.0f};         
        GLfloat mat_diffuse[]  = {diffuse, diffuse, diffuse, 1.0f};         
        GLfloat mat_specular[] = {specular, specular, specular, 1.0f};         
        GLfloat mat_emission[] = {emission, emission, emission, 1.0f};         
        GLfloat mat_shininess  = shininess;           
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);         
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);         
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);         
        glMaterialfv(GL_FRONT, GL_EMISSION,  mat_emission);         
        glMaterialf (GL_FRONT, GL_SHININESS, mat_shininess);

		if(angle!=0){
         if(shoot && tan(angle)<(1.0*(-position_x+bullit_x+radius)/(-position_z+lookAt_z)) 
			 && tan(angle)>(1.0*(-position_x+bullit_x-radius)/(-position_z+bullit_z))
			 && position_y-radius<bullit_y && position_y+radius>bullit_y 
			 && pow(bullit_x-position_x,2)+pow(lookAt_z-position_z,2)+0.5<pow(bullit_z-lookAt_z, 2)
			 && pow(bullit_x-position_x,2)+pow(lookAt_z-position_z,2)-0.5<pow(bullit_z-lookAt_z, 2))
			 //pow(bullit_x-position_x, 2)+pow(bullit_y-position_y, 2)<pow(radius, 2) && position_z-bullit_z<radius 
			// &&position_z-bullit_z>-radius)
		 {
			 //glutSolidSphere(radius/10, 50,50);
			 drawIt=false;
			 *ifDraw=false;
		}
		 if(ifDraw && drawIt&&!(shoot && tan(angle)<(1.0*(-position_x+bullit_x+radius)/(-position_z+lookAt_z)) 
			 && tan(angle)>(1.0*(-position_x+bullit_x-radius)/(-position_z+bullit_z))
			 && position_y-radius<bullit_y && position_y+radius>bullit_y 
			 && pow(bullit_x-position_x,2)+pow(lookAt_z-position_z,2)+0.5<pow(bullit_z-lookAt_z, 2)
			 && pow(bullit_x-position_x,2)+pow(lookAt_z-position_z,2)-0.5<pow(bullit_z-lookAt_z, 2))){
			 glColor3f(color_r,color_g,color_b);
			glutSolidSphere(radius, 50,50);
		 }
		}
		else{
			if(shoot && pow(bullit_x-position_x, 2)+pow(bullit_y-position_y, 2)<pow(radius, 2) && position_z-bullit_z<radius 
			 &&position_z-bullit_z>-radius){
			 //glutSolidSphere(radius/10, 50,50);
			 drawIt=false;
			 *ifDraw=false;
			}
			if(ifDraw && drawIt&&!(shoot && pow(bullit_x-position_x, 2)+pow(bullit_y-position_y, 2)<pow(radius, 2) && position_z-bullit_z<radius 
			 &&position_z-bullit_z>-radius)){
				 glColor3f(color_r,color_g,color_b);
			glutSolidSphere(radius, 50,50);
		 }
		}
         
        glPopMatrix();
    }
