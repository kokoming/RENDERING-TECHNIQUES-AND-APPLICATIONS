/*********************************
1072���ϧ޳N�P���δ����M�D-���y�j��
�@��:�ĤT��  
4104056004 ��u�| ���a�@ 
4104056034 ��u�| �_�a�W
**********************************
This object will create a battle scene.
����������:
�w��������:
	�v�貾��:�ƹ�
	�v������}��:��L"1","2","3"����
	�v��g��(�L����):X��
	�v��I���P�w
	���}�{��:Esc
	�ĤH���˦��`
	�v����˦��`
	WIN-LOSE-FLAG
	�v�趰��g��
	�Ĥv��������h
	���d�]�p
	�@���Ҧ�
	�ĤH���ʮg��
	���a�K�ϡA�ѪŶK��
*********************************/
#ifndef BATTLE_SCENE_H
#define BATTLE_SCENE_H

#include "scene.h"
#include "snowcraft\objects\hero.cpp"
#include "snowcraft\objects\enemy.cpp"
#include "snowcraft\objects\snowball.cpp"
class Battle_scene:public Scene{
public :

	bool Win_Flag = false;		//Set true if win.
	bool Lose_Flag = false;		//Set true if lose.
	bool Unlimited_Snow_Ball_Works = false;				//�@���Ҧ�:�L�����y�s
	bool People_Do_Not_Died_If_They_Are_Kill = false;	//�@���Ҧ�:�H�Q�����|��
	int stage = 1;				//�{�b�����d�s��
	Battle_scene() :Scene(){
	}

	Battle_scene(double camera_x, double camera_y, double camera_z
		, double lookat_x, double lookat_y, double lookat_z
		, double camera_up_x, double camera_up_y, double camera_up_z
		, int stage)
	:Scene(camera_x, camera_y,  camera_z, lookat_x,  lookat_y, lookat_z, camera_up_x,camera_up_y, camera_up_z){
		this->stage = stage;
		init();
		init_objects(); 
	}
	/*�}��/�����@���Ҧ�*/
	void open_cheat(int Holy_Grail) {
		if (Holy_Grail == 1) {	//�Ұʧ@���Ҧ�
			cout << "�Ұʧ@���Ҧ�\n";
			Unlimited_Snow_Ball_Works = true;	
			People_Do_Not_Died_If_They_Are_Kill = true;
			init_objects();
		}
		else if (Holy_Grail == 0) {	//�����@���Ҧ�
			cout << "�����@���Ҧ�\n";
			Unlimited_Snow_Ball_Works = false;
			People_Do_Not_Died_If_They_Are_Kill = false;
			init_objects();
		}
	}
	/*��l�Ƥ@�Ǧ����S��*/
	void init() {	//��l�ƿù�
		cout << "init\n";
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(65.0, 1 * (GLfloat)INITIAL_WIDTH / (GLfloat)INITIAL_HEIGHT, 1.0, 450.0);

		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_shininess[] = { 100.0 };
		GLfloat light_position[] = { 0.0, 50.0, 0.0, 0.0 };
		GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glShadeModel(GL_SMOOTH);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
		glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);

