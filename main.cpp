

//#include <windows.h>				
#include <stdio.h>					
#include "ImageIO.h"
#include "LocalGraphicsLib.h"
#include "FlameEmitter.h"
#include "FlashEmitter.h"
//#define MAX_FLASH_PARTICLES 500
#define MAX_DEBRIS_PARTICLES 2000
#define MAX_SHOCK_PARTICLES 1


				
bool	active=TRUE;				
					
//flame emitter variable

FlameEmitter *flameEmitter;

//flash emitter variables
FlashEmitter *flashEmitter;
 
//debris emitter variables
float	debris_slowdown=40.0f;				
//float	xspeed;						
//float	yspeed;						
float	debris_zoom=-100.0f;				

GLuint	debris_loop;						
GLuint	debris_col;						
GLuint	debris_delay;						
GLuint	debris_texture[2];	


//shock emitter variables
float	shock_slowdown=1000.0f;				
//float	xspeed;						
//float	yspeed;						
float	shock_zoom=-100.0f;				

GLuint	shock_loop;						
GLuint	shock_col;						
GLuint	shock_delay;						
GLuint	shock_texture[1];	
float dx=2.0f*20;   // shockwave x increment size 
float dz=2.0f*20;   // shockwave z increment size
float win_width = 768;
float win_height = 512;


particles debris_particle[MAX_DEBRIS_PARTICLES];
particles shock_particle[MAX_SHOCK_PARTICLES];

GLvoid reshape(GLsizei width, GLsizei height)		
{
	if (height==0)										
	{
		height=1;										
	}

	glViewport(0,0,width,height);					

	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();									

	
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,200.0f);

	glMatrixMode(GL_MODELVIEW);							
	glLoadIdentity();									
}

void debrisEmitterInit(){
	ImageIO* thedebris_image1 = new ImageIO("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/debris1.ppm");
	LoadGLTextures(thedebris_image1, &debris_texture[0]);							
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f,0.0f,0.0f,0.0f);					
	glClearDepth(1.0f);								
	glDisable(GL_DEPTH_TEST);							
	glEnable(GL_BLEND);									
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				
	glEnable(GL_TEXTURE_2D);							
	glBindTexture(GL_TEXTURE_2D,debris_texture[0]);			

	for (debris_loop=0;debris_loop<MAX_DEBRIS_PARTICLES/2;debris_loop++)				
	{
		debris_particle[debris_loop].active=true;								
		debris_particle[debris_loop].life=1.0f;								
		debris_particle[debris_loop].fade=float(rand()%100)/10000.0f +0.01;	
		debris_particle[debris_loop].r=227/255.0;	
		debris_particle[debris_loop].g=140.0/255.0;	;	
		debris_particle[debris_loop].b=45/255.0;	
		debris_particle[debris_loop].xi=float((rand()%50)-26.0f)*2;		
		debris_particle[debris_loop].yi=float((rand()%50)-25.0f)*2;			
		debris_particle[debris_loop].zi=float((rand()%50)-25.0f)*2;		
		debris_particle[debris_loop].xg=0.0f;									
		debris_particle[debris_loop].yg=0.0f;								
		debris_particle[debris_loop].zg=0.0f;									
	}
	ImageIO* thedebris_image2 = new ImageIO("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/debris2.ppm");
	LoadGLTextures(thedebris_image2, &debris_texture[1]);							
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f,0.0f,0.0f,0.0f);					
	glClearDepth(1.0f);								
	glDisable(GL_DEPTH_TEST);							
	glEnable(GL_BLEND);									
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				
	glEnable(GL_TEXTURE_2D);							
	glBindTexture(GL_TEXTURE_2D,debris_texture[1]);			

	for (debris_loop=MAX_DEBRIS_PARTICLES/2;debris_loop<MAX_DEBRIS_PARTICLES;debris_loop++)				
	{
		debris_particle[debris_loop].active=true;								
		debris_particle[debris_loop].life=1.0f;								
		debris_particle[debris_loop].fade=float(rand()%100)/1000.0f;	
		debris_particle[debris_loop].r=227/255.0;	
		debris_particle[debris_loop].g=140.0/255.0;	;	
		debris_particle[debris_loop].b=45/255.0;	
		debris_particle[debris_loop].xi=float((rand()%50)-26.0f)*2;		
		debris_particle[debris_loop].yi=float((rand()%50)-25.0f)*2;			
		debris_particle[debris_loop].zi=float((rand()%50)-25.0f)*2;		
		debris_particle[debris_loop].xg=0.0f;									
		debris_particle[debris_loop].yg=0.0f;								
		debris_particle[debris_loop].zg=0.0f;									
	}
}




