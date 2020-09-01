/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:第三組  
4104056004 資工四 李家駿 
4104056034 資工四 柯冠名
**********************************
中間過場
*********************************/
#ifndef MIDDLE_SCENE_H
#define MIDDLE_SCENE_H

#define NDEBUG
#include "scene.h"
class Middle_scene :public Scene {
public:
	int stage;
	Middle_scene(int stage) :Scene() {
		this->stage = stage;
		init();
	}

	Middle_scene(double camera_x, double camera_y, double camera_z
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


		glEnable(GL_TEXTURE_2D);
		cout << "loading middle_scene texture...";
		char tex1_path[40] = "picture/level",tex2_path[40]= "picture/level";
		char tmp[3];
		_itoa_s(stage, tmp, 10);
		strcat_s(tex1_path, 40, tmp);
		strcat_s(tex1_path, 40, "-1.bmp");
		strcat_s(tex2_path, 40, tmp);
		strcat_s(tex2_path, 40, "-2.bmp");
		first = load_texture(tex1_path);
		second = load_texture(tex2_path);
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
		(n == 1) ? glBindTexture(GL_TEXTURE_2D, first) : glBindTexture(GL_TEXTURE_2D, second);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, 1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, 1.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 1.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, 1.0);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glutSwapBuffers();
		//glFlush();
	}
	void Draw() {
		num++;
		if (num % 100 == 0) {
			n++;
		}
		if (n == 3) {
			n = 1;
		}
		display();
	}
private:
	GLuint first;
	GLuint second;
	int num;
	int n;

};
#endif //!DEATH_SCENE_H