/*********************************
1072���ϧ޳N�P���δ����M�D-���y�j��
�@��:�ĤT��  
4104056004 ��u�| ���a�@ 
4104056034 ��u�| �_�a�W
**********************************
�i�ާ@�H��
*********************************/
#ifndef HERO_H
#define HERO_H
#include "snowcraft\objects\Moving_object.h"
#include "snowcraft\objects\snowball.cpp"
class Hero :public Moving_object {
public:
	Hero():Moving_object(){}
	Hero(double x,double y,double z):Moving_object(x,y,z){
		HP = 5;
		charge = 0;
		_velocity = Vec(0.1, 0, 0);
		stoping = false;
		immortal = false;
		hitback = false;
		alive = true;
		object_time = time(0);
		model = hero_model;
	}
	Hero(double x, double y, double z, double v_x, double v_y, double v_z) :Moving_object(x, y, z, v_x, v_y, v_z) {
		HP = 3;
		charge = 0;
		stoping = false;
		immortal = false;
		hitback = false;
		alive = true;
		object_time = time(0);
	}
	/*�^��HP�ƭ�*/
	int getHP() {
		return HP;
	}
	/*�}�ҵL��*/
	void Immortal(int state) {	//Enable or disable stop state;
		if (state == 0) {
			immortal = false;
		}
		else if (state == 1)
		{
			immortal = true;
		}
		else
			;
	}
	/*�^�Ƕ����v*/
	double charge_persent() {
		return (double)charge / 1;
	}
	/*���y����g��*/
	Snowball chargeShot(char key) {
		if (!hitback) {
			Vec v(snowball_speed, G, 0);
			switch (key) {
			case 'c':	//Charging
				if (charge < 1)
					charge += charge_unit;
				else
					charge = 1;
				break;
			case 's':   //Shot
				cout << "charge:" << charge << "\n";
				v.plus(Vec(charge_speed_base*charge, 0, 0));
				charge = 0;
				return Shot(v);
				break;
			default:
				break;
			}
		}
	}
	/*���y���q�g��*/
	Snowball Shot(Vec v) {
		Snowball sb = Snowball(_position, v, HERO_ID);
		return sb;
	}
	/*���y��������P�i�J���h���A*/
	bool HitByBall(Snowball sb) {	//Return true if still alive.
		if (!immortal) {
			HP--;
			if (HP == 0)
			{
				alive = false;
				immortal = true;
				return false;
			}
			else
			{
				timer = time(0);	//Get now time
				_velocity = Vec(sb.velocity().x(), 0, 0);
				hitback = true;
				immortal = true;
				stoping = true;
				return true;
			}
		}
		return false;
	}
	/*���h�ĪG*/
	bool HitbackING() {
		if (hitback) {
			if (time(0) - timer == HIT_BACK_TIME) {	//�X����Ѱ����h���A
				hitback = false;
				immortal = false;
				stoping = false;
				_velocity = Vec(0.05, 0, 0);
				return false;
			}
			else
			{
				Moveto(_position.plus(_velocity));
				_velocity = Vec(_velocity.x()*0.9, 0, 0);
				return true;
			}
		}
		return false;
	}
	/*����*/
	bool Moveto(Vec step){
		if (stoping)		//stoping���A�U���i����
			return false;
		step.plus(Vec(0, _position.y(), 0));
		//_position.plus(step);
		if (step.x() > 30 || step.x() < -90
			|| step.z() > 90 || step.z() < -90)	//�X���ˬd
		{
			return false;
		}
		else
		{
			position(step);
			return true;
		}
	}
	/*ø�s�H��*/
	void Draw() {
		HitbackING();
		glPushMatrix();
			glTranslatef(_position.x(), _position.y(), _position.z());
			glTranslatef(-5, -2, 7);
			glRotatef(90, 0, 1, 0);
			glCallList(HERO_ID);
		glPopMatrix();
	}
private:
	int HP;		//�ͩR��
	double charge; //����
	bool immortal;	//�L�Ī��A
	bool alive;		//�ͦs���A,HP=0->alive=false;
	bool hitback;	//���h���A
	time_t timer;
	GLMmodel * model;
};
#endif // !HERO_H
