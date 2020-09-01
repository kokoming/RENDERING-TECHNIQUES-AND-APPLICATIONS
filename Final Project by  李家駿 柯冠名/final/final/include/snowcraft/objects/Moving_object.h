/*********************************
1072���ϧ޳N�P���δ����M�D-���y�j��
�@��:�ĤT��  
4104056004 ��u�| ���a�@ 
4104056034 ��u�| �_�a�W
**********************************
Define a moving object.
*********************************/
#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include "snowcraft\constants\init_constants.h"
//#include "snowcraft\objects\bounding_box.cpp"
#include "snowcraft\constants\vec.cpp"
#include <ctime>
class Moving_object {
public:
	Vec _position;
	Vec _velocity;
	bool stoping = false;	//���i���ʪ��A
	time_t object_time;			//�����ɶ�
	//GLMmodel * model;	    //3D model

	Moving_object() {
		_position = Vec(0, 0, 0);
		_velocity = Vec(0, 0, 0);
	}
	Moving_object(double x, double y, double z) {
		_position = Vec(x, y, z);
	}
	Moving_object(double x, double y, double z,double v_x,double v_y,double v_z) {
		_position = Vec(x, y, z);
		_velocity = Vec(v_x, v_y, v_z);
	}
	void Stop(int state) {	//Enable or disable stop state;
		if (state == 0) {	//Disable stop state;
			stoping = false;
		}
		else if (state == 1)
		{
			stoping = true;
		}
		else
			;
	}
	Vec position() {
		Vec tmp = _position;
		return tmp;
	}
	Vec velocity() {
		Vec tmp = _velocity;
		return tmp;
	}
	void position(Vec tmp) {
		_position = Vec(tmp.x(), tmp.y(), tmp.z());
	}

	void position(double x, double y, double z) {
		_position = Vec(x, y, z);
	}
	void Move(Vec step) {
		if(!stoping)
			_position = _position.plus(step);
	}
	void Move(double x_step, double y_step, double z_step) {
		Vec tmp = Vec(x_step, y_step, z_step);
		Move(tmp);
	}
	void Draw();
private:
};
#endif // !MOVING_OBJECT_H
