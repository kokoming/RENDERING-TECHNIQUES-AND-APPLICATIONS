/******************************
4104056034 柯冠名 第6次作業 5/29
*******************************/

#define NDEBUG
#include "stdafx.h"
#include "GL\glew.h"
#include "GL\glut.h"
#include <stdlib.h>
#include "glm.h"

GLMmodel * model;

#define none 0
#define Mupward 3
#define Mdownward 4
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
int z = 20;			//z-axis
int y = 0;			//y-axis
int x = 0;			//x-axis
int angle_x = 0;
int angle_y = 0;
int angle_z = 0;
static int shoulder = 0, elbow = 0;
static int thumb = 0, finger1 = 0, finger2 = 0, finger3 = 0;
static int year = 0, day = 0;
int screen = 1; // Enable/Disable full screen
int fog = 1; // Enable/Disable fog
int aliasing = 1; // Enable/Disable anti-aliasing
int poly_offset = 0; // Enable/Disable polygon offset
int snipe = 0;
static int spinlight = 0;
int hand_x = 0, hand_y = 0, hand_z = 0;	//move hand

void planet(void) {
	day = (day + 5) % 360;
	year = (year + 1) % 360;
	spinlight = (spinlight + 1) % 360;	//rotate the light
	glutPostRedisplay();
}