void shockEmitterInit(){
	ImageIO* theshock_image = new ImageIO("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/shock.ppm");
	LoadGLTextures(theshock_image, &shock_texture[0]);							
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f,0.0f,0.0f,0.0f);					
	glClearDepth(1.0f);								
	glDisable(GL_DEPTH_TEST);							
	glEnable(GL_BLEND);									
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				
	glEnable(GL_TEXTURE_2D);							
	glBindTexture(GL_TEXTURE_2D,shock_texture[0]);			

	for (shock_loop=0;shock_loop<MAX_SHOCK_PARTICLES;shock_loop++)				
	{
		shock_particle[shock_loop].active=true;								
		shock_particle[shock_loop].life=1.0f;								
		shock_particle[shock_loop].fade=float(rand()%100)/100000.0f;	
		shock_particle[shock_loop].r=1.0;	
		shock_particle[shock_loop].g=103/255.0;	;	
		shock_particle[shock_loop].b=0.0;	
		shock_particle[shock_loop].xi=float((rand()%50)-26.0f)*15;		
		shock_particle[shock_loop].yi=float((rand()%50)-25.0f)*15;			
		shock_particle[shock_loop].zi=float((rand()%50)-25.0f)*15;		
		shock_particle[shock_loop].xg=0.0f;									
		shock_particle[shock_loop].yg=0.0f;								
		shock_particle[shock_loop].zg=0.0f;									
	}



}

int InitGL(GLvoid)										
{
	flameEmitter = new FlameEmitter("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/falme.ppm");
	flashEmitter = new FlashEmitter("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/flash.ppm");
	shockEmitterInit();
	flashEmitter->flashEmitterInit();
	flameEmitter->flameEmitterInit();
	debrisEmitterInit();
	
	return TRUE;										
}






void debrisEmitterDisplay(){
for (debris_loop=0;debris_loop<MAX_DEBRIS_PARTICLES/2;debris_loop++)					
	{
		if (debris_particle[debris_loop].active)							
		{
			float x=debris_particle[debris_loop].x;						
			float y=debris_particle[debris_loop].y;						
			float z=debris_particle[debris_loop].z+debris_zoom;					

			
			glColor4f(debris_particle[debris_loop].r,debris_particle[debris_loop].g,debris_particle[debris_loop].b,debris_particle[debris_loop].life);
			glBindTexture(GL_TEXTURE_2D,debris_texture[0]);	
			glBegin(GL_TRIANGLE_STRIP);						
			    glTexCoord2d(1,1); glVertex3f(x+1.0f,y+1.0f,z); 
				glTexCoord2d(0,1); glVertex3f(x-1.0f,y+1.0f,z); 
				glTexCoord2d(1,0); glVertex3f(x+1.0f,y-1.0f,z); 
				glTexCoord2d(0,0); glVertex3f(x-1.0f,y-1.0f,z); 
			glEnd();			
			
			debris_particle[debris_loop].x+=	debris_particle[debris_loop].xi/(debris_slowdown);
			debris_particle[debris_loop].y+=	debris_particle[debris_loop].yi/(debris_slowdown);
			debris_particle[debris_loop].z+=	debris_particle[debris_loop].zi/(debris_slowdown);

			debris_particle[debris_loop].xi+=	debris_particle[debris_loop].xg;			
			debris_particle[debris_loop].yi+=	debris_particle[debris_loop].yg;			
			debris_particle[debris_loop].zi+=	debris_particle[debris_loop].zg;			
			debris_particle[debris_loop].life-=	debris_particle[debris_loop].fade;			
		}
}
for (debris_loop=MAX_DEBRIS_PARTICLES/2;debris_loop<MAX_DEBRIS_PARTICLES;debris_loop++)					
	{
		if (debris_particle[debris_loop].active)							
		{
			float x=debris_particle[debris_loop].x;						
			float y=debris_particle[debris_loop].y;						
			float z=debris_particle[debris_loop].z+debris_zoom;					

			
			glColor4f(debris_particle[debris_loop].r,debris_particle[debris_loop].g,debris_particle[debris_loop].b,debris_particle[debris_loop].life);
			glBindTexture(GL_TEXTURE_2D,debris_texture[1]);	
			glBegin(GL_TRIANGLE_STRIP);						
			    glTexCoord2d(1,1); glVertex3f(x+1.0f,y+1.0f,z); 
				glTexCoord2d(0,1); glVertex3f(x-1.0f,y+1.0f,z); 
				glTexCoord2d(1,0); glVertex3f(x+1.0f,y-1.0f,z); 
				glTexCoord2d(0,0); glVertex3f(x-1.0f,y-1.0f,z); 
			glEnd();			
			
			debris_particle[debris_loop].x+=	debris_particle[debris_loop].xi/(debris_slowdown);
			debris_particle[debris_loop].y+=	debris_particle[debris_loop].yi/(debris_slowdown);
			debris_particle[debris_loop].z+=	debris_particle[debris_loop].zi/(debris_slowdown);

			debris_particle[debris_loop].xi+=	debris_particle[debris_loop].xg;			
			debris_particle[debris_loop].yi+=	debris_particle[debris_loop].yg;			
			debris_particle[debris_loop].zi+=	debris_particle[debris_loop].zg;			
			debris_particle[debris_loop].life-=	debris_particle[debris_loop].fade;			
		}
}
}










