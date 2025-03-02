/******************************
4104056034 柯冠名 第2次作業 4/7
*******************************/

#define NDEBUG
#include "stdafx.h"
#include "GL\glew.h"
#include "GL\glut.h"
#include <stdlib.h>

#define none 0
#define DrawArrays 1
#define DrawElements 2
#define MultiDrawArrays 3
#define MultiDrawElements 4

int Method = none;

void setupPointers_polygons(void); //polygon vertex array
void setupPointers_triangles(void); //triangle vertex array

static GLuint num[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,
101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,
201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,
301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,
401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426
};

void setupInterleave(void)
{
	static GLfloat intertwined[] =
	{   1.0, 0.2, 1.0, 0.835, 0.66, 0.0,
		1.0, 0.2, 0.2, 0.867, 0.52, 0.0,
		1.0, 1.0, 0.2, 0.849, 0.5, 0.0,
		0.2, 1.0, 0.2, 0.83, 0.52, 0.0,
		0.2, 1.0, 1.0, 0.825, 0.58, 0.0,
		0.2, 0.2, 1.0, 0.83, 0.64, 0.0,
		//------------------------
		1.0, 0.2, 1.0, 0.838, 0.668, 0.0,
		1.0, 0.2, 0.2, 0.854, 0.67, 0.0,
		1.0, 1.0, 0.2, 0.87, 0.64, 0.0,
		0.2, 1.0, 0.2, 0.875, 0.58, 0.0,
		0.2, 1.0, 1.0, 0.87, 0.52, 0.0,
		0.2, 0.2, 1.0, 0.863, 0.6, 0.0,
	 };

	glInterleavedArrays(GL_C3F_V3F, 0, intertwined);
}

void display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0.0, 255.0, 255.0);

	int i = 0;

	if (Method == DrawArrays) {
		setupPointers_polygons();
		for (i = 0; i < 426; i += 6) {
			glDrawArrays(GL_POLYGON, i, 6);
			if (i == 408) {
				glColor3f(1.0, 0.0, 0.0); //red
			}
		}
		glColor3f(0.0, 255.0, 255.0); //light blue
		setupPointers_triangles();
		glDrawArrays(GL_TRIANGLES, 0, 414);
	}
	else if (Method == DrawElements) {
		
		int a = 0;
		setupPointers_polygons();
		for (i = 0; i < 426; i += 6) {
			GLuint indices_poly[] = { num[i],num[i + 1], num[i + 2], num[i + 3], num[i + 4], num[i + 5] };
			glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_INT, indices_poly);
			if (i == 408) {
				glColor3f(1.0, 0.0, 0.0); //red
			}
		}
		glColor3f(0.0, 255.0, 255.0); //light blue
		setupPointers_triangles();
		for (i = 0; i < 414; i += 3) {
			GLuint indices_tri[] = { num[i],num[i + 1], num[i + 2]};
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, indices_tri);
		}
	}
	else if (Method == MultiDrawArrays) {
		static GLsizei count1[] = {
			6,6,6,6,6,6,6,6,6,6,6,6,6,6,
			6,6,6,6,6,6,6,6,6,6,6,6,6,6,
			6,6,6,6,6,6,6,6,6,6,6,6,6,6,
			6,6,6,6,6,6,6,6,6,6,6,6,6,6,
			6,6,6,6,6,6,6,6,6,6,6,6,6,6,6
		};
		setupPointers_polygons();
		GLint *first = new GLint [71];
		int k = 0;
		for (i = 0; i < 426; i += 6) {
			first[k] = num[i];
			k++;
		}
		glMultiDrawArrays(GL_POLYGON, first, count1, 71);
		free(first);

		//-----LOGO------
		glColor3f(1.0, 0.0, 0.0); //red
		static GLsizei count3[] = {
			6,6
		};
		GLint *first3 = new GLint[6];
		k = 0;
		for (i = 414; i < 426; i += 6) {
			first3[k] = num[i];
			k++;
		}
		glMultiDrawArrays(GL_POLYGON, first3, count1, 2);
		free(first3);
		glColor3f(0.0, 255.0, 255.0); //light blue

		static GLsizei count2[] = {
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3
		};
		setupPointers_triangles();
		GLint *first2 = new GLint[138];
		k = 0;
		for (i = 0; i < 414; i += 3) {
			first2[k] = num[i];
			k++;
		}
		glMultiDrawArrays(GL_TRIANGLES, first2, count2, 138);
		free(first2);
	}
	else if (Method == MultiDrawElements) {
		static GLsizei count1[] = {
			6,6,6,6,6,6,6,6,6,6,6,6,6,6,
			6,6,6,6,6,6,6,6,6,6,6,6,6,6, 
			6,6,6,6,6,6,6,6,6,6,6,6,6,6, 
			6,6,6,6,6,6,6,6,6,6,6,6,6,6, 
			6,6,6,6,6,6,6,6,6,6,6,6,6,6,6
		};
		int j;
		static GLvoid ** indices = new GLvoid *[71];
		setupPointers_polygons();
		for (i = 0; i < 426; i+=6) {	
			GLuint *indices_poly = new GLuint[6];
			for (j = 0; j < 6; j++) {
				indices_poly[j] = num[i+j];
			}

			int k = i / 6;
			indices[k] = indices_poly;
		}
		glMultiDrawElements(GL_POLYGON, count1, GL_UNSIGNED_INT, indices,71);
		
		for (i = 0; i < 71; i++) {
			free(indices[i]);
		}

		//-----LOGO---
		glColor3f(1.0, 0.0, 0.0); //red
		static GLsizei count3[] = {
			6,6
		};
		static GLvoid ** indices3 = new GLvoid *[2];
		int m = 0;
		for (i = 414; i < 426; i += 6) {
			GLuint *indices_poly3 = new GLuint[6];
			for (j = 0; j < 6; j++) {
				indices_poly3[j] = num[i + j];
			}

			indices3[m] = indices_poly3;
			m++;
		}
		glMultiDrawElements(GL_POLYGON, count3, GL_UNSIGNED_INT, indices3, 2);

		for (i = 0; i < 2; i++) {
			free(indices3[i]);
		}
		glColor3f(0.0, 255.0, 255.0); //light blue

		static GLsizei count2[] = {
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			3,3,3,3,3,3,3,3,3,3,3,3,3
		};
		static GLvoid ** indices2 = new GLvoid *[138];
		setupPointers_triangles();
		for (i = 0; i < 414; i+=3) {
			GLuint *indices_tri = new GLuint[3];
			for (j = 0; j < 3; j++) {
				indices_tri[j] = num[i + j];
			}
			int k = i / 3;
			indices2[k] = indices_tri;
		}
		glMultiDrawElements(GL_TRIANGLES, count2, GL_UNSIGNED_INT, indices2, 138);
		for (i = 0; i < 138; i++) {
			free(indices2[i]);
		}
	}

	glutSwapBuffers();
	glFlush();
}

