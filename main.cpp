

//#include <windows.h>				
#include <stdio.h>					
#include "ImageIO.h"
#include "LocalGraphicsLib.h"
#include "ParticleSystem.h"
#include "object.h"
				
bool	active=TRUE;				
					
ParticleSystem *particleSystem;
ParticleSystem *particleSystem1;
ParticleSystem *particleSystem2;
object p(0.4,0.0, -5.0, -20.0, 1, 0.10, 0.31);
object p1(0.2,1.0, 2.0, -30.0, 1, 1, 0.31);
object p2(0.1,0.0, 3.0, -10.0, 1, 0.10, 1);
float win_width = 768;
float win_height = 512;


GLvoid reshape(int w, int h)		
{
	win_width = w;
	win_height = h;
			glViewport( 0, 0, w, h );
			glutPostRedisplay();					
}

int InitGL(GLvoid)										
{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glLoadIdentity();
		gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

		glShadeModel (GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
	
	particleSystem= new ParticleSystem();
	particleSystem1= new ParticleSystem();
	particleSystem2= new ParticleSystem();
	
	return TRUE;										
}

void explode(float rad, float x, float y, float z, ParticleSystem *ps){
	glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(rad,rad,rad);
	ps->display();
	glPopMatrix();
}

void  display(GLvoid)										
{
		glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			gluPerspective(45.f, win_width/win_height, .1f, 500.f);
			//glOrtho(-2, 2, -2, 2, 0.1, 500);
			glMatrixMode(GL_MODELVIEW);

			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glPolygonMode(GL_LINE, GL_FILL);
		
			if(p.hit){
				explode(p.radius, p.position_x,p.position_y,p.position_z,particleSystem);
			}else{
			p.draw();
			}
			
			if(p1.hit){
				explode(p1.radius, p1.position_x,p1.position_y,p1.position_z,particleSystem1);
			}else{
			p1.draw();
			}
			
			if(p2.hit){
				explode(p2.radius, p2.position_x,p2.position_y,p2.position_z,particleSystem2);
			}else{
			p2.draw();
			}
	//glPushMatrix();
	//glTranslatef(0,5, -30);
	//glScalef(0.1, 0.1, 0.1);
	//particleSystem1->display();
	////getchar();
	//glPopMatrix();
	//glPushMatrix();
	//glTranslatef(0,0, 0);
	//glScalef(0.5, 0.5, 0.5);
	//particleSystem2->display();
	////getchar();
	//glPopMatrix();
	
	
	glutSwapBuffers();							
}

void keyboard( unsigned char key, int x, int y ) {
    switch(key) {
        case 27: // Escape key
            exit(0);
            break;
		case 't':
            p.hit=true; 
			break;
		case 'r':
			p1.hit=true;
			break;
		case 'y':
			p2.hit=true;
			break;

             
    }
}

void idle( void ){
    
    glutPostRedisplay();
}

int main(int argc, char * argv[])
{
    
   glutInit( &argc, argv );

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
			glutInitWindowSize( win_width, win_height );
	
    glutCreateWindow( "Image" );
    
    InitGL();
	
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
    glutIdleFunc( idle );
    
        
    glutMainLoop();
    
    
   
    return 0;
}