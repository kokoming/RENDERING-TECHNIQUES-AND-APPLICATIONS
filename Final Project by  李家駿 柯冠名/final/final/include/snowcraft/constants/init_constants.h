/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:第三組  
4104056004 資工四 李家駿 
4104056034 資工四 柯冠名
**********************************
宣告常數與include檔案
*********************************/
#ifndef INIT_H
#define INIT_H

#include "GL/glew.h"
#include "GL/glut.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "GL/glm.h"
#include <iostream>
using namespace std;
#define INITIAL_HEIGHT 540
#define INITIAL_WIDTH  960

/*Scene constants:宣告場景所代表的變數*/
#define START_SCENE 0
#define BATTLE_SCENE 1
#define DEATH_SCENE 2
#define PAUSE_SCENE 3
#define WIN_SCENE 4
#define MIDDLE_SCENE 5

/*敵我id*/
#define HERO_ID 1
#define ENEMY_ID 2
#define SNOWBALL_ID 3

/*敵人移動模式*/
#define MOVE_MODE_LINE 0
#define MOVE_MODE_TRIANGLE 1
#define MOVE_MODE_SQUARE 2

/*移動參數*/
#define HIT_BACK_TIME 3

/*Models*/
GLMmodel *hero_model,*enemy_model;
void load_all_models() {
	if (!hero_model) {
		cout << "load models...";
		/*Load enemy model*/
		enemy_model = glmReadOBJ("model/Snowman/SnowmanOBJ.obj");
		glmScale(enemy_model, 0.1);
		glmFacetNormals(enemy_model);
		glmVertexNormals(enemy_model, 0);

		/*Load hero model*/
		hero_model = glmReadOBJ("model/Lego/lego.obj");
		glmScale(hero_model, 0.3);
		glmFacetNormals(hero_model);
		glmVertexNormals(hero_model, 90);
		cout << "Done!\n";

		/*Build display list*/
		glNewList(1, GL_COMPILE);
		glmDraw(hero_model, GLM_SMOOTH | GLM_MATERIAL);
		glEndList();

		glNewList(2, GL_COMPILE);
		glmDraw(enemy_model, GLM_SMOOTH | GLM_MATERIAL);
		glEndList();

		glNewList(3, GL_COMPILE);
		glutSolidSphere(2.0,20,10);
		glEndList();
	}
}
#endif // !INIT_H