		glEnable(GL_TEXTURE_2D);
		wall = load_texture("picture/wall.bmp");
		floor = load_texture("picture/floor.bmp");
	}
	void init_objects() {
		field_length = 180;
		field_height = 1;
		field_width = 180;

		/*Create heros*/
		heros = { Hero(-40,5,0),Hero(-40,5,-20), Hero(-40,5,20) };
		if (People_Do_Not_Died_If_They_Are_Kill)	//�@���Ҧ��}��
			for (int i = 0; i < 3; i++)
				heros[i].Immortal(1);

		/*Read enemy data and create enemys.*/
		char stage_data[30] = "stage/stage",tmp[3];
		_itoa_s(stage, tmp, 10);
		strcat_s(stage_data, 30, tmp);
		strcat_s(stage_data, 30, ".txt");
		if (read_stage(stage_data) == 1)
			exit(0);
		enemys = vector<Enemy>(number_of_enemys);
		for (int i = 0; i < enemys.size(); i++) {
			enemys[i] = Enemy(enemys_position[i],enemy_move_mode[i]);
			//enemys[i].Immortal(1);
		}
	}
	/*Ū�����d��ơA���d��ƪ��榡��:
		�Ĥ@��:�@�Ӿ�ơA�����ĤH���ƶq�C
		�ĤG�椧��:�@��T�ӯB�I�ơA�@�Ӿ�ơA�γr���j�}�A�����ĤH����m�P���ʼҦ�
		ex.
			3			//�T�ӼĤH
			10,5,0,0	//�b(10,5,0)�o�Ӧ�m�A���ʼҦ���0(MODE_LINE)
			*/
	int read_stage(const char* stage_data) {	
		FILE *fp;
		if (fopen_s(&fp, stage_data, "r") != 0)
		{
			cout << "Can't read stage data '" << stage_data << "'.\n";
			return 1;
		}
		double tmp,tmpxyz[3];
		int i = 0;
		fscanf_s(fp, "%d", &number_of_enemys);	//Get number of enemys.
		while (fscanf_s(fp, "%lf,", &tmp) != EOF) {	//Read enemy positions data
			tmpxyz[i++] = tmp;
			if (i == 3) {
				i = 0;
				fscanf_s(fp, "%lf,", &tmp);
				enemy_move_mode.push_back(tmp);
				enemys_position.push_back(Vec(tmpxyz[0], tmpxyz[1], tmpxyz[2]));
			}
		}
		return 0;	//Success
	}
	/*ø�s����(�a�O�A�Ѫ�)*/
	void Draw_environment() {
		/*Draw the floor*/
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, wall);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(130.0, 0.0, -150.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(130.0, 60.0, -150.0);
		glTexCoord2f(2.0f, 2.0f); glVertex3f(130.0, 60.0, 450.0);
		glTexCoord2f(2.0f, 0.0f); glVertex3f(130.0, 0.0, 450.0);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, floor);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-100.0, 1.0, -150.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-100.0, 1.0, 450.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(130.0, 1.0, 450.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(130.0, 1.0, -150.0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			glScalef(field_length, field_height, field_width);
			glutWireCube(1.0);
		glPopMatrix();
	}

	/*ø�sHUD(����A������A�b�Y)*/
	void Draw_2d() {
		/*�]�����U�ӷ|��projection���ন2D�A�ҥH�n���O������2D��m*/
		int x= position_to_mouse(heros[now_controll].position()).x(), y= INITIAL_HEIGHT-position_to_mouse(heros[now_controll].position()).y();
		vector<Vec> heros_mouse_position;
		vector<Vec> enemys_mouse_position;
		/*Get the screen position of hero and enemys*/
		for (int i = 0; i < 3; i++) {
			heros_mouse_position.push_back(position_to_mouse(heros[i].position()));
			heros_mouse_position[i].y(INITIAL_HEIGHT - heros_mouse_position[i].y());
		}
		for (int i = 0; i < enemys.size(); i++) {
			enemys_mouse_position.push_back(position_to_mouse(enemys[i].position()));
			enemys_mouse_position[i].y(INITIAL_HEIGHT - enemys_mouse_position[i].y());
		}

		/*�e��ήئ�ثe�ާ@�}��*/
		if (heros[now_controll].getHP() > 0) {
			glPushMatrix();
				glColor3f(0.88, 0, 0);
				glTranslatef(heros[now_controll].position().x(), heros[now_controll].position().y()-5, heros[now_controll].position().z());
				glScalef(10, 1, 10);
				glutWireCube(1.0);
			glPopMatrix();
		}

		/*�NProjection�ഫ��2D
		���q�{���X��s�� https://www.youtube.com/watch?v=i1mp4zflkYo */
		glPushMatrix();
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
				glLoadIdentity();
				gluOrtho2D(0, INITIAL_WIDTH, 0, INITIAL_HEIGHT);
				glClearColor(1, 1, 1, 0);
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
					glLoadIdentity();

					/*�e�v��HUD*/
					for (int i = 0; i < heros.size(); i++)
						if (heros[i].getHP() > 0)
						{
							/*�s��*/
							for (int j = 0; j < i + 1; j++) {
							glPushMatrix();
								glDisable(GL_LIGHTING);
								glColor3f(0, 1, 0);
								glTranslatef(heros_mouse_position[i].x()-10+j*7, heros_mouse_position[i].y() + 60, 0);
								glScalef(4, 10, 1); 
								glutSolidCube(1.0);
								glEnable(GL_LIGHTING);
							glPopMatrix();
							}

							/*���*/
							glPushMatrix();
								glDisable(GL_LIGHTING);
								glColor3f(1, 0, 0);
								glTranslatef(heros_mouse_position[i].x()-5*(5- heros[i].getHP()), heros_mouse_position[i].y()+40,0);
								glScalef(heros[i].getHP()*10, 10 ,1);
								glutSolidCube(1.0);
								glEnable(GL_LIGHTING);
							glPopMatrix();

							/*����~��*/
							glPushMatrix();
								glDisable(GL_LIGHTING);
								glColor3f(0, 0, 0);

								for (int j = 0; j < 5; j++) {
									glPushMatrix();
										glTranslatef(heros_mouse_position[i].x() - 10 *(2-j), heros_mouse_position[i].y() + 40, 0);
										glScalef(10, 10.5, 1);
										glutWireCube(1.0);
									glPopMatrix();
								}
								glEnable(GL_LIGHTING);
							glPopMatrix();

							/*�����*/
							glPushMatrix();
								glDisable(GL_LIGHTING);
								glColor3f(1* heros[i].charge_persent(), 1, 0);	//�ھڶ���{���ܦ�
								glTranslatef(heros_mouse_position[i].x()-40,heros_mouse_position[i].y(),0);
								glPushMatrix();
									glScalef(11, 50, 1);
									glutWireCube(1.0);
								glPopMatrix(); 
								glTranslatef(0,-25*(1- heros[i].charge_persent()), 0);
								glScalef(10, 50*heros[i].charge_persent(), 1);
								glutSolidCube(1.0);
								glEnable(GL_LIGHTING);
							glPopMatrix();

						}

						/*�e�Ĥ�HUD*/
						for (int i = 0; i < enemys.size(); i++)
							if (enemys[i].getHP() > 0)
							{
								/*���*/
								glPushMatrix();
									glDisable(GL_LIGHTING);
									glColor3f(1, 0, 0);
									glTranslatef(enemys_mouse_position[i].x() - 5 * (3 - enemys[i].getHP()), enemys_mouse_position[i].y() + 40, 0);
									glScalef(enemys[i].getHP() * 10, 10, 1);
									glutSolidCube(1.0);
									glEnable(GL_LIGHTING);
									glPopMatrix();

									/*����~��*/
									glPushMatrix();
									glDisable(GL_LIGHTING);
									glColor3f(0, 0, 0);

									for (int j = 0; j < 3; j++) {
										glPushMatrix();
										glTranslatef(enemys_mouse_position[i].x() - 10 * (1 - j), enemys_mouse_position[i].y() + 40, 0);
										glScalef(10, 10.5, 1);
										glutWireCube(1.0);
										glPopMatrix();
									}
									glEnable(GL_LIGHTING);
								glPopMatrix();
							}
						glPopMatrix();
					glEnable(GL_LIGHTING);
				glPopMatrix();
				glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}

	/*ø�s���y*/
	void Draw_snowballs() {
		//Draw the snowballs.
		if (!snowball_buffer.empty()) {
			/*���M���w�X�ɪ����y*/
			for (std::vector<Snowball>::iterator iter = snowball_buffer.begin(); iter != snowball_buffer.end(); ++iter) {
				if ((*iter).isOutOfBound(90) == 1 || (*iter).kill) {
					if (&(*iter) == &snowball_buffer.back()) {
						snowball_buffer.pop_back();
						break;
					}
					else
						iter = snowball_buffer.erase(iter);
				}
				if (snowball_buffer.size() == 0)
					break;
			}
			/*�e���y*/
			if (!snowball_buffer.empty())
				for (std::vector<Snowball>::iterator iter = snowball_buffer.begin(); iter != snowball_buffer.end(); ++iter)
					(*iter).Draw();

			/*���y��������*/
			for (int i = 0; i < snowball_buffer.size(); i++) {
				if (snowball_buffer[i].picther_id == HERO_ID) {	//�Ĥ�Q��������
					for (int j = 0; j < enemys.size(); j++) {
						/*�Q�ήy�ЧP�w�����P�_�A�����P�w�ج��ۤv�����I12x12�d��H��*/
						if (abs(snowball_buffer[i].position().x() - enemys[j].position().x()) <= 6
							&& abs(snowball_buffer[i].position().z() - enemys[j].position().z()) <= 6) {
							if (enemys[j].HitByBall(snowball_buffer[i]))	//�Q�����S��
							{
								cout << "Enemy number " << j << "is hit.HP=" << enemys[j].getHP() << endl;
								/*Remove snowball from list*/
								snowball_buffer[i].Kill();
							}

						}
					}
				}
				if (snowball_buffer[i].picther_id == ENEMY_ID) {	//�v��Q��������
					for (int j = 0; j < heros.size(); j++) {
						if (abs(snowball_buffer[i].position().x() - heros[j].position().x()) <= 2.5
							&& abs(snowball_buffer[i].position().z() - heros[j].position().z()) <= 2.5) {
							if (heros[j].HitByBall(snowball_buffer[i]))	//�Q�����S��
							{
								cout << "Hero number " << j << "is hit.HP=" << heros[j].getHP() << endl;
								/*Remove snowball from list*/
								snowball_buffer[i].Kill();
							}
						}
					}
				}
			}
		}
	}

	/*ø�sbattle scene*/
	void Draw(unsigned char key,int mouse_x,int mouse_y) {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity(); 
		gluLookAt(camera.x(), camera.y(), camera.z(), lookat.x(), lookat.y(), lookat.z(), camera_up.x(), camera_up.y(), camera_up.z());
		
		/*�ާ@��----------------------------*/
		/*������O*/
		switch (key) {
			if (!charging) {
				case '1':
				case '2':
				case '3':
					now_controll = key - '0' - 1;
					glutWarpPointer(position_to_mouse(heros[now_controll].position()).x(), position_to_mouse(heros[now_controll].position()).y()); //Wrap the cursor position.
					break;
			}
			case 's':
				if (Unlimited_Snow_Ball_Works) break;
				if (heros[now_controll].getHP() > 0)	//Dead people can't attack.
				{
					snowball_buffer.push_back(heros[now_controll].chargeShot(key));
					charging = false;
				}
				break;
			case 'c':
				if (heros[now_controll].getHP() > 0)	//Dead people can't attack.
				{
					if (Unlimited_Snow_Ball_Works)
					{
						snowball_buffer.push_back(heros[now_controll].Shot(Vec(2.0, G, 0)));
						heros[now_controll].position(heros[now_controll].position().plus(Vec(0, 0, 1.5)));
						snowball_buffer.push_back(heros[now_controll].Shot(Vec(2.0, G, 0)));
						heros[now_controll].position(heros[now_controll].position().plus(Vec(0, 0, 1.5)));
						snowball_buffer.push_back(heros[now_controll].Shot(Vec(2.0, G, 0)));
						heros[now_controll].position(heros[now_controll].position().plus(Vec(0, 0, 1.5)));
						snowball_buffer.push_back(heros[now_controll].Shot(Vec(2.0, G, 0)));
						heros[now_controll].position(heros[now_controll].position().plus(Vec(0, 0, -4.5)));
						heros[now_controll].position(heros[now_controll].position().plus(Vec(0, 0, -1.5)));
						snowball_buffer.push_back(heros[now_controll].Shot(Vec(2.0, G, 0)));
						heros[now_controll].position(heros[now_controll].position().plus(Vec(0, 0, -1.5)));
						snowball_buffer.push_back(heros[now_controll].Shot(Vec(2.0, G, 0)));
						heros[now_controll].position(heros[now_controll].position().plus(Vec(0, 0, -1.5)));
						snowball_buffer.push_back(heros[now_controll].Shot(Vec(2.0, G, 0)));
						heros[now_controll].position(heros[now_controll].position().plus(Vec(0, 0, 4.5)));
					}
					else {
						//����
						heros[now_controll].chargeShot(key);
						charging = true;
					}
				}
				break;
			case 'v':	//�Ĥ��ʮg���Adebug��
				if (enemys[0].getHP() > 0)	//Dead people can't attack.
					snowball_buffer.push_back(enemys[0].Shot());
			default:
				break;
		}

		/*���ʤv��*/
		heros[now_controll].Moveto(GetCursorPlane(mouse_x, mouse_y));

		/*ø�ϰ�-------------------------------------*/
		/*Draw the floor,walls and sky.*/
		Draw_environment();

		/*Draw the hero*/
		for (int i = 0; i < heros.size(); i++)
			if (heros[i].getHP() > 0)
					heros[i].Draw();

		/*Draw the enemys*/
		for (int i = 0; i < enemys.size(); i++)
			if (enemys[i].getHP() > 0)
			{
				enemys[i].Draw();
				if (enemys[i].Auto_Move())
					snowball_buffer.push_back(enemys[i].Shot());
			}
		
		/*Draw the snowballs*/
		Draw_snowballs();

		/*Draw 2d objects.*/
		Draw_2d();

		/*������---------------------------------------*/
		/*�ݾl�H�Ʋέp*/
		int remains = 0;
		for (int i = 0; i < enemys.size(); i++)
			if (enemys[i].getHP() > 0)
				remains++;
		if (remains == 0)//No more enemys.
		{
			cout << "Win!!\n";
			Win_Flag = true;
		}
		remains = 0;
		for (int i = 0; i < heros.size(); i++)
			if (heros[i].getHP() > 0)
				remains++;
		if (remains == 0)//No more heros.
		{
			cout << "Lose!!\n";
			Lose_Flag = true;
		}

		glutSwapBuffers();

	}
private:
	double field_length, field_height, field_width;
	int number_of_enemys = 3;		//�ĤH�ƶq
	int number_of_heros = 3;		//�v��ƶq
	int now_controll = 0;			//�{�b�������
	bool charging = false;			//���𪬺A		
	std::vector<Snowball> snowball_buffer;	//���yqueue
	std::vector<Enemy> enemys;				//�ĤHqueue
	vector<Vec>enemys_position;				//�ĤH��mqueue
	vector<int>enemy_move_mode;				//�ĤH���ʼҦ�queue
	std::vector<Hero> heros;				//�v��queue
	GLuint wall;							//����K��
	GLuint floor;							//�a�O�K��
};
#endif // !BATTLE_SCENE_H