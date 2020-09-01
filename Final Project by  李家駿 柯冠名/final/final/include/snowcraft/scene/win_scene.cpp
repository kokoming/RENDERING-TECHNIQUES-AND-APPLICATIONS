/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:  
4104056004 資工四 李家駿 
4104056034 資工四 柯冠名
**********************************
顯示勝利畫面
*********************************/
#ifndef WIN_SCENE_H
#define WIN_SCENE_H

#include "scene.h"
class Win_scene :public Scene {
	public:
		Win_scene() :Scene() {
			init();
		}

		Win_scene(double camera_x, double camera_y, double camera_z
			, double lookat_x, double lookat_y, double lookat_z
			, double camera_up_x, double camera_up_y, double camera_up_z)
			:Scene(camera_x, camera_y, camera_z, lookat_x, lookat_y, lookat_z, camera_up_x, camera_up_y, camera_up_z) {
			
		}
		
		void display(void)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(0, 1.78, 1, 100);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, win[n]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, 1);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, 1);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, youwin);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, 1.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, -0.7, 1.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, -0.7, 1.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, 1.0);
			glEnd();
			glDisable(GL_TEXTURE_2D);

			glutSwapBuffers();
		}

		void init(void)
		{
			num = 1;
			n = 1;
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glShadeModel(GL_SMOOTH);
			int i = 0;
			for (i = 0; i < 50; i++) {
				win[i] = i;
			}

			char b[5] = ".bmp";
			char str[3];
			char path[17] = "";

			cout << "loading win_scene texture...";
			glEnable(GL_TEXTURE_2D);
			for (i = 1; i < 50; i++) {
				char a[15] = "picture/";
				_itoa_s(i, str, 10);
				strcat_s(a,15, str);
				strcat_s(a, 15, b);
				strcpy_s(path, a);
				win[i] = load_texture(path);
			}
			youwin = load_texture("picture/youwin.bmp");
			cout << "Done!\n";

		}
		void Draw()
		{
			num++;
			if (num % 5 == 0) {
				n++;
			}
			if (n == 50) {
				n = 1;
			}
			display();
		}
	private:
		GLuint win[50];
		GLuint youwin;
		GLuint back;
		int num = 1;
		int n = 1;
		int now_input;
};










//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
//	glutInitWindowSize(INITIAL_WIDTH, INITIAL_HEIGHT);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("final");
//	init();
//	glewInit();
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//	glutKeyboardFunc(keyboard);
//
//	
//	glutMainLoop();
//	return 0;
//}

#endif // !WIN_SCENE_H