

//#include <windows.h>				
#include <stdio.h>					
#include "ImageIO.h"
#include "LocalGraphicsLib.h"
#include "FlameEmitter.h"
#include "FlashEmitter.h"
#include "ShockwaveEmitter.h"
#include "DebrisEmitter.h"
				
bool	active=TRUE;				
					
//flame emitter variable
FlameEmitter *flameEmitter;

//flash emitter variables
FlashEmitter *flashEmitter;
 
//debris emitter variables
DebrisEmitter *debrisEmitter;

//shock emitter variables
ShockwaveEmitter *shockwaveEmitter;

float win_width = 768;
float win_height = 512;


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

int InitGL(GLvoid)										
{
	flameEmitter = new FlameEmitter("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/falme.ppm");
	flashEmitter = new FlashEmitter("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/flash.ppm");
	shockwaveEmitter = new ShockwaveEmitter("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/shock.ppm");
	debrisEmitter = new DebrisEmitter("C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/debris1.ppm",
		                                "C:/Users/Lanceton/Dropbox/Compsci 344 Final Project/Particle System Code/debris2.ppm");
	
	shockwaveEmitter->shockwaveEmitterInit();
	flashEmitter->flashEmitterInit();
	flameEmitter->flameEmitterInit();
	debrisEmitter->debrisEmitterInit();
	
	return TRUE;										
}

void  display(GLvoid)										
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
	glLoadIdentity();										
	shockwaveEmitter->shockwaveEmitterDisplay();	
	flashEmitter->flashEmitterDisplay();
	flameEmitter->flameEmitterDisplay();
    debrisEmitter->debrisEmitterDisplay();
									
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