void move() {
	if (Moving == Mforward) {
		glLoadIdentity();
		z--;
		gluLookAt(x, y, z, x, y, -50.0, 0.0, 1.0, 0.0);
		Moving = none;
	}
	else if (Moving == Mbackward) {
		glLoadIdentity();
		z++;
		gluLookAt(x, y, z, x, y, -50.0, 0.0, 1.0, 0.0);
		Moving = none;
	}
	else if (Moving == Mleft) {
		glLoadIdentity();
		x--;
		gluLookAt(x, y, z, x, y, -50.0, 0.0, 1.0, 0.0);
		Moving = none;
	}
	else if (Moving == Mright) {
		glLoadIdentity();
		x++;
		gluLookAt(x, y, z, x, y, -50.0, 0.0, 1.0, 0.0);
		Moving = none;
	}
	else if (Moving == Mupward) {
		glLoadIdentity();
		y++;
		gluLookAt(x, y, z, x, y, -50.0, 0.0, 1.0, 0.0);
		Moving = none;
	}
	else if (Moving == Mdownward) {
		glLoadIdentity();
		y--;
		gluLookAt(x, y, z, x, y, -50.0, 0.0, 1.0, 0.0);
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

void Draw_walls(void) {
	
	glBegin(GL_POLYGON);
		glVertex3f(-12.0, -10.0, -20.0);
		glVertex3f(-12.0, 25.0, -20.0);
		glVertex3f(25.0, 25.0, -20.0);
		glVertex3f(25.0, -10.0, -20.0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-12.0, -1.0, 10.0);
		glVertex3f(-12.0, -10.0, 10.0);
		glVertex3f(25.0, -10.0, 10.0);
		glVertex3f(25.0, -1.0, 10.0);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f(25.0, -10.0, -20.0);
		glVertex3f(25.0, 25.0, -20.0);
		glVertex3f(25.0, 25.0, 10.0);
		glVertex3f(25.0, -10.0, 10.0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-12.0, -10.0, -20.0);
		glVertex3f(-12.0, 25.0, -20.0);
		glVertex3f(-12.0, 25.0, 10.0);
		glVertex3f(-12.0, -10.0, 10.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 1.0);
		glVertex3f(-12.0, -10.0, -20.0);
		glVertex3f(25.0, -10.0, -20.0);
		glVertex3f(25.0, -10.0, 10.0);
		glVertex3f(-12.0, -10.0, 10.0);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
}

void display(void) 
{
//	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 1.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPushMatrix();
		GLfloat light_position2[] = { 8.0, 20.0, 0.0, 1.0 };
		glRotated((GLdouble)spinlight, 1.0, 0.0, 0.0);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
		glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	
	

	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

	if (snipe % 2 == 1) {
		gluLookAt(x, y, z-10, x, y, -50.0, 0.0, 1.0, 0.0);
	}
	else {
		gluLookAt(x, y, z, x, y, -50.0, 0.0, 1.0, 0.0);
	}
			
	move();
	glRotatef(angle_x, 1.0, 0.0, 0.0);
	glRotatef(angle_y, 0.0, 1.0, 0.0);
	glRotatef(angle_z, 0.0, 0.0, 1.0);
	
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	

	if (poly_offset % 2 == 1) {
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 1.0);
		Draw_walls();
		glDisable(GL_POLYGON_OFFSET_FILL);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Draw_walls();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else {
		Draw_walls();
	}

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glTranslatef(hand_x, hand_y, hand_z);
		//shoulder
		glTranslatef(-1.0, 0.0, 0.0);
		glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
		glTranslatef(1.0, 0.0, 0.0);
		glPushMatrix();
			glScalef(1.5, 0.5, 0.5);
			glutSolidSphere(1.0,40,50);
		glPopMatrix();

		//elbow
		glTranslatef(1.5, 0.0, 0.0);
		glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
		glTranslatef(1.0, 0.0, 0.0);
		glPushMatrix();
			glScalef(1.5, 0.5, 0.5);
			glutSolidSphere(1.0, 40, 50);
		glPopMatrix();
		
		//thumb-second
		glPushMatrix();
			glTranslatef(1.5, -0.4, 0.4);
			glRotatef(330, 0.0, 1.0, 0.0);
			glScalef(0.25, 0.1, 0.1);
			glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
			glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
			glutSolidSphere(1.0, 40, 50);
		glPopMatrix();
		//thumb-first
		glPushMatrix();
			glTranslatef(1.8, -0.4, 0.6);
			glRotatef(330, 0.0, 1.0, 0.0);
			glRotatef((GLfloat)thumb, 0.0, 0.0, 1.0);
			glTranslatef(0.2, 0.0, 0.0);
			glPushMatrix();
				glScalef(0.25, 0.1, 0.1);
				glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
				glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
				glutSolidSphere(1.0, 40, 50);
			glPopMatrix();
		glPopMatrix();

		//finger1-second
		glPushMatrix();
			glTranslatef(1.5, 0.4, 0.4);
			glRotatef(330, 0.0, 1.0, 0.0);
			glScalef(0.25, 0.1, 0.1);
			glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
			glutSolidSphere(1.0, 40, 50);			
		glPopMatrix();
		//finger1-first
		glPushMatrix();
			glTranslatef(1.8, 0.4, 0.6);
			glRotatef(330, 0.0, 1.0, 0.0);
			glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);
			glTranslatef(0.2, 0.0, 0.0);
			glPushMatrix();
				glScalef(0.25, 0.1, 0.1);
				glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
				glutSolidSphere(1.0, 40, 50);
			glPopMatrix();
		glPopMatrix();

		//finger2-second
		glPushMatrix();
			glTranslatef(1.5, 0.4, 0.0);
			glScalef(0.25, 0.1, 0.1);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
			glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
			glutSolidSphere(1.0, 40, 50);
		glPopMatrix();
		//finger2-first
		glPushMatrix();
			glTranslatef(1.8, 0.4, 0.0);
			glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);
			glTranslatef(0.2, 0.0, 0.0);
			glPushMatrix();
				glScalef(0.25, 0.1, 0.1);
				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
				glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
				glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
				glutSolidSphere(1.0, 40, 50);
			glPopMatrix();
		glPopMatrix();

		//finger3-second
		glPushMatrix();
			glTranslatef(1.5, 0.4, -0.4);
			glRotatef(30, 0.0, 1.0, 0.0);
			glScalef(0.25, 0.1, 0.1);
			glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
			glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
			glutSolidSphere(1.0, 40, 50);
		glPopMatrix();
		//finger3-first
		glPushMatrix();
			glTranslatef(1.8, 0.4, -0.6);
			glRotatef(30, 0.0, 1.0, 0.0);
			glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);
			glTranslatef(0.2, 0.0, 0.0);
			glPushMatrix();
				glScalef(0.25, 0.1, 0.1);
				glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
				glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
				glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
				glutSolidSphere(1.0, 40, 50);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	//planets
	glPushMatrix();
		glTranslatef(0.0, 8.0, 0.0);
		glColor3f(1.0, 0.0, 0.0);
		glutSolidSphere(1.0, 20, 16);   //sun	
		glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
		glTranslatef(2.0, 0.0, 0.0);
		glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
		glColor3f(0.0, 0.0, 1.0);
		glutSolidSphere(0.2, 10, 8);    //planet
	//	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glutIdleFunc(planet);

	glColor3f(0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(5.0, 0.0, 11.0);
	glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(5.0, 0.0, 0.0);
	glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
	glTranslatef(5.0, 0.0, 0.0);
	glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
}

