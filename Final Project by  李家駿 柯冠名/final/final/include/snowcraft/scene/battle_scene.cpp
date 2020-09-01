/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:第三組  
4104056004 資工四 李家駿 
4104056034 資工四 柯冠名
**********************************
This object will create a battle scene.
未完成項目:
已完成項目:
	己方移動:滑鼠
	己方切換腳色:鍵盤"1","2","3"按鍵
	己方射擊(無集氣):X鍵
	己方碰撞判定
	離開程式:Esc
	敵人受傷死亡
	己方受傷死亡
	WIN-LOSE-FLAG
	己方集氣射擊
	敵己方受傷擊退
	關卡設計
	作弊模式
	敵人移動射擊
	場地貼圖，天空貼圖
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
	bool Unlimited_Snow_Ball_Works = false;				//作弊模式:無限雪球製
	bool People_Do_Not_Died_If_They_Are_Kill = false;	//作弊模式:人被殺不會死
	int stage = 1;				//現在的關卡編號
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
	/*開啟/關閉作弊模式*/
	void open_cheat(int Holy_Grail) {
		if (Holy_Grail == 1) {	//啟動作弊模式
			cout << "啟動作弊模式\n";
			Unlimited_Snow_Ball_Works = true;	
			People_Do_Not_Died_If_They_Are_Kill = true;
			init_objects();
		}
		else if (Holy_Grail == 0) {	//關閉作弊模式
			cout << "關閉作弊模式\n";
			Unlimited_Snow_Ball_Works = false;
			People_Do_Not_Died_If_They_Are_Kill = false;
			init_objects();
		}
	}
	/*初始化一些有的沒的*/
	void init() {	//初始化螢幕
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
		if (People_Do_Not_Died_If_They_Are_Kill)	//作弊模式開啟
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
	/*讀取關卡資料，關卡資料的格式為:
		第一行:一個整數，紀錄敵人的數量。
		第二行之後:一行三個浮點數，一個整數，用逗號隔開，紀錄敵人的位置與移動模式
		ex.
			3			//三個敵人
			10,5,0,0	//在(10,5,0)這個位置，移動模式為0(MODE_LINE)
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
	/*繪製場景(地板，天空)*/
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

	/*繪製HUD(血條，集氣條，箭頭)*/
	void Draw_2d() {
		/*因為接下來會把projection先轉成2D，所以要先記錄物件的2D位置*/
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

		/*畫方形框住目前操作腳色*/
		if (heros[now_controll].getHP() > 0) {
			glPushMatrix();
				glColor3f(0.88, 0, 0);
				glTranslatef(heros[now_controll].position().x(), heros[now_controll].position().y()-5, heros[now_controll].position().z());
				glScalef(10, 1, 10);
				glutWireCube(1.0);
			glPopMatrix();
		}

		/*將Projection轉換成2D
		此段程式碼改編自 https://www.youtube.com/watch?v=i1mp4zflkYo */
		glPushMatrix();
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
				glLoadIdentity();
				gluOrtho2D(0, INITIAL_WIDTH, 0, INITIAL_HEIGHT);
				glClearColor(1, 1, 1, 0);
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
					glLoadIdentity();

					/*畫己方HUD*/
					for (int i = 0; i < heros.size(); i++)
						if (heros[i].getHP() > 0)
						{
							/*編號*/
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

							/*血條*/
							glPushMatrix();
								glDisable(GL_LIGHTING);
								glColor3f(1, 0, 0);
								glTranslatef(heros_mouse_position[i].x()-5*(5- heros[i].getHP()), heros_mouse_position[i].y()+40,0);
								glScalef(heros[i].getHP()*10, 10 ,1);
								glutSolidCube(1.0);
								glEnable(GL_LIGHTING);
							glPopMatrix();

							/*血條外框*/
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

							/*集氣條*/
							glPushMatrix();
								glDisable(GL_LIGHTING);
								glColor3f(1* heros[i].charge_persent(), 1, 0);	//根據集氣程度變色
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

						/*畫敵方HUD*/
						for (int i = 0; i < enemys.size(); i++)
							if (enemys[i].getHP() > 0)
							{
								/*血條*/
								glPushMatrix();
									glDisable(GL_LIGHTING);
									glColor3f(1, 0, 0);
									glTranslatef(enemys_mouse_position[i].x() - 5 * (3 - enemys[i].getHP()), enemys_mouse_position[i].y() + 40, 0);
									glScalef(enemys[i].getHP() * 10, 10, 1);
									glutSolidCube(1.0);
									glEnable(GL_LIGHTING);
									glPopMatrix();

									/*血條外框*/
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

	/*繪製雪球*/
	void Draw_snowballs() {
		//Draw the snowballs.
		if (!snowball_buffer.empty()) {
			/*先清除已出界的雪球*/
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
			/*畫雪球*/
			if (!snowball_buffer.empty())
				for (std::vector<Snowball>::iterator iter = snowball_buffer.begin(); iter != snowball_buffer.end(); ++iter)
					(*iter).Draw();

			/*雪球撞擊偵測*/
			for (int i = 0; i < snowball_buffer.size(); i++) {
				if (snowball_buffer[i].picther_id == HERO_ID) {	//敵方被擊中偵測
					for (int j = 0; j < enemys.size(); j++) {
						/*利用座標判定擊中與否，受擊判定框為自己中心點12x12範圍以內*/
						if (abs(snowball_buffer[i].position().x() - enemys[j].position().x()) <= 6
							&& abs(snowball_buffer[i].position().z() - enemys[j].position().z()) <= 6) {
							if (enemys[j].HitByBall(snowball_buffer[i]))	//被擊中沒死
							{
								cout << "Enemy number " << j << "is hit.HP=" << enemys[j].getHP() << endl;
								/*Remove snowball from list*/
								snowball_buffer[i].Kill();
							}

						}
					}
				}
				if (snowball_buffer[i].picther_id == ENEMY_ID) {	//己方被擊中偵測
					for (int j = 0; j < heros.size(); j++) {
						if (abs(snowball_buffer[i].position().x() - heros[j].position().x()) <= 2.5
							&& abs(snowball_buffer[i].position().z() - heros[j].position().z()) <= 2.5) {
							if (heros[j].HitByBall(snowball_buffer[i]))	//被擊中沒死
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

	/*繪製battle scene*/
	void Draw(unsigned char key,int mouse_x,int mouse_y) {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity(); 
		gluLookAt(camera.x(), camera.y(), camera.z(), lookat.x(), lookat.y(), lookat.z(), camera_up.x(), camera_up.y(), camera_up.z());
		
		/*操作區----------------------------*/
		/*執行指令*/
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
						//集氣
						heros[now_controll].chargeShot(key);
						charging = true;
					}
				}
				break;
			case 'v':	//敵方手動射擊，debug用
				if (enemys[0].getHP() > 0)	//Dead people can't attack.
					snowball_buffer.push_back(enemys[0].Shot());
			default:
				break;
		}

		/*移動己方*/
		heros[now_controll].Moveto(GetCursorPlane(mouse_x, mouse_y));

		/*繪圖區-------------------------------------*/
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

		/*結束區---------------------------------------*/
		/*殘餘人數統計*/
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
	int number_of_enemys = 3;		//敵人數量
	int number_of_heros = 3;		//己方數量
	int now_controll = 0;			//現在控制的角色
	bool charging = false;			//集氣狀態		
	std::vector<Snowball> snowball_buffer;	//雪球queue
	std::vector<Enemy> enemys;				//敵人queue
	vector<Vec>enemys_position;				//敵人位置queue
	vector<int>enemy_move_mode;				//敵人移動模式queue
	std::vector<Hero> heros;				//己方queue
	GLuint wall;							//牆壁貼圖
	GLuint floor;							//地板貼圖
};
#endif // !BATTLE_SCENE_H