// final.cpp : 定義主控台應用程式的進入點。
//
/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:
4104056004 資工四 李家駿
4104056034 資工四 柯冠名
**********************************
This program will implement a snowcraft game.
*********************************/
#include "stdafx.h"
#include "snowcraft/snowcraft.cpp"
Snowcraft snowcraft(0);
static bool press_on = false;	//偵測滑鼠持續按壓

void init() {
	glutSetCursor(GLUT_CURSOR_NONE);	//隱藏滑鼠游標
	snowcraft = Snowcraft(1);
	press_on = false;
}
void display()
{
	snowcraft.Display_scene();
}
void idle_display() 
{
	if (press_on)	//偵測持續按壓，直到放開按鍵
		snowcraft.now_input = 'c';
	snowcraft.Display_scene();
}
//void reshape(int w, int h)
//{
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	if (w>h)
//		gluPerspective(65.0, 1 * (GLfloat)w / (GLfloat)h, 1.0, 200.0);
//	else
//		gluPerspective(65.0*(GLfloat)h / (GLfloat)w, 1, 1.0, 200.0);
//}
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case '1':
		case '2':
		case '3':
		case 'c':
		case 'v':
		case 'b':
		case 'a':
		case 13://Enter
			snowcraft.now_input = key;
			glutPostRedisplay();
			break;
		case 27://Esc
			exit(EXIT_SUCCESS);
			break;
	}
}
void mouse(int button,int state, int x, int y) {
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) {	//Charge
				snowcraft.now_input = 'c';
				press_on = true;
				glutPostRedisplay();
			}
			else if (state == GLUT_UP) {
				snowcraft.now_input = 's';
				press_on = false;
				glutPostRedisplay();
			}
			else
				;
			break;
		default:
			//glutPostRedisplay();
			break;
	}
}
void special_keyboard(GLint key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT:
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
			snowcraft.now_input=key;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}
void move_mouse(int x, int y) {
	snowcraft.mouse_x = x;
	snowcraft.mouse_y = y;
	//cout << x << "," << y << endl;
	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(INITIAL_WIDTH, INITIAL_HEIGHT);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("final");
	init();
	glewInit();
	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);		//Keep the shape of objects.
	glutKeyboardFunc(keyboard);		//Get the keyboard input.
	glutSpecialFunc(special_keyboard); //Get special keyboard input.
	glutMouseFunc(mouse);			//Get the mouse input.
	glutPassiveMotionFunc(move_mouse);
	glutIdleFunc(idle_display);
	glutMainLoop();

    return 0;
}