void init(void) 
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	printf("press '1' to use 'Rotate the upper arm'\n");
	printf("press '2' to use 'Rotate the lower arm'\n");
	printf("press '3' to use 'Rotate the first sections of the fingers'\n");
	printf("press '4' to use 'Rotate the thumb'\n");
	printf("press 'w' to use 'Move forward'\n");
	printf("press 'a' to use 'Move left'\n");
	printf("press 's' to use 'Move right'\n");
	printf("press 'd' to use 'Move backward'\n");
	printf("press 'e' to use 'Move upward'\n");
	printf("press 'q' to use 'Move downward'\n");
	printf("Mouse right click to rotate the scene by x-axis\n");
	printf("Mouse left click to rotate the scene by z-axis\n");
	printf("Mouse middle click to rotate the scene by y-axis\n");
	printf("press 'y' to move hand forward\n");
	printf("press 'g' to move hand left\n");
	printf("press 'h' to move hand backward\n");
	printf("press 'j' to move hand right\n");
	printf("press 'u' to move hand up\n");
	printf("press 't' to move hand down\n");
	printf("press 'z' to Enable/Disable full screen\n");
	printf("press 'b' to snipe your target\n");
	printf("press 'c' to Enable/Disable anti-aliasing\n");
	printf("press 'f' to Enable/Disable fog your scene\n");
	printf("press 'p' to offset your polygon\n");

	
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
		case 'E':
		case 'e':
			Moving = Mupward;
			glutPostRedisplay();
			break;
		case 'Q':
		case 'q':
			Moving = Mdownward;
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
		case 'Z':
		case 'z':
			if (screen % 2 == 1) {
				glutFullScreen();
			}
			else {
				glutReshapeWindow(800, 600);
				glutPositionWindow(100, 100);
			}
			screen++;
		case 'Y':
		case 'y':
			if (hand_z > -19) {
				hand_z--;
			}
			glutPostRedisplay();
			break;
		case 'G':
		case 'g':
			if (hand_x > -11) {
				hand_x--;
			}		
			glutPostRedisplay();
			break;
		case 'H':
		case 'h':
			if (hand_z < 9) {
				hand_z++;
			}		
			glutPostRedisplay();
			break;
		case 'J':
		case 'j':
			if (hand_x < 20) {
				hand_x++;
			}		
			glutPostRedisplay();
			break;
		case 'U':
		case 'u':
			hand_y++;
			glutPostRedisplay();
			break;
		case 'T':
		case 't':
			if (hand_y > -10) {
				hand_y--;
			}		
			glutPostRedisplay();
			break;
		case 'F':
		case 'f':
			if (fog % 2 == 1) {
				glEnable(GL_FOG);
				{
					GLfloat fogColor[4] = { 0.5, 0.5, 0.5, 1.0 };
					glFogi(GL_FOG_MODE, GL_EXP);
					glFogfv(GL_FOG_COLOR, fogColor);
					glFogf(GL_FOG_DENSITY, 0.1);
					glHint(GL_FOG_HINT, GL_DONT_CARE);
					glFogf(GL_FOG_START, 0.1);
					glFogf(GL_FOG_END, 0.5);
				}
				glClearColor(0.0, 0.0, 0.0, 0.0);
			}
			else {
				glDisable(GL_FOG);
			}
			fog++;
			glutPostRedisplay();
			break;
		case 'C':
		case 'c':
			if (aliasing % 2 == 1) {
				glEnable(GL_MULTISAMPLE);
			}
			else {
				glDisable(GL_MULTISAMPLE);
			}
			aliasing++;
			glutPostRedisplay();
			break;
		case 'P':
		case 'p':
			poly_offset++;
			glutPostRedisplay();
			break;
		case 'B':
		case 'b':
			
			snipe++;
			glutPostRedisplay();
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glewInit();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	model = glmReadOBJ("Bison.obj");
	glmScale(model, 2);
	//glmUnitize(model);
	glmFacetNormals(model);
	glmVertexNormals(model, 0);
	
	glutMainLoop();
	return 0;
}
