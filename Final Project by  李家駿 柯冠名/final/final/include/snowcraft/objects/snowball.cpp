/*********************************
1072���ϧ޳N�P���δ����M�D-���y�j��
�@��:�ĤT��  
4104056004 ��u�| ���a�@ 
4104056034 ��u�| �_�a�W
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
	int picther_id;	//�Y�X���y�����O,0=hero,1=enemy
	bool kill = false;
	Snowball() :Moving_object() {}
	Snowball(double x, double y, double z) :Moving_object(x, y, z) {}
	Snowball(double x, double y, double z, double v_x, double v_y, double v_z) :Moving_object(x, y, z, v_x, v_y, v_z) {}
	Snowball(Vec position, Vec velocity,int id) {
		_position = position;
		_velocity = velocity;
		picther_id = id;
	}
	/*�ˬd���y�O�_�X��*/
	bool isOutOfBound(int x_bound) {//Return 1 if the snowball is out of bound.
		_velocity.plus(Vec(0, G, 0));	//�W�[�U���t��
		_position.plus(_velocity);		//�e�i
		if (_position.x() > x_bound) {
			return 1;	//Kill the snowball.
		}
		if (_position.y() <= 0) {
			return 1;
		}
		return 0;
	}
	/*�N���y�]�w������*/
	void Kill() {
		kill = true;
	}
	/*�ھڦ�mø�s���y*/
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
