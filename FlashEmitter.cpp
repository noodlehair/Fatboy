#include "FlashEmitter.h"
#include "LocalGraphicsLib.h"
#define MAX_FLASH_PARTICLES 500
particles flash_particle[MAX_FLASH_PARTICLES];	// Particle Array 

FlashEmitter :: FlashEmitter(const char* file_name){

	image = new ImageIO(file_name);
	slowdown=1000.0f;
	zoom=-40.0f;
	

}
FlashEmitter :: ~FlashEmitter(void){
delete [] image;
}

void FlashEmitter::flashEmitterInit(){
	//ImageIO* theflash_image = new ImageIO("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/flash.ppm");
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

	for (loop=0;loop<MAX_FLASH_PARTICLES;loop++)				
	{
		flash_particle[loop].active=true;								
		flash_particle[loop].life=1.0f;								
		flash_particle[loop].fade=float(rand()%100)/10000.0f +0.01;	
		flash_particle[loop].r=227/255.0;	
		flash_particle[loop].g=140.0/255.0;	;	
		flash_particle[loop].b=45/255.0;	
		flash_particle[loop].xi=float((rand()%50)-26.0f)*2;		
		flash_particle[loop].yi=float((rand()%50)-25.0f)*2;			
		flash_particle[loop].zi=float((rand()%50)-25.0f)*2;		
		flash_particle[loop].xg=0.0f;									
		flash_particle[loop].yg=0.0f;								
		flash_particle[loop].zg=0.0f;									
	}


}
void FlashEmitter::flashEmitterDisplay(){
for (loop=0;loop<MAX_FLASH_PARTICLES;loop++)					
	{
		if (flash_particle[loop].active)							
		{
			float x=flash_particle[loop].x;						
			float y=flash_particle[loop].y;						
			float z=flash_particle[loop].z+zoom;					

			
			glColor4f(flash_particle[loop].r,flash_particle[loop].g,flash_particle[loop].b,flash_particle[loop].life);
			glBindTexture(GL_TEXTURE_2D,texture[0]);	
			glBegin(GL_TRIANGLE_STRIP);						
			glTexCoord2d(1,1); glVertex3f(x+2.0f,y+2.0f,z); 
			glTexCoord2d(0,1); glVertex3f(x-2.0f,y+2.0f,z); 
			glTexCoord2d(1,0); glVertex3f(x+2.0f,y-2.0f,z); 
			glTexCoord2d(0,0); glVertex3f(x-2.0f,y-2.0f,z); 
			glEnd();			
			
			flash_particle[loop].x+=	flash_particle[loop].xi/(slowdown);
			flash_particle[loop].y+=	flash_particle[loop].yi/(slowdown);
			flash_particle[loop].z+=	flash_particle[loop].zi/(slowdown);

			flash_particle[loop].xi+=	flash_particle[loop].xg;			
			flash_particle[loop].yi+=	flash_particle[loop].yg;			
			flash_particle[loop].zi+=	flash_particle[loop].zg;			
			flash_particle[loop].life-=	flash_particle[loop].fade;		

			if (flash_particle[loop].life<0.0f)					
			{
				/*flash_particle[loop].life=1.0f;					
				flash_particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	
				flash_particle[loop].x=0.0f;						
				flash_particle[loop].y=0.0f;						
				flash_particle[loop].z=0.0f;						
				flash_particle[loop].xi=xspeed+float((rand()%60)-32.0f);	
				flash_particle[loop].yi=yspeed+float((rand()%60)-30.0f);	
				flash_particle[loop].zi=float((rand()%60)-30.0f);	
				flash_particle[loop].r=1;			
				flash_particle[loop].g=103/255.0;			
				flash_particle[loop].b=0;			*/
			}

			

			
		}
}



}
