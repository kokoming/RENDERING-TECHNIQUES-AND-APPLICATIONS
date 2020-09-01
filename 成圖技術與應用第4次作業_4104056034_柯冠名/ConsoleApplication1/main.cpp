/******************************
4104056034 柯冠名 第4次作業 5/1
*******************************/

#define NDEBUG
#include "stdafx.h"
#include "GL\glew.h"
#include "GL\glut.h"
#include <stdlib.h>

#define none 0
#define Mforward 5
#define Mbackward 6
#define Mleft 7
#define Mright 8
#define Rotate_X 9
#define Rotate_Y 10
#define Rotate_Z 11

int Method = none;	//check event
int Moving = none;	//keyboard event
int Click = none;   //mouse event
int z = 10;			//z-axis
int x = 0;			//x-axis
int angle_x = 0;
int angle_y = 0;
int angle_z = 0;
static int shoulder = 0, elbow = 0;
static int thumb = 0, finger1 = 0, finger2 = 0, finger3 = 0;
static int year = 0, day = 0;

void planet(void) {
	day = (day + 5) % 360;
	year = (year + 1) % 360;
	glutPostRedisplay();
}

void move() {
	if (Moving == Mforward) {
		glLoadIdentity();
		z--;
		gluLookAt(0.0, 0.0, z, x, 0.0, 0.0, 0.0, 1.0, 0.0);
		Moving = none;
	}
	else if (Moving == Mbackward) {
		glLoadIdentity();
		z++;
		gluLookAt(0.0, 0.0, z, x, 0.0, 0.0, 0.0, 1.0, 0.0);
		Moving = none;
	}
	else if (Moving == Mleft) {
		glLoadIdentity();
		x--;
		gluLookAt(0.0, 0.0, z, x, 0.0, 0.0, 0.0, 1.0, 0.0);
		Moving = none;
	}
	else if (Moving == Mright) {
		glLoadIdentity();
		x++;
		gluLookAt(0.0, 0.0, z, x, 0.0, 0.0, 0.0, 1.0, 0.0);
		Moving = none;
	}

	if (Click == Rotate_X) {
		angle_x += 30;
		angle_x %= 360;
		Click = none;
	}
	else if (Click == Rotate_Y) {
		angle_y += 30;
		angle_y %= 360;
		Click = none;
	}
	else if (Click == Rotate_Z) {	
		angle_z += 30;
		angle_z %= 360;
		Click = none;
	}
}