void init(void) 
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	setupPointers_polygons();
	setupPointers_triangles();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
		case 49:
			printf("keyboard 1\n");
			Method = DrawArrays;
			glutPostRedisplay();
			break;
		case 50:
			printf("keyboard 2\n");
			Method = DrawElements;
			glutPostRedisplay();
			break;
		case 51:
			printf("keyboard 3\n");
			Method = MultiDrawArrays;
			glutPostRedisplay();
			break;
		case 52:
			printf("keyboard 4\n");
			Method = MultiDrawElements;
			glutPostRedisplay();
			break;

	}
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(900, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glewInit();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

void setupPointers_polygons(void)
{
	static GLfloat polygons[] = {
		//-----------國----------
		0.05, 0.5, 0.0,
		0.048, 0.53, 0.0,
		0.052, 0.74, 0.0,
		0.06, 0.73, 0.0,
		0.06, 0.51, 0.0,
		0.06, 0.51, 0.0,	
		//------------------------
		0.055, 0.73, 0.0,
		0.07, 0.75, 0.0,
		0.13, 0.78, 0.0,
		0.13, 0.76, 0.0,
		0.06, 0.72, 0.0,
		0.06, 0.72, 0.0,
		//------------------------
		0.06, 0.54, 0.0,
		0.125, 0.55, 0.0,
		0.125, 0.52, 0.0,
		0.06, 0.51, 0.0,
		0.06, 0.51, 0.0,
		0.06, 0.51, 0.0,
		//------------------------
		0.13, 0.78, 0.0,
		0.135, 0.77, 0.0,
		0.14, 0.51, 0.0,
		0.132, 0.48, 0.0,
		0.132, 0.48, 0.0,
		0.132, 0.48, 0.0,
		//------------------------
		0.125, 0.52, 0.0,
		0.133, 0.52, 0.0,
		0.132, 0.48, 0.0,
		0.132, 0.48, 0.0,
		0.132, 0.48, 0.0,
		0.132, 0.48, 0.0,
		//------------------------
		0.059, 0.73, 0.0,
		0.063, 0.73, 0.0,
		0.072, 0.69, 0.0,
		0.061, 0.64, 0.0,
		0.061, 0.64, 0.0,
		0.061, 0.64, 0.0,
		//------------------------
		0.069, 0.69, 0.0,
		0.12, 0.73, 0.0,
		0.123, 0.7, 0.0,
		0.068, 0.67, 0.0,
		0.068, 0.67, 0.0,
		0.068, 0.67, 0.0,
		//------------------------
		0.104, 0.76, 0.0,
		0.117, 0.77, 0.0,
		0.123, 0.7, 0.0,
		0.11, 0.73, 0.0,
		0.11, 0.73, 0.0,
		0.11, 0.73, 0.0,
		//------------------------
		0.092, 0.74, 0.0,
		0.102, 0.75, 0.0,
		0.118, 0.64, 0.0,
		0.128, 0.58, 0.0,
		0.123, 0.55, 0.0,
		0.115, 0.62, 0.0,
		//------------------------
		0.121, 0.68, 0.0,
		0.125, 0.67, 0.0,
		0.122, 0.62, 0.0,
		0.094, 0.51, 0.0,
		0.08, 0.51, 0.0,
		0.115, 0.6, 0.0,
		//------------------------
		0.065, 0.59, 0.0,
		0.105, 0.63, 0.0,
		0.102, 0.6, 0.0,
		0.067, 0.56, 0.0,
		0.067, 0.56, 0.0,
		0.067, 0.56, 0.0,
		//------------------------
		0.065, 0.59, 0.0,
		0.108, 0.69, 0.0,
		0.112, 0.68, 0.0,
		0.083, 0.59, 0.0,
		0.083, 0.59, 0.0,
		0.083, 0.59, 0.0,
		//------------------------
		0.063, 0.62, 0.0,
		0.09, 0.65, 0.0,
		0.09, 0.63, 0.0,
		0.063, 0.6, 0.0,
		0.063, 0.6, 0.0,
		0.063, 0.6, 0.0,
		//------------------------
		0.063, 0.62, 0.0,
		0.085, 0.68, 0.0,
		0.094, 0.7, 0.0,
		0.07, 0.59, 0.0,
		0.07, 0.59, 0.0,
		0.07, 0.59, 0.0,
		//---------立-------------
		0.177, 0.63, 0.0,
		0.18, 0.65, 0.0,
		0.25, 0.69, 0.0,
		0.252, 0.65, 0.0,
		0.23, 0.65, 0.0,
		0.18, 0.61, 0.0,
		//------------------------
		0.207, 0.73, 0.0,
		0.23, 0.685, 0.0,
		0.21, 0.65, 0.0,
		0.205, 0.7, 0.0,
		0.205, 0.7, 0.0,
		0.205, 0.7, 0.0,
		//------------------------
		0.177, 0.51, 0.0,
		0.268, 0.53, 0.0,
		0.27, 0.5, 0.0,
		0.26, 0.51, 0.0,
		0.19, 0.48, 0.0,
		0.19, 0.48, 0.0,
		//------------------------
		0.199, 0.59, 0.0,
		0.23, 0.67, 0.0,
		0.24, 0.67, 0.0,
		0.196, 0.56, 0.0,
		0.196, 0.56, 0.0,
		0.196, 0.56, 0.0,
		//------------------------
		0.198, 0.59, 0.0,
		0.25, 0.62, 0.0,
		0.25, 0.61, 0.0,
		0.196, 0.56, 0.0,
		0.196, 0.56, 0.0,
		0.196, 0.56, 0.0,
		//------------------------
		0.245, 0.62, 0.0,
		0.255, 0.61, 0.0,
		0.211, 0.5, 0.0,
		0.207, 0.5, 0.0,
		0.207, 0.5, 0.0,
		0.207, 0.5, 0.0,
		//---------中--------------
		0.28, 0.68, 0.0,
		0.285, 0.69, 0.0,
		0.29, 0.68, 0.0,
		0.292, 0.59, 0.0,
		0.283, 0.61, 0.0,
		0.283, 0.61, 0.0,
		//------------------------
		0.285, 0.68, 0.0,
		0.36, 0.695, 0.0,
		0.36, 0.67, 0.0,
		0.345, 0.68, 0.0,
		0.298, 0.65, 0.0,
		0.298, 0.65, 0.0,
		//------------------------
		0.36, 0.695, 0.0,
		0.365, 0.67, 0.0,
		0.31, 0.6, 0.0,
		0.31, 0.58, 0.0,
		0.31, 0.58, 0.0,
		0.31, 0.58, 0.0,
		//------------------------
		0.31, 0.6, 0.0,
		0.33, 0.615, 0.0,
		0.345, 0.61, 0.0,
		0.345, 0.59, 0.0,
		0.309, 0.58, 0.0,
		0.309, 0.58, 0.0,
		//------------------------
		0.325, 0.735, 0.0,
		0.333, 0.74, 0.0,
		0.333, 0.41, 0.0,
		0.325, 0.4, 0.0,
		0.325, 0.4, 0.0,
		0.325, 0.4, 0.0,
		//-----------興------------
		0.365, 0.55, 0.0,
		0.489, 0.6, 0.0,
		0.49, 0.57, 0.0,
		0.44, 0.565, 0.0,
		0.37, 0.51, 0.0,
		0.363, 0.52, 0.0,
		//------------------------
		0.395, 0.485, 0.0,
		0.43, 0.51, 0.0,
		0.425, 0.49, 0.0,
		0.405, 0.46, 0.0,
		0.405, 0.46, 0.0,
		0.405, 0.46, 0.0,
		//------------------------
		0.39, 0.51, 0.0,
		0.41, 0.49, 0.0,
		0.4, 0.47, 0.0,
		0.4, 0.47, 0.0,
		0.4, 0.47, 0.0,
		0.4, 0.47, 0.0,
		//------------------------
		0.46, 0.52, 0.0,
		0.485, 0.49, 0.0,
		0.483, 0.45, 0.0,
		0.483, 0.45, 0.0,
		0.483, 0.45, 0.0,
		0.483, 0.45, 0.0,
		//------------------------
		0.405, 0.55, 0.0,
		0.405, 0.69, 0.0,
		0.402, 0.71, 0.0,
		0.41, 0.71, 0.0,
		0.412, 0.55, 0.0,
		0.412, 0.55, 0.0,
		//------------------------
		0.418, 0.55, 0.0,
		0.422, 0.69, 0.0,
		0.413, 0.72, 0.0,
		0.421, 0.725, 0.0,
		0.423, 0.55, 0.0,
		0.423, 0.55, 0.0,
		//------------------------
		0.438, 0.57, 0.0,
		0.428, 0.73, 0.0,
		0.435, 0.73, 0.0,
		0.429, 0.56, 0.0,
		0.429, 0.56, 0.0,
		0.429, 0.56, 0.0,
		//------------------------
		0.448, 0.56, 0.0,
		0.45, 0.752, 0.0,
		0.46, 0.75, 0.0,
		0.455, 0.55, 0.0,
		0.455, 0.55, 0.0,
		0.455, 0.55, 0.0,
		//------------------------
		0.428, 0.725, 0.0,
		0.45, 0.75, 0.0,
		0.46, 0.74, 0.0,
		0.428, 0.72, 0.0,
		0.428, 0.72, 0.0,
		0.428, 0.72, 0.0,
		//------------------------
		0.468, 0.57, 0.0,
		0.475, 0.74, 0.0,
		0.485, 0.75, 0.0,
		0.482, 0.73, 0.0,
		0.472, 0.57, 0.0,
		0.472, 0.57, 0.0,
		//------------------------
		0.45, 0.725, 0.0,
		0.48, 0.74, 0.0,
		0.48, 0.72, 0.0,
		0.45, 0.715, 0.0,
		0.45, 0.715, 0.0,
		0.45, 0.715, 0.0,
		//------------------------
		0.43, 0.69, 0.0,
		0.45, 0.7, 0.0,
		0.45, 0.65, 0.0,
		0.43, 0.65, 0.0,
		0.43, 0.65, 0.0,
		0.43, 0.65, 0.0,
		//------------------------
		0.43, 0.56, 0.0,
		0.45, 0.7, 0.0,
		0.445, 0.57, 0.0,
		0.445, 0.57, 0.0,
		0.445, 0.57, 0.0,
		0.445, 0.57, 0.0,
		//------------------------
		0.45, 0.74, 0.0,
		0.48, 0.65, 0.0,
		0.475, 0.6, 0.0,
		0.45, 0.72, 0.0,
		0.45, 0.72, 0.0,
		0.45, 0.72, 0.0,
		//------------------------
		0.48, 0.65, 0.0,
		0.48, 0.62, 0.0,
		0.45, 0.65, 0.0,
		0.45, 0.65, 0.0,
		0.45, 0.65, 0.0,
		0.45, 0.65, 0.0,
		//---------大--------------
		0.52, 0.62, 0.0,
		0.6, 0.67, 0.0,
		0.6, 0.64, 0.0,
		0.538, 0.59, 0.0,
		0.525, 0.57, 0.0,
		0.525, 0.57, 0.0,
		//------------------------
		0.58, 0.74, 0.0,
		0.584, 0.74, 0.0,
		0.56, 0.5, 0.0,
		0.55, 0.5, 0.0,
		0.55, 0.5, 0.0,
		0.55, 0.5, 0.0,
		//------------------------
		0.535, 0.5, 0.0,
		0.56, 0.555, 0.0,
		0.555, 0.5, 0.0,
		0.555, 0.5, 0.0,
		0.555, 0.5, 0.0,
		0.555, 0.5, 0.0,
		//------------------------
		0.58, 0.555, 0.0,
		0.61, 0.52, 0.0,
		0.609, 0.49, 0.0,
		0.609, 0.49, 0.0,
		0.609, 0.49, 0.0,
		0.609, 0.49, 0.0,
		//------------------------
		0.582, 0.5, 0.0,
		0.6, 0.52, 0.0,
		0.61, 0.495, 0.0,
		0.61, 0.495, 0.0,
		0.61, 0.495, 0.0,
		0.61, 0.495, 0.0,
		//--------學---------------
		0.64, 0.58, 0.0,
		0.628, 0.52, 0.0,
		0.63, 0.505, 0.0,
		0.635, 0.5, 0.0,
		0.647, 0.57, 0.0,
		0.647, 0.57, 0.0,
		//------------------------
		0.64, 0.575, 0.0,
		0.72, 0.63, 0.0,
		0.72, 0.61, 0.0,
		0.647, 0.565, 0.0,
		0.647, 0.565, 0.0,
		0.647, 0.565, 0.0,
		//------------------------
		0.72, 0.625, 0.0,
		0.71, 0.575, 0.0,
		0.73, 0.595, 0.0,
		0.735, 0.61, 0.0,
		0.73, 0.63, 0.0,
		0.73, 0.63, 0.0,
		//------------------------
		0.66, 0.512, 0.0,
		0.71, 0.52, 0.0,
		0.712, 0.5, 0.0,
		0.66, 0.5, 0.0,
		0.66, 0.5, 0.0,
		0.66, 0.5, 0.0,
		//------------------------
		0.68, 0.505, 0.0,
		0.686, 0.571, 0.0,
		0.692, 0.574, 0.0,
		0.697, 0.571, 0.0,
		0.69, 0.51, 0.0,
		0.692, 0.505, 0.0,
		//------------------------
		0.67, 0.56, 0.0,
		0.692, 0.57, 0.0,
		0.686, 0.535, 0.0,
		0.686, 0.535, 0.0,
		0.686, 0.535, 0.0,
		0.686, 0.535, 0.0,
		//------------------------
		0.683, 0.505, 0.0,
		0.692, 0.505, 0.0,
		0.692, 0.42, 0.0,
		0.683, 0.42, 0.0,
		0.683, 0.42, 0.0,
		0.683, 0.42, 0.0,
		//------------------------
		0.683, 0.42, 0.0,
		0.692, 0.42, 0.0,
		0.692, 0.41, 0.0,
		0.65, 0.36, 0.0,
		0.65, 0.36, 0.0,
		0.65, 0.36, 0.0,
		//------------------------
		0.652, 0.57, 0.0,
		0.652, 0.75, 0.0,
		0.659, 0.74, 0.0,
		0.659, 0.57, 0.0,
		0.659, 0.57, 0.0,
		0.659, 0.57, 0.0,
		//------------------------
		0.652, 0.71, 0.0,
		0.665, 0.77, 0.0,
		0.67, 0.74, 0.0,
		0.67, 0.74, 0.0,
		0.67, 0.74, 0.0,
		0.67, 0.74, 0.0,
		//------------------------
		0.652, 0.70, 0.0,
		0.67, 0.715, 0.0,
		0.67, 0.67, 0.0,
		0.652, 0.66, 0.0,
		0.652, 0.66, 0.0,
		0.652, 0.66, 0.0,
		//------------------------
		0.652, 0.64, 0.0,
		0.67, 0.66, 0.0,
		0.67, 0.63, 0.0,
		0.652, 0.61, 0.0,
		0.652, 0.61, 0.0,
		0.652, 0.61, 0.0,
		//------------------------
		0.7, 0.6, 0.0,
		0.71, 0.75, 0.0,
		0.714, 0.752, 0.0,
		0.718, 0.745, 0.0,
		0.71, 0.6, 0.0,
		0.71, 0.6, 0.0,
		//------------------------
		0.714, 0.749, 0.0,
		0.695, 0.725, 0.0,
		0.714, 0.71, 0.0,
		0.714, 0.71, 0.0,
		0.714, 0.71, 0.0,
		0.714, 0.71, 0.0,
		//------------------------
		0.697, 0.7, 0.0,
		0.71, 0.7, 0.0,
		0.709, 0.63, 0.0,
		0.692, 0.63, 0.0,
		0.692, 0.63, 0.0,
		0.692, 0.63, 0.0,
		//------------------------
		0.675, 0.702, 0.0,
		0.695, 0.715, 0.0,
		0.695, 0.685, 0.0,
		0.675, 0.69, 0.0,
		0.675, 0.69, 0.0,
		0.675, 0.69, 0.0,
		//------------------------
		0.671, 0.66, 0.0,
		0.688, 0.765, 0.0,
		0.695, 0.75, 0.0,
		0.67, 0.63, 0.0,
		0.67, 0.63, 0.0,
		0.67, 0.63, 0.0,
		//------------------------
		0.671, 0.58, 0.0,
		0.685, 0.676, 0.0,
		0.69, 0.674, 0.0,
		0.68, 0.59, 0.0,
		0.68, 0.59, 0.0,
		0.68, 0.59, 0.0,
		//------------------------
		0.67, 0.66, 0.0,
		0.7, 0.59, 0.0,
		0.69, 0.59, 0.0,
		0.66, 0.66, 0.0,
		0.66, 0.66, 0.0,
		0.66, 0.66, 0.0,
		//--------logo---------------
		0.8, 0.74, 0.0,
		0.79, 0.41, 0.0,
		0.86, 0.44, 0.0,
		0.88, 0.42, 0.0,
		0.867, 0.52, 0.0,
		0.83, 0.68, 0.0,
		//------------------------
		0.88, 0.42, 0.0,
		0.84, 0.77, 0.0,
		0.91, 0.79, 0.0,
		0.895, 0.6, 0.0,
		0.91, 0.4, 0.0,
		0.91, 0.4, 0.0,
		//------------------------
		0.88, 0.77, 0.0,
		0.79, 0.8, 0.0,
		0.8, 0.78, 0.0,
		0.88, 0.76, 0.0,
		0.88, 0.76, 0.0,
		0.88, 0.76, 0.0,
		//------------------------
		0.88, 0.77, 0.0,
		0.79, 0.8, 0.0,
		0.8, 0.78, 0.0,
		0.88, 0.76, 0.0,
		0.88, 0.76, 0.0,
		0.88, 0.76, 0.0,
		//------------------------
		0.88, 0.77, 0.0,
		0.8, 0.78, 0.0,
		0.86, 0.6, 0.0,
		0.88, 0.42, 0.0,
		0.88, 0.42, 0.0,
		0.88, 0.42, 0.0,
		//------------------------
		0.835, 0.66, 0.0,
		0.867, 0.52, 0.0,
		0.849, 0.5, 0.0,
		0.83, 0.52, 0.0,
		0.825, 0.58, 0.0,
		0.83, 0.64, 0.0,
		//------------------------
		0.838, 0.668, 0.0,
		0.854, 0.67, 0.0,
		0.87, 0.64, 0.0,
		0.875, 0.58, 0.0,
		0.87, 0.52, 0.0,
		0.863, 0.6, 0.0,
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, polygons);
}

void setupPointers_triangles(void)
{
	static GLfloat triangles[] = {
		0.05, 0.1, 0.0,
		0.05, 0.2, 0.0,
		0.055, 0.1, 0.0,
		0.05, 0.2, 0.0,
		0.055, 0.2, 0.0,
		0.055, 0.1, 0.0,
		0.075, 0.1, 0.0,
		0.075, 0.2, 0.0,
		0.08, 0.1, 0.0,
		0.075, 0.2, 0.0,
		0.08, 0.2, 0.0,
		0.08, 0.1, 0.0,
		0.05, 0.2, 0.0,
		0.055, 0.2, 0.0,
		0.075, 0.1, 0.0,
		0.055, 0.2, 0.0,
		0.08, 0.1, 0.0,
		0.075, 0.1, 0.0,
		0.11, 0.1, 0.0,
		0.11, 0.16, 0.0,
		0.115, 0.1, 0.0,
		0.11, 0.16, 0.0,
		0.115, 0.16, 0.0,
		0.115, 0.1, 0.0,
		0.09, 0.16, 0.0,
		0.102, 0.175, 0.0,
		0.115, 0.16, 0.0,
		0.09, 0.13, 0.0,
		0.102, 0.14, 0.0,
		0.115, 0.13, 0.0,
		0.09, 0.11, 0.0,
		0.102, 0.1, 0.0,
		0.115, 0.11, 0.0,
		0.09, 0.12, 0.0,
		0.095, 0.14, 0.0,
		0.095, 0.1, 0.0,
		0.127, 0.11, 0.0,
		0.127, 0.19, 0.0,
		0.131, 0.1, 0.0,
		0.127, 0.19, 0.0,
		0.131, 0.195, 0.0,
		0.131, 0.1, 0.0,
		0.122, 0.16, 0.0,
		0.122, 0.175, 0.0,
		0.137, 0.16, 0.0,
		0.122, 0.175, 0.0,
		0.137, 0.175, 0.0,
		0.137, 0.16, 0.0,
		0.128, 0.105, 0.0,
		0.127, 0.115, 0.0,
		0.137, 0.1, 0.0,
		0.127, 0.115, 0.0,
		0.137, 0.115, 0.0,
		0.137, 0.1, 0.0,
		0.145, 0.1, 0.0,
		0.145, 0.173, 0.0,
		0.149, 0.1, 0.0,
		0.145, 0.173, 0.0,
		0.149, 0.173, 0.0,
		0.149, 0.1, 0.0,
		0.145, 0.185, 0.0,
		0.145, 0.2, 0.0,
		0.149, 0.185, 0.0,
		0.145, 0.2, 0.0,
		0.149, 0.2, 0.0,
		0.149, 0.185, 0.0,
		0.158, 0.136, 0.0,
		0.162, 0.16, 0.0,
		0.162, 0.113, 0.0,
		0.175, 0.16, 0.0,
		0.179, 0.136, 0.0,
		0.175, 0.113, 0.0,
		0.162, 0.16, 0.0,
		0.169, 0.173, 0.0,
		0.175, 0.16, 0.0,
		0.162, 0.113, 0.0,
		0.175, 0.113, 0.0,
		0.169, 0.1, 0.0,
		0.187, 0.1, 0.0,
		0.187, 0.173, 0.0,
		0.191, 0.1, 0.0,
		0.187, 0.173, 0.0,
		0.191, 0.173, 0.0,
		0.191, 0.1, 0.0,
		0.202, 0.1, 0.0,
		0.202, 0.173, 0.0,
		0.207, 0.1, 0.0,
		0.202, 0.16, 0.0,
		0.207, 0.16, 0.0,
		0.207, 0.1, 0.0,
		0.187, 0.16, 0.0,
		0.199, 0.173, 0.0,
		0.207, 0.16, 0.0,
		0.233, 0.1, 0.0,
		0.233, 0.16, 0.0,
		0.238, 0.1, 0.0,
		0.233, 0.16, 0.0,
		0.238, 0.16, 0.0,
		0.238, 0.1, 0.0,
		0.213, 0.16, 0.0,
		0.225, 0.175, 0.0,
		0.238, 0.16, 0.0,
		0.213, 0.13, 0.0,
		0.225, 0.14, 0.0,
		0.238, 0.13, 0.0,
		0.213, 0.11, 0.0,
		0.225, 0.1, 0.0,
		0.238, 0.11, 0.0,
		0.213, 0.12, 0.0,
		0.218, 0.14, 0.0,
		0.218, 0.1, 0.0,
		0.247, 0.1, 0.0,
		0.247, 0.2, 0.0,
		0.251, 0.1, 0.0,
		0.247, 0.2, 0.0,
		0.251, 0.2, 0.0,
		0.251, 0.1, 0.0,
		0.273, 0.15, 0.0,
		0.278, 0.2, 0.0,
		0.278, 0.1, 0.0,
		0.278, 0.19, 0.0,
		0.29, 0.2, 0.0,
		0.302, 0.19, 0.0,
		0.278, 0.11, 0.0,
		0.29, 0.1, 0.0,
		0.302, 0.11, 0.0,
		0.313, 0.1, 0.0,
		0.313, 0.2, 0.0,
		0.318, 0.1, 0.0,
		0.313, 0.2, 0.0,
		0.318, 0.2, 0.0,
		0.318, 0.1, 0.0,
		0.329, 0.1, 0.0,
		0.329, 0.173, 0.0,
		0.333, 0.1, 0.0,
		0.329, 0.16, 0.0,
		0.333, 0.16, 0.0,
		0.333, 0.1, 0.0,
		0.313, 0.16, 0.0,
		0.324, 0.173, 0.0,
		0.334, 0.16, 0.0,
		0.344, 0.11, 0.0,
		0.344, 0.173, 0.0,
		0.349, 0.11, 0.0,
		0.344, 0.173, 0.0,
		0.349, 0.173, 0.0,
		0.349, 0.11, 0.0,
		0.36, 0.1, 0.0,
		0.36, 0.173, 0.0,
		0.365, 0.1, 0.0,
		0.36, 0.173, 0.0,
		0.365, 0.173, 0.0,
		0.365, 0.1, 0.0,
		0.344, 0.11, 0.0,
		0.355, 0.1, 0.0,
		0.365, 0.12, 0.0,
		0.375, 0.1, 0.0,
		0.375, 0.173, 0.0,
		0.379, 0.1, 0.0,
		0.375, 0.173, 0.0,
		0.379, 0.173, 0.0,
		0.379, 0.1, 0.0,
		0.39, 0.1, 0.0,
		0.39, 0.173, 0.0,
		0.394, 0.1, 0.0,
		0.39, 0.16, 0.0,
		0.394, 0.16, 0.0,
		0.394, 0.1, 0.0,
		0.375, 0.16, 0.0,
		0.385, 0.173, 0.0,
		0.394, 0.16, 0.0,
		0.404, 0.136, 0.0,
		0.408, 0.173, 0.0,
		0.408, 0.1, 0.0,
		0.408, 0.16, 0.0,
		0.416, 0.173, 0.0,
		0.427, 0.16, 0.0,
		0.408, 0.11, 0.0,
		0.416, 0.1, 0.0,
		0.427, 0.11, 0.0,
		0.427, 0.075, 0.0,
		0.427, 0.173, 0.0,
		0.431, 0.075, 0.0,
		0.427, 0.173, 0.0,
		0.431, 0.173, 0.0,
		0.431, 0.075, 0.0,
		0.408, 0.075, 0.0,
		0.418, 0.065, 0.0,
		0.427, 0.075, 0.0,
		0.453, 0.1, 0.0,
		0.453, 0.2, 0.0,
		0.458, 0.1, 0.0,
		0.453, 0.2, 0.0,
		0.458, 0.2, 0.0,
		0.458, 0.1, 0.0,
		0.478, 0.1, 0.0,
		0.478, 0.2, 0.0,
		0.482, 0.1, 0.0,
		0.478, 0.2, 0.0,
		0.482, 0.2, 0.0,
		0.482, 0.1, 0.0,
		0.453, 0.14, 0.0,
		0.453, 0.15, 0.0,
		0.482, 0.14, 0.0,
		0.453, 0.15, 0.0,
		0.482, 0.15, 0.0,
		0.482, 0.14, 0.0,
		0.493, 0.15, 0.0,
		0.497, 0.173, 0.0,
		0.497, 0.137, 0.0,
		0.496, 0.16, 0.0,
		0.504, 0.173, 0.0,
		0.515, 0.16, 0.0,
		0.496, 0.14, 0.0,
		0.498, 0.15, 0.0,
		0.51, 0.13, 0.0,
		0.496, 0.15, 0.0,
		0.512, 0.135, 0.0,
		0.514, 0.12, 0.0,
		0.512, 0.099, 0.0,
		0.512, 0.135, 0.0,
		0.516, 0.117, 0.0,
		0.496, 0.11, 0.0,
		0.504, 0.1, 0.0,
		0.515, 0.11, 0.0,
		0.525, 0.1, 0.0,
		0.525, 0.173, 0.0,
		0.529, 0.1, 0.0,
		0.525, 0.173, 0.0,
		0.529, 0.173, 0.0,
		0.529, 0.1, 0.0,
		0.525, 0.185, 0.0,
		0.525, 0.2, 0.0,
		0.529, 0.185, 0.0,
		0.525, 0.2, 0.0,
		0.529, 0.2, 0.0,
		0.529, 0.185, 0.0,
		0.539, 0.1, 0.0,
		0.539, 0.173, 0.0,
		0.543, 0.1, 0.0,
		0.539, 0.173, 0.0,
		0.543, 0.173, 0.0,
		0.543, 0.1, 0.0,
		0.554, 0.1, 0.0,
		0.554, 0.173, 0.0,
		0.559, 0.1, 0.0,
		0.554, 0.16, 0.0,
		0.559, 0.16, 0.0,
		0.559, 0.1, 0.0,
		0.539, 0.16, 0.0,
		0.551, 0.173, 0.0,
		0.559, 0.16, 0.0,
		0.568, 0.136, 0.0,
		0.572, 0.173, 0.0,
		0.572, 0.1, 0.0,
		0.572, 0.16, 0.0,
		0.581, 0.173, 0.0,
		0.591, 0.16, 0.0,
		0.572, 0.11, 0.0,
		0.581, 0.1, 0.0,
		0.591, 0.11, 0.0,
		0.589, 0.075, 0.0,
		0.589, 0.173, 0.0,
		0.593, 0.075, 0.0,
		0.589, 0.173, 0.0,
		0.593, 0.173, 0.0,
		0.593, 0.075, 0.0,
		0.572, 0.075, 0.0,
		0.581, 0.065, 0.0,
		0.591, 0.075, 0.0,
		0.614, 0.11, 0.0,
		0.614, 0.2, 0.0,
		0.619, 0.11, 0.0,
		0.614, 0.2, 0.0,
		0.619, 0.2, 0.0,
		0.619, 0.11, 0.0,
		0.64, 0.11, 0.0,
		0.64, 0.2, 0.0,
		0.644, 0.11, 0.0,
		0.64, 0.2, 0.0,
		0.644, 0.2, 0.0,
		0.644, 0.11, 0.0,
		0.614, 0.11, 0.0,
		0.629, 0.1, 0.0,
		0.644, 0.11, 0.0,
		0.654, 0.1, 0.0,
		0.654, 0.173, 0.0,
		0.659, 0.1, 0.0,
		0.654, 0.173, 0.0,
		0.659, 0.173, 0.0,
		0.659, 0.1, 0.0,
		0.672, 0.1, 0.0,
		0.672, 0.173, 0.0,
		0.677, 0.1, 0.0,
		0.672, 0.16, 0.0,
		0.677, 0.16, 0.0,
		0.677, 0.1, 0.0,
		0.654, 0.16, 0.0,
		0.666, 0.173, 0.0,
		0.677, 0.16, 0.0,
		0.687, 0.1, 0.0,
		0.687, 0.173, 0.0,
		0.691, 0.1, 0.0,
		0.687, 0.173, 0.0,
		0.691, 0.173, 0.0,
		0.691, 0.1, 0.0,
		0.687, 0.185, 0.0,
		0.687, 0.2, 0.0,
		0.691, 0.185, 0.0,
		0.687, 0.2, 0.0,
		0.691, 0.2, 0.0,
		0.691, 0.185, 0.0,
		0.698, 0.173, 0.0,
		0.703, 0.173, 0.0,
		0.709, 0.1, 0.0,
		0.703, 0.173, 0.0,
		0.714, 0.1, 0.0,
		0.709, 0.1, 0.0,
		0.709, 0.1, 0.0,
		0.72, 0.173, 0.0,
		0.714, 0.1, 0.0,
		0.72, 0.173, 0.0,
		0.725, 0.173, 0.0,
		0.714, 0.1, 0.0,
		0.729, 0.136, 0.0,
		0.733, 0.17, 0.0,
		0.733, 0.1, 0.0,
		0.733, 0.16, 0.0,
		0.743, 0.173, 0.0,
		0.753, 0.16, 0.0,
		0.733, 0.13, 0.0,
		0.733, 0.14, 0.0,
		0.753, 0.13, 0.0,
		0.733, 0.14, 0.0,
		0.753, 0.14, 0.0,
		0.753, 0.13, 0.0,
		0.751, 0.17, 0.0,
		0.755, 0.15, 0.0,
		0.751, 0.13, 0.0,
		0.731, 0.11, 0.0,
		0.755, 0.11, 0.0,
		0.744, 0.1, 0.0,
		0.763, 0.1, 0.0,
		0.763, 0.173, 0.0,
		0.768, 0.1, 0.0,
		0.763, 0.173, 0.0,
		0.768, 0.173, 0.0,
		0.768, 0.1, 0.0,
		0.763, 0.155, 0.0,
		0.778, 0.173, 0.0,
		0.781, 0.16, 0.0,
		0.786, 0.15, 0.0,
		0.79, 0.173, 0.0,
		0.79, 0.137, 0.0,
		0.789, 0.16, 0.0,
		0.797, 0.173, 0.0,
		0.808, 0.16, 0.0,
		0.789, 0.14, 0.0,
		0.791, 0.15, 0.0,
		0.803, 0.13, 0.0,
		0.789, 0.15, 0.0,
		0.805, 0.135, 0.0,
		0.807, 0.12, 0.0,
		0.805, 0.099, 0.0,
		0.805, 0.135, 0.0,
		0.809, 0.117, 0.0,
		0.789, 0.11, 0.0,
		0.797, 0.1, 0.0,
		0.808, 0.11, 0.0,
		0.818, 0.1, 0.0,
		0.818, 0.173, 0.0,
		0.822, 0.1, 0.0,
		0.818, 0.173, 0.0,
		0.822, 0.173, 0.0,
		0.822, 0.1, 0.0,
		0.818, 0.185, 0.0,
		0.818, 0.2, 0.0,
		0.822, 0.185, 0.0,
		0.818, 0.2, 0.0,
		0.822, 0.2, 0.0,
		0.822, 0.185, 0.0,
		0.832, 0.11, 0.0,
		0.832, 0.19, 0.0,
		0.836, 0.1, 0.0,
		0.832, 0.19, 0.0,
		0.836, 0.195, 0.0,
		0.836, 0.1, 0.0,
		0.827, 0.16, 0.0,
		0.827, 0.175, 0.0,
		0.842, 0.16, 0.0,
		0.827, 0.175, 0.0,
		0.842, 0.175, 0.0,
		0.842, 0.16, 0.0,
		0.843, 0.105, 0.0,
		0.832, 0.115, 0.0,
		0.842, 0.1, 0.0,
		0.832, 0.11, 0.0,
		0.842, 0.115, 0.0,
		0.842, 0.1, 0.0,
		0.85, 0.173, 0.0,
		0.855, 0.173, 0.0,
		0.861, 0.1, 0.0,
		0.855, 0.173, 0.0,
		0.866, 0.1, 0.0,
		0.861, 0.1, 0.0,
		0.861, 0.065, 0.0,
		0.872, 0.173, 0.0,
		0.866, 0.065, 0.0,
		0.872, 0.173, 0.0,
		0.877, 0.173, 0.0,
		0.866, 0.065, 0.0,
		0.853, 0.075, 0.0,
		0.868, 0.075, 0.0,
		0.858, 0.065, 0.0,
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, triangles);
}