void shockEmitterDisplay(){
	
	
for (shock_loop=0;shock_loop<1;shock_loop++)					
	{
		if (shock_particle[0].active)							
		{
			float x=shock_particle[0].x;						
			float y=-5;						
			float z=shock_particle[0].z+shock_zoom;					

			//printf("%f %f %f\n", x,y,z);
			glColor4f(shock_particle[0].r,shock_particle[0].g,shock_particle[0].b,shock_particle[0].life);
			glBindTexture(GL_TEXTURE_2D,shock_texture[0]);	
			glBegin(GL_TRIANGLE_STRIP);						
			    glTexCoord2d(1,1); glVertex3f(x+dx,y,z+dz); 
				glTexCoord2d(0,1); glVertex3f(x-dx,y,z+dz); 
				glTexCoord2d(1,0); glVertex3f(x+dx,y,z-dz); 
				glTexCoord2d(0,0); glVertex3f(x-dx,y,z-dz); 
			glEnd();			
			//printf("hrllo");
			dx +=0.5f;
			dz +=0.5f;
			shock_particle[0].x+=0;	//shock_particle[0].xi/(slowdown*500);;
			shock_particle[0].y+=0;	//shock_particle[0].yi/(slowdown*500);;
			shock_particle[0].z+=0;	//shock_particle[0].zi/(slowdown*500);;

			shock_particle[0].xi+=	shock_particle[0].xg;			
			shock_particle[0].yi+=	shock_particle[0].yg;			
			shock_particle[0].zi+=	shock_particle[0].zg;			
			shock_particle[0].life-= shock_particle[0].fade +0.020 ;		

			if (shock_particle[0].life<0.0f)					
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
void  display(GLvoid)										
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
	glLoadIdentity();										
	shockEmitterDisplay();	
	flashEmitter->flashEmitterDisplay();
	flameEmitter->flameEmitterDisplay();
    debrisEmitterDisplay();
									
}

void idle( void ){
    
    glutPostRedisplay();
}

int main(int argc, char * argv[])
{
    
    glutInit( &argc, argv );
    
    glutInitDisplayMode( GLUT_RGB );
    glutInitWindowSize( win_width, win_height );
	
    glutCreateWindow( "Image" );
    
    InitGL();
	
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );

    glutIdleFunc( idle );
    
        
    glutMainLoop();
    
    
   
    return 0;
}
