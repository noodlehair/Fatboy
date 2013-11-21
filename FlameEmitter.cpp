#include "FlameEmitter.h"
#include "LocalGraphicsLib.h"
#define	MAX_PARTICLES	2000
particles particle[MAX_PARTICLES];	// Particle Array 

FlameEmitter :: FlameEmitter(const char* file_name){

	image = new ImageIO(file_name);
	slowdown=2.0f;
	zoom=-20.0f;
    initFlag =false;

}
FlameEmitter :: ~FlameEmitter(void){
delete [] image;
}

void FlameEmitter::flameEmitterInit(){
	//ImageIO* the_image = new ImageIO("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/falme.ppm");
	LoadGLTextures(image, &texture[0]);							
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f,0.0f,0.0f,0.0f);					
	glClearDepth(1.0f);								
	glDisable(GL_DEPTH_TEST);							
	glEnable(GL_BLEND);									
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );					
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				
	glEnable(GL_TEXTURE_2D);							
	glBindTexture(GL_TEXTURE_2D,texture[0]);			
	float x=-1.1, y=1.1;
	for (loop=0;loop<MAX_PARTICLES;loop++)				
	{
		particle[loop].x =x;
		particle[loop].y =y;
		x+=0.001;
		y-=0.001;
		particle[loop].active=true;								
		particle[loop].life=1.0f;								
		particle[loop].fade=float(rand()%100)/1000.0f+0.01f;	
		particle[loop].r=1;	
		particle[loop].g=103/255.0;	
		particle[loop].b=0;	
		particle[loop].xi=float((rand()%50)-26.0f)*3;		
		particle[loop].yi=float((rand()%50)-25.0f)*3;		
		particle[loop].zi=float((rand()%50)-25.0f)*3;	
		particle[loop].xg=0.0f;									
		particle[loop].yg=0.0f;								
		particle[loop].zg=0.0f;									
	}

}
void FlameEmitter::flameEmitterDisplay(){

	if(!initFlag){
	flameEmitterInit();	
	 initFlag =true;
	}
for (loop=0;loop<MAX_PARTICLES;loop++)					
	{
		if (particle[loop].active)							
		{
			float x=particle[loop].x;						
			float y=particle[loop].y;						
			float z=particle[loop].z+zoom;					

			
			glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life);
			glBindTexture(GL_TEXTURE_2D,texture[0]);	
			glBegin(GL_TRIANGLE_STRIP);						
			    glTexCoord2d(1,1); glVertex3f(x+1.0f,y+1.0f,z); 
				glTexCoord2d(0,1); glVertex3f(x-1.0f,y+1.0f,z); 
				glTexCoord2d(1,0); glVertex3f(x+1.0f,y-1.0f,z); 
				glTexCoord2d(0,0); glVertex3f(x-1.0f,y-1.0f,z); 
			glEnd();			
			
			particle[loop].x+=particle[loop].xi/(slowdown*500);
			particle[loop].y+=particle[loop].yi/(slowdown*500);
			particle[loop].z+=particle[loop].zi/(slowdown*500);

			particle[loop].xi+=particle[loop].xg;			
			particle[loop].yi+=particle[loop].yg;			
			particle[loop].zi+=particle[loop].zg;			
			particle[loop].life-=particle[loop].fade;		

			if (particle[loop].life<0.0f)					
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
