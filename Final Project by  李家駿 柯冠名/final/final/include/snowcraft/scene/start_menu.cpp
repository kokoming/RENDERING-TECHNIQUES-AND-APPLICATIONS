/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:第三組  
4104056004 資工四 李家駿 
4104056034 資工四 柯冠名
**********************************
開始畫面
在這個畫面輸入上上下下左右左右BA可開啟作弊模式
*********************************/
#ifndef START_SCENE_H
#define START_SCENE_H
#include "scene.h"
class Start_menu :public Scene {
public:
	Start_menu():Scene() {
		init();
	}
	Start_menu(double camera_x, double camera_y, double camera_z
		, double lookat_x, double lookat_y, double lookat_z
		, double camera_up_x, double camera_up_y, double camera_up_z)
		:Scene(camera_x, camera_y, camera_z, lookat_x, lookat_y, lookat_z, camera_up_x, camera_up_y, camera_up_z) {
		//init();
	}
	/*Initialize all variables.*/
	void init() {
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glShadeModel(GL_SMOOTH);
		choose = 1;
		num = 1;
		n = 1;
		glEnable(GL_TEXTURE_2D);
		cout << "loading star_menu texture...";
		start_scene1 = load_texture("picture/start_scene1.bmp");
		start_scene2 = load_texture("picture/start_scene2.bmp");
		start1 = load_texture("picture/start1.bmp");
		start2 = load_texture("picture/start2.bmp");
		option1 = load_texture("picture/option1.bmp");
		option2 = load_texture("picture/option2.bmp");
		leave1 = load_texture("picture/leave1.bmp");
		leave2 = load_texture("picture/leave2.bmp");
		manual = load_texture("picture/manual.bmp");
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
		if (show_manual) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, manual);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, 1.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, 1.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 1.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, 1.0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glutSwapBuffers();
			return;
		}
		glEnable(GL_TEXTURE_2D);
		(n==1)? glBindTexture(GL_TEXTURE_2D, start_scene1): glBindTexture(GL_TEXTURE_2D, start_scene2);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, 1.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, 1.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 1.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, 1.0);
		glEnd();

		/*Draw start button.*/
		glPushMatrix();
			if (choose == 1) {
				glTranslatef(0.0, -0.2, 0.0);
				glBindTexture(GL_TEXTURE_2D, start2);
			}
			else 
				glBindTexture(GL_TEXTURE_2D, start1);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3, 0.7, 1.0);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3, 1.0, 1.0);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0.1, 1.0, 1.0);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.1, 0.7, 1.0);
			glEnd();
		glPopMatrix(); 

		/*Draw option button.*/
		glPushMatrix();
			if (choose == 2) {
				glTranslatef(0.0, -0.2, 0.0);
				glBindTexture(GL_TEXTURE_2D, option2);
			}
			else 
				glBindTexture(GL_TEXTURE_2D, option1);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0.15, 0.7, 1.0);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(0.15, 1.0, 1.0);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(0.55, 1.0, 1.0);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(0.55, 0.7, 1.0);
			glEnd();
		glPopMatrix();

		/*Draw leave button.*/
		glPushMatrix();
		if (choose == 3) {
			glTranslatef(0.0, -0.2, 0.0);
			glBindTexture(GL_TEXTURE_2D, leave2);
		}
		else
			glBindTexture(GL_TEXTURE_2D, leave1);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0.6, 0.7, 1.0);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(0.6, 1.0, 1.0);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 1.0);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, 0.7, 1.0);
			glEnd();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glutSwapBuffers();
	}
	/*開始畫面按左右鍵選擇輸入
	  return 0:nothing
	  return 1:start game
	  return 2:options
	  return 3:leave game
	  */
	int SpecialKey(GLint key)		
	{
		if (key != ' ') {
			shift_array();
			input_log[sizeof(cheat_code) / sizeof(int)-1] = key;
			for (int i = 0; i <  sizeof(cheat_code) / sizeof(int); i++)
				cout << input_log[i] << ",";
			cout << endl;
		}
		switch (key) {
			case GLUT_KEY_LEFT:
				choose--;
				break;
			case GLUT_KEY_RIGHT:
				choose++;
				break;
			case 13://Enter:
				if (show_manual) 
					show_manual = false;
				else
					(choose == 2) ? show_manual = true : show_manual = false;	//Show the manual.
				return choose;
				break;
			default:
				break;
		}

		if (cheat_open(input_log))
			return 4;	//Input the code.Open the cheat mode.
		if (choose == 4) {
			choose = 1;
		}
		else if (choose == 0) {
			choose = 3;
		}
		return 0;
	}

	/*如果輸入指令與作弊碼符合，就開啟作弊模式
		開啟return true*/
	bool cheat_open(int *log) {
		for (int i = 0; i < sizeof(cheat_code)/sizeof(int); i++) {
			if (log[i] != cheat_code[i]) return false;
		}
		return true;
	}

	/*Array向前移動一個單位*/
	void shift_array() {
		for (int i = 0; i < sizeof(cheat_code) / sizeof(int)-1; i++)
			input_log[i] = input_log[i+1];
		input_log[sizeof(cheat_code) / sizeof(int) - 1] = 0;
	}
	int Draw(GLint key) {
		int tmp=SpecialKey(key);
		num++;
		if (num % 100 == 0) {
			n++;
		}
		if (n == 3) {
			n = 1;
		}
		display();
		return tmp;
	}
private:
	GLuint start_scene1;
	GLuint start_scene2;
	GLuint start1;
	GLuint start2;
	GLuint option1;
	GLuint option2;
	GLuint leave1;
	GLuint leave2;
	GLuint manual;
	int choose = 1;
	int num = 1;
	int n = 1;
	int input_log_index = 0;
	bool show_manual = false;
	GLint cheat_code[10] = { GLUT_KEY_UP,GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_DOWN ,GLUT_KEY_LEFT,GLUT_KEY_RIGHT,GLUT_KEY_LEFT,GLUT_KEY_RIGHT,'b','a' };
	GLint input_log[11] = { 0 };
	//GLint cheat_code[5] = { 'c','h','e','a','t' };
};
#endif // !START_SCENE_H
