//
//  main.cpp
//  SolarSystem
//  Kangyi Zhang
//
 
#include <iostream>
#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include "object.h"
#include "player.h"
#include <glut.h>

#include <stdio.h>                                        
#include "ImageIO.h"
#include "LocalGraphicsLib.h"
#include "ParticleSystem.h"
using namespace std;


float win_width = 1024;
float win_height = 1024;

float angle;

bool shadeType = false;
bool lighting = false;
bool pressTracker = false;
static float lookAtLocationX = 0, lookAtLocationY = 0, lookAtLocationZ = 10;

float rotateA = 0;

bool shoot_ball;
float ball_x_distance, ball_y_distance, ball_z_distance;

bool ifDraw;
bool ifDraw1;
bool ifDraw2;
bool ifDraw3;
bool ifDraw4;
bool ifDraw5;
bool ifDraw6;
bool ifDraw7;

bool ifExplostion;
bool ifExplostion1;
bool ifExplostion2;
bool ifExplostion3;
bool ifExplostion4;
bool ifExplostion5;
bool ifExplostion6;
bool ifExplostion7;

bool  active = true;

ParticleSystem *p;
ParticleSystem *p1;
ParticleSystem *p2;
ParticleSystem *p3;
ParticleSystem *p4;
ParticleSystem *p5;
ParticleSystem *p6;
ParticleSystem *p7;


