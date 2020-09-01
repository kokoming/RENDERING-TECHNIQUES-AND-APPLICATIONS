/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:第三組  
4104056004 資工四 李家駿 
4104056034 資工四 柯冠名
**********************************
Snowball object
*********************************/
#ifndef SNOWBALL_H
#define SNOWBALL_H
#define G -0.005
const double snowball_speed = 0.5;
const double charge_speed_base = 0.9;
const double charge_unit = 0.03;
#include "Moving_object.h"
class Snowball :public Moving_object {
public:
	int picther_id;	//擲出雪球者類別,0=hero,1=enemy
	bool kill = false;
	Snowball() :Moving_object() {}
	Snowball(double x, double y, double z) :Moving_object(x, y, z) {}
	Snowball(double x, double y, double z, double v_x, double v_y, double v_z) :Moving_object(x, y, z, v_x, v_y, v_z) {}
	Snowball(Vec position, Vec velocity,int id) {
		_position = position;
		_velocity = velocity;
		picther_id = id;
	}
	/*檢查雪球是否出界*/
	bool isOutOfBound(int x_bound) {//Return 1 if the snowball is out of bound.
		_velocity.plus(Vec(0, G, 0));	//增加下降速度
		_position.plus(_velocity);		//前進
		if (_position.x() > x_bound) {
			return 1;	//Kill the snowball.
		}
		if (_position.y() <= 0) {
			return 1;
		}
		return 0;
	}
	/*將雪球設定為消除*/
	void Kill() {
		kill = true;
	}
	/*根據位置繪製雪球*/
	void Draw() {	
		glPushMatrix();
			glEnable(GL_COLOR_MATERIAL);
			glColor3f(1, 1, 1);
			glTranslatef(_position.x(), _position.y(), _position.z());
			glCallList(SNOWBALL_ID);
			glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
	}
private:
};
#endif // !SNOWBALL_H
