#include "ShockwaveEmitter.h"
#include "LocalGraphicsLib.h"
#define MAX_SHOCK_PARTICLES 1
particles shockwave_particle[MAX_SHOCK_PARTICLES];	// Particle Array 

ShockwaveEmitter :: ShockwaveEmitter(const char* file_name){

	image = new ImageIO(file_name);
	slowdown=1000.0f;	
	zoom=-100.0f;	
	dx=2.0f*20;   
    dz=2.0f*20;   
	initFlag =false;
}
ShockwaveEmitter :: ~ShockwaveEmitter(void){
delete [] image;
}

void ShockwaveEmitter::shockwaveEmitterInit(){
	//ImageIO* image = new ImageIO("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/shock.ppm");
	LoadGLTextures(image, &texture[0]);							
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f,0.0f,0.0f,0.0f);					
	glClearDepth(1.0f);								
	glDisable(GL_DEPTH_TEST);							
	glEnable(GL_BLEND);									
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				
	glEnable(GL_TEXTURE_2D);							
	glBindTexture(GL_TEXTURE_2D,texture[0]);			

	for (loop=0;loop<MAX_SHOCK_PARTICLES;loop++)				
	{
		shockwave_particle[loop].active=true;								
		shockwave_particle[loop].life=1.0f;								
		shockwave_particle[loop].fade=float(rand()%100)/100000.0f;	
		shockwave_particle[loop].r=1.0;	
		shockwave_particle[loop].g=103/255.0;	;	
		shockwave_particle[loop].b=0.0;	
		shockwave_particle[loop].xi=float((rand()%50)-26.0f)*15;		
		shockwave_particle[loop].yi=float((rand()%50)-25.0f)*15;			
		shockwave_particle[loop].zi=float((rand()%50)-25.0f)*15;		
		shockwave_particle[loop].xg=0.0f;									
		shockwave_particle[loop].yg=0.0f;								
		shockwave_particle[loop].zg=0.0f;									
	}




}
void ShockwaveEmitter::shockwaveEmitterDisplay(){
	if(!initFlag){
	shockwaveEmitterInit();	
	 initFlag =true;
	}
for (loop=0;loop<MAX_SHOCK_PARTICLES;loop++)					
	{
		if (shockwave_particle[0].active)							
		{
			float x=shockwave_particle[0].x;						
			float y=-5;						
			float z=shockwave_particle[0].z+zoom;					

			//printf("%f %f %f\n", x,y,z);
			glColor4f(shockwave_particle[0].r,shockwave_particle[0].g,shockwave_particle[0].b,shockwave_particle[0].life);
			glBindTexture(GL_TEXTURE_2D,texture[0]);	
			glBegin(GL_TRIANGLE_STRIP);						
			    glTexCoord2d(1,1); glVertex3f(x+dx,y,z+dz); 
				glTexCoord2d(0,1); glVertex3f(x-dx,y,z+dz); 
				glTexCoord2d(1,0); glVertex3f(x+dx,y,z-dz); 
				glTexCoord2d(0,0); glVertex3f(x-dx,y,z-dz); 
			glEnd();			
			//printf("hrllo");
			dx +=0.5f;
			dz +=0.5f;
			shockwave_particle[0].x+=0;	//shockwave_particle[0].xi/(slowdown*500);;
			shockwave_particle[0].y+=0;	//shockwave_particle[0].yi/(slowdown*500);;
			shockwave_particle[0].z+=0;	//shockwave_particle[0].zi/(slowdown*500);;

			shockwave_particle[0].xi+=	shockwave_particle[0].xg;			
			shockwave_particle[0].yi+=	shockwave_particle[0].yg;			
			shockwave_particle[0].zi+=	shockwave_particle[0].zg;			
			shockwave_particle[0].life-= shockwave_particle[0].fade +0.020 ;		

			if (shockwave_particle[0].life<0.0f)					
			{
				/*particle[loop].life=1.0f;					
				particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	
				particle[loop].x=0.0f;						
				particle[loop].y=0.0f;						
				particle[loop].z=0.0f;						
				particle[loop].xi=xspeed+float((rand()%60)-32.0f);	
				particle[loop].yi=yspeed+float((rand()%60)-30.0f);	
				particle[loop].zi=float((rand()%60)-30.0f);	
				particle[loop].r=1;			
				particle[loop].g=103/255.0;			
				particle[loop].b=0;			*/
			}

			

			
		}
}



}
