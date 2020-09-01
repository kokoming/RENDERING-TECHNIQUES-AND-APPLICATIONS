/*********************************
1072���ϧ޳N�P���δ����M�D-���y�j��
�@��:�ĤT��  
4104056004 ��u�| ���a�@ 
4104056034 ��u�| �_�a�W
**********************************
�ŧi�`�ƻPinclude�ɮ�
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

/*Scene constants:�ŧi�����ҥN���ܼ�*/
#define START_SCENE 0
#define BATTLE_SCENE 1
#define DEATH_SCENE 2
#define PAUSE_SCENE 3
#define WIN_SCENE 4
#define MIDDLE_SCENE 5

/*�ħ�id*/
#define HERO_ID 1
#define ENEMY_ID 2
#define SNOWBALL_ID 3

/*�ĤH���ʼҦ�*/
#define MOVE_MODE_LINE 0
#define MOVE_MODE_TRIANGLE 1
#define MOVE_MODE_SQUARE 2

/*���ʰѼ�*/
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