void init(void){
	angle = 0;

	glEnable(GL_LIGHT0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glLoadIdentity();
	gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	{
		GLfloat sun_light_position[] = { lookAtLocationX, lookAtLocationY, lookAtLocationZ, 1.0f };
		GLfloat sun_light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}

	glEnable(GL_COLOR_MATERIAL);

	ball_x_distance = lookAtLocationX;
	ball_y_distance = lookAtLocationY;
	ball_z_distance = lookAtLocationZ - 6;

	ifDraw = true;
	ifDraw1 = true;
	ifDraw2 = true;
	ifDraw3 = true;
	ifDraw4 = true;
	ifDraw5 = true;
	ifDraw6 = true;
	ifDraw7 = true;
	shoot_ball = false;
	ifExplostion = true;
	ifExplostion1 = true;
	ifExplostion2 = true;
	ifExplostion3 = true;
	ifExplostion4 = true;
	ifExplostion5 = true;
	ifExplostion6 = true;
	ifExplostion7 = true;

	p = new ParticleSystem();
	p1 = new ParticleSystem();
	p2 = new ParticleSystem();
	p3 = new ParticleSystem();
	p4 = new ParticleSystem();
	p5 = new ParticleSystem();
	p6 = new ParticleSystem();
	p7= new ParticleSystem();


}


void ball(void){

	GLfloat mat_ambient[] = { 1, 1, 1, 1.0f };
	GLfloat mat_diffuse[] = { 1, 1, 1, 1.0f };
	GLfloat mat_specular[] = { 1, 1, 1, 1.0f };
	GLfloat mat_emission[] = { 0, 0, 0, 1.0f };
	GLfloat mat_shininess = 50;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();

	glColor3f(1, 0, 0);

	glutSolidSphere(0.15, 20, 12);
	glPopMatrix();
}

void ball_move(void){
	if (!shoot_ball){
		ball_z_distance = lookAtLocationZ - 6;
	}
	if (shoot_ball){
		if (ball_z_distance - lookAtLocationZ>-15){
			ball_z_distance -= 0.065;
		}
		else {
			shoot_ball = false;
			ball_z_distance = lookAtLocationZ;
		}
	}
}


void idle(void){
	angle += 0.08;
	ball_move();
	glutPostRedisplay();
}

void beingShoot(float x, float y, float z, float radius, bool* ifex, ParticleSystem* ps){
	if (*ifex){
	glPushMatrix();
	//glTranslatef(0,0,-15);
	glTranslatef(x, y, z);
	//glRotatef(5,1,0,0);
	glScalef(radius / 5, radius / 5, radius / 5);
	ps->display();
	glPopMatrix();
	if (ps->flameEmitter->destroy){
		delete ps;
		*ifex = false;
	}
	}
	
	
	
}

void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.f, win_width / win_height, .1f, 500.f);
	glMatrixMode(GL_MODELVIEW);

	//beingShoot();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(lookAtLocationX, lookAtLocationY, lookAtLocationZ, lookAtLocationX, lookAtLocationY, -100, 0, 1, 0);
	glPolygonMode(GL_LINE, GL_FILL);

	player spaceShip(2.0);
	spaceShip.draw(lookAtLocationX, lookAtLocationY, lookAtLocationZ);

	glPushMatrix();

	glRotatef(rotateA, 0, 1, 0);

	//glTranslatef(lookAtLocationX, 0, lookAtLocationZ);
	if (ifDraw){
		object sun(0.5, 0, 0, -15, 0.95, 0.63, 0);
		sun.draw(0, 0, 0, 0.5, 0, lookAtLocationX, lookAtLocationY, ball_z_distance, &ifDraw, rotateA, lookAtLocationY,shoot_ball);
	}
	else
		beingShoot(0, 0, -15, 0.5, &ifExplostion,p);
	if (ifDraw1){
		object planet1(0.1, 0.8, 0, -15, 0.8, 0.1, 0.21);
		planet1.draw(1, 0, 0, 0.3, 20, lookAtLocationX, lookAtLocationY, ball_z_distance, &ifDraw1, rotateA, lookAtLocationY,shoot_ball);
	}
	else
		beingShoot(0.8, 0, -15, 0.1, &ifExplostion1,p1);
	if (ifDraw2){
		object planet2(0.15, 1.2, 0, -15, 0, 1.0, 0.41);
		planet2.draw(0, 1, 0, 0, 30, lookAtLocationX, lookAtLocationY, ball_z_distance, &ifDraw2, rotateA, lookAtLocationY,shoot_ball);
	}
	else
		beingShoot(1.2, 0, -15, 0.15, &ifExplostion2,p2);
	if (ifDraw3){
		object planet3(0.18, 0, 1.8, -15, .5, 0, 0);
		planet3.draw(0, 0, 1, 0, 40, lookAtLocationX, lookAtLocationY, ball_z_distance, &ifDraw3, rotateA, lookAtLocationY,shoot_ball);
	}
	else
		beingShoot(0, 1.8, -15, 0.18, &ifExplostion3,p3);
	if (ifDraw4){
		object planet4(0.22, 0.5, 0.5, -12.5, 0, 0.2, 0.321);
		planet4.draw(1, 0, 1, 0, 40, lookAtLocationX, lookAtLocationY, ball_z_distance, &ifDraw4, rotateA, lookAtLocationY,shoot_ball);
	}
	else
		beingShoot(0.5, 0.5, -12.5, 0.22, &ifExplostion4,p4);
	if (ifDraw5){
		object planet5(0.25, -3.2, 0, -14, 0, 0.4, 0.21);
		planet5.draw(0, 1, 1, 0, 40, lookAtLocationX, lookAtLocationY, ball_z_distance, &ifDraw5, rotateA, lookAtLocationY,shoot_ball);
	}
	else
		beingShoot(-3.2, 0, -14, 0.25, &ifExplostion5,p5);
	if (ifDraw6){
		object planet6(0.3, 4.0, -2, -15, 0, 0.10, 0.31);
		planet6.draw(0.5, 0.5, 0.5, 0.5, 40, lookAtLocationX, lookAtLocationY, ball_z_distance, &ifDraw6, rotateA, lookAtLocationY,shoot_ball);
	}
	else
		beingShoot(4.0, -2, -15, 0.3, &ifExplostion6,p6);
	if (ifDraw7){
		object planet7(0.4, 1, 2, -5, 0.2, 0, 0.21);
		planet7.draw(1, 1, 1, 0, 50, lookAtLocationX, lookAtLocationY, ball_z_distance, &ifDraw7, rotateA, lookAtLocationY,shoot_ball);
	}
	else
		beingShoot(1, 2, -5, 0.4, &ifExplostion7,p7);
	//glTranslatef(-lookAtLocationX, 0, -lookAtLocationZ);

	glPopMatrix();

	glPushMatrix();

	glTranslatef(lookAtLocationX, lookAtLocationY, ball_z_distance);

	if (shoot_ball)//>0.05&&lookAtLocationZ-6-ball_z_distance<-0.05)
		ball();

	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	win_width = w;
	win_height = h;
	glViewport(0, 0, w, h);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // Escape key
		exit(0);
		break;

	case 'a': lookAtLocationX -= 0.1; break;
	case 'd': lookAtLocationX += 0.1; break;
	case 'e': lookAtLocationY -= 0.1; break;
	case 'q': lookAtLocationY += 0.1; break;
	case 'w': lookAtLocationZ -= 0.1; break;
	case 's': lookAtLocationZ += 0.1; break;
	case 'i': rotateA -= 0.5; break;
	case 'o': rotateA += 0.5; break;
	/*case 't':{
				 shoot_ball = true;
	}*/

	}
}
void onMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
	shoot_ball = true;
	}
}

void onMotion(int x, int y) {

}
int main(int argc, char * argv[])
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(win_width, win_height);

	glutCreateWindow("Material World");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}
