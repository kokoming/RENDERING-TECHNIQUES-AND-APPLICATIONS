/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:第三組  
4104056004 資工四 李家駿 
4104056034 資工四 柯冠名
**********************************
死亡場景
*********************************/
#ifndef DEATH_SCENE_H
#define DEATH_SCENE_H

#define NDEBUG
#include "scene.h"
class Death_scene :public Scene {
	public:
		Death_scene() :Scene() {
			init();
		}

		Death_scene(double camera_x, double camera_y, double camera_z
			, double lookat_x, double lookat_y, double lookat_z
			, double camera_up_x, double camera_up_y, double camera_up_z)
			:Scene(camera_x, camera_y, camera_z, lookat_x, lookat_y, lookat_z, camera_up_x, camera_up_y, camera_up_z) {

		}
		void init(void)
		{
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glShadeModel(GL_SMOOTH);
			glEnable(GL_TEXTURE_2D);
			num = 1;
			n = 1;
			int i = 0;
			for (i = 0; i <7; i++) {
				death[i] = i;
			}

			char b[5] = ".bmp";
			char str[3];
			char path[30] = "";

			glEnable(GL_TEXTURE_2D);
			cout << "loading death_scene texture...";
			for (i = 1; i < 7; i++) {
				char a[25] = "picture/death";
				_itoa_s(i, str, 10);
				strcat_s(a, 25, str);
				strcat_s(a, 25, b);
				strcpy_s(path, a);
				death[i] = load_texture(path);
			}
			cout << "Done!\n";
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
			glBindTexture(GL_TEXTURE_2D, death[n]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, 1.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, 1.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 1.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, 1.0);
			glEnd();

			glutSwapBuffers();
		}
		void Draw() {
			num++;
			if (num % 40 == 0) {
				n++;
			}
			if (n == 7) {
				n = 1;
			}
			display();
		}
	private:
		GLuint death[7];
		GLuint back;
		int num;
		int n;

};
#endif //!DEATH_SCENE_H