void display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, z, x, 0.0, 0.0, 0.0, 1.0, 0.0);		
	move();
	glRotatef(angle_x, 1.0, 0.0, 0.0);
	glRotatef(angle_y, 0.0, 1.0, 0.0);
	glRotatef(angle_z, 0.0, 0.0, 1.0);

	glPushMatrix();
		//shoulder
		glTranslatef(-1.0, 0.0, 0.0);
		glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
		glTranslatef(1.0, 0.0, 0.0);
		glPushMatrix();
			glScalef(2.5, 1.0, 1.0);
			glutWireCube(1.0);
		glPopMatrix();

		//elbow
		glTranslatef(1.5, 0.0, 0.0);
		glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
		glTranslatef(1.0, 0.0, 0.0);
		glPushMatrix();
			glScalef(2.5, 1.0, 1.0);
			glutWireCube(1.0);
		glPopMatrix();

		//thumb-second
		glPushMatrix();
			glTranslatef(1.5, -0.4, 0.4);
			glScalef(0.5, 0.1, 0.25);
			glutWireCube(1.0);
		glPopMatrix();
		//thumb-first
		glPushMatrix();
			glTranslatef(1.8, -0.4, 0.4);
			glRotatef((GLfloat)thumb, 0.0, 0.0, 1.0);
			glTranslatef(0.2, 0.0, 0.0);
			glPushMatrix();
				glScalef(0.5, 0.1, 0.25);
				glutWireCube(1.0);
			glPopMatrix();
		glPopMatrix();

		//finger1-second
		glPushMatrix();
			glTranslatef(1.5, 0.4, 0.4);
			glScalef(0.5, 0.1, 0.25);
			glutWireCube(1.0);
		glPopMatrix();
		//finger1-first
		glPushMatrix();
			glTranslatef(1.8, 0.4, 0.4);
			glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);
			glTranslatef(0.2, 0.0, 0.0);
			glPushMatrix();
				glScalef(0.5, 0.1, 0.25);
				glutWireCube(1.0);
			glPopMatrix();
		glPopMatrix();

		//finger2-second
		glPushMatrix();
			glTranslatef(1.5, 0.4, 0.0);
			glScalef(0.5, 0.1, 0.25);
			glutWireCube(1.0);
		glPopMatrix();
		//finger2-first
		glPushMatrix();
			glTranslatef(1.8, 0.4, 0.0);
			glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);
			glTranslatef(0.2, 0.0, 0.0);
			glPushMatrix();
				glScalef(0.5, 0.1, 0.25);
				glutWireCube(1.0);
			glPopMatrix();
		glPopMatrix();

		//finger3-second
		glPushMatrix();
			glTranslatef(1.5, 0.4, -0.4);
			glScalef(0.5, 0.1, 0.25);
			glutWireCube(1.0);
		glPopMatrix();
		//finger3-first
		glPushMatrix();
			glTranslatef(1.8, 0.4, -0.4);
			glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);
			glTranslatef(0.2, 0.0, 0.0);
			glPushMatrix();
				glScalef(0.5, 0.1, 0.25);
				glutWireCube(1.0);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	//planets
	glPushMatrix();
		glTranslatef(0.0, 3.0, 0.0);
		glutWireSphere(1.0, 20, 16);   //sun	
		glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
		glTranslatef(2.0, 0.0, 0.0);
		glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
		glutWireSphere(0.2, 10, 8);    //planet
	glPopMatrix();

	glutIdleFunc(planet);

	glutSwapBuffers();
	glFlush();
}

void init(void) 
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	printf("press '1' to use 'Rotate the upper arm'\n");
	printf("press '2' to use 'Rotate the lower arm'\n");
	printf("press '3' to use 'Rotate the first sections of the fingers'\n");
	printf("press '4' to use 'Rotate the thumb'\n");
	printf("press 'w' to use 'Move forward'\n");
	printf("press 'a' to use 'Move left'\n");
	printf("press 's' to use 'Move right'\n");
	printf("press 'd' to use 'Move backward'\n");
	printf("Mouse right click to rotate the scene by x-axis\n");
	printf("Mouse left click to rotate the scene by z-axis\n");
	printf("Mouse middle click to rotate the scene by y-axis\n");
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5, 1.0, -0.5, 1.0, 1.0, 100.0);		
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
		case 49:
			shoulder = (shoulder + 5) % 360;
			glutPostRedisplay();
			break;
		case 50:
			elbow = (elbow + 5) % 360;
			glutPostRedisplay();
			break;
		case 51:
			finger1 = (finger1 + 5) % 360;
			finger2 = (finger2 + 5) % 360;
			finger3 = (finger3 + 5) % 360;
			glutPostRedisplay();
			break;
		case 52:
			thumb = (thumb + 5) % 360;
			glutPostRedisplay();
			break;
		case 'W':
		case 'w':
			Moving = Mforward;
			glutPostRedisplay();
			break;
		case 'A':
		case 'a':
			Moving = Mleft;
			glutPostRedisplay();
			break;
		case 'S':
		case 's':
			Moving = Mbackward;
			glutPostRedisplay();
			break;
		case 'D':
		case 'd':
			Moving = Mright;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) {
				Click = Rotate_Z;
			}	
			glutPostRedisplay();
			break;
		case GLUT_MIDDLE_BUTTON:
			if (state == GLUT_DOWN) {
				Click = Rotate_Y;
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN) {
				Click = Rotate_X;
			}
			break;
		default:
			break;
	}
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glewInit();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
