/*********************************
1072���ϧ޳N�P���δ����M�D-���y�j��
�@��:�ĤT��  
4104056004 ��u�| ���a�@ 
4104056034 ��u�| �_�a�W
**********************************
�ĤH����
*********************************/
#ifndef ENEMY_H
#define ENEMY_H

#include "snowcraft\objects\Moving_object.h"
#include "snowcraft\objects\snowball.cpp"
class Enemy :public Moving_object {
public:
	int move_mode = MOVE_MODE_LINE;	//The move mode of enemy.
	Enemy() :Moving_object() {}
	Enemy(double x, double y, double z) :Moving_object(x, y, z) {
		init();
	}
	Enemy(double x, double y, double z, double v_x, double v_y, double v_z) :Moving_object(x, y, z, v_x, v_y, v_z) {
		init();
	}
	Enemy(Vec position,int mode) {
		_position = position;
		move_mode = mode;
		init();
	}
	void init() {
		HP = 3;
		charge = 0;
		_velocity = Vec(0.1, 0, 0);
		stoping = false;
		immortal = false;
		hitback = false;
		alive = true;
		object_time = time(0);

		/*�ھڰѼƩw�q���ʼҦ�*/
		switch (move_mode) {
			case MOVE_MODE_LINE:
				path = vector<Vec>{ Vec(_position),Vec(_position).plus(Vec(0,0,-40)) };
				//cout << "0path:" << path[0].x() << "," << path[0].y() << "," << path[0].z() << " " << path[1].x() << "," << path[1].y() << "," << path[1].z() << endl;
				break;
			case MOVE_MODE_TRIANGLE:
				path = vector<Vec>{ Vec(_position),Vec(_position).plus(Vec(-40,0,-20)), Vec(_position).plus(Vec(0,0,-40)) };
				//cout << "1path:" << path[0].x() << "," << path[0].y() << "," << path[0].z() << " " << path[2].x() << "," << path[2].y() << "," << path[2].z() << endl;
				break;
			case MOVE_MODE_SQUARE:
				path = vector<Vec>{ Vec(_position),Vec(_position).plus(Vec(-40,0,0)),Vec(_position).plus(Vec(-40,0,-40)),Vec(_position).plus(Vec(0,0,-40)) };
				//cout << "2path:" << path[0].x() << "," << path[0].y() << "," << path[0].z() << " " << path[3].x() << "," << path[3].y() << "," << path[3].z() << endl;

				break;
		}
		gofor = 1;	//�ؼЬ��ĤG�ӳ��I
	}
	/*���oHP�ƭ�*/
	int getHP() {
		return HP;
	}
	/*�]�w���L��*/
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
	/*�g�X���y*/
	Snowball Shot() {
		Vec v(-(snowball_speed+0.8), G, 0);
		Snowball sb = Snowball(_position, v,ENEMY_ID);
		return sb;
	}
	/*�Q���y�����A����P�i�J���h���A*/
	bool HitByBall(Snowball sb) {
		if (!immortal) {
			HP--;
			if (HP == 0)
			{
				//Set death.
				Death();
				return false;
			}
			else
			{
				//Stun for 1 sec.
				timer = time(0);	//Get now time
				_velocity = Vec(sb.velocity().x(),0,0);
				hitback = true; 
				immortal = true;
				//Display stun animation.
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
				return false;
			}
			else
			{
				Moveto(_velocity);
				_velocity = Vec(_velocity.x()*0.9, 0, 0);
				return true;
			}
		}
		return false;
	}
	/*�ĤH�۰ʲ��ʡAreturn true�N������|���I*/
	bool Auto_Move() {
		if (!hitback)
		{
			if (gofor == path.size())//Go back to start.
			{
				Vec v(Vec(path[0]).minus(_position));
				v = Vec(v.x() / v.length()*0.25, 0, v.z() / v.length()*0.25);
				Moveto(v);
				if (_position.rangeEqual(path[0],0.5))
				{
					gofor = 1;
					_position = Vec(path[0]);//�j����קK�d��
					return true;//Shot
				}
			}
			else
			{
				//cout << "1position:" << _position.x() << "," << _position.y() << "," << _position.z() << " goto:" << path[gofor].x() << "," << path[gofor].y() << "," << path[gofor].z() << endl;

				Vec v(Vec(path[gofor]).minus(_position));
				v = Vec(v.x() / v.length()*0.25,0, v.z() / v.length()*0.25);
				Moveto(v);
				if (_position.rangeEqual(path[gofor],0.5))
				{
					gofor++;
					_position = Vec(path[gofor-1]);//�j����קK�d��
					//Shot
					return true;
				}
			}
		}
		return false;
	}
	/*����*/
	bool Moveto(Vec step) {
		step.plus(_position);
		//_position.plus(step);
		if (step.x() > 90 || step.x() < -45
			|| step.z() > 90 || step.z() < -90)
		{
			position(step);
			return true;
			//return false;
		}
		else
		{
			position(step);
			return true;
		}
	}
	/*���`���A�]�w*/
	void Death() {
		alive = false;
		immortal = true;
	}
	/*ø�s�ĤH*/
	void Draw() {
		HitbackING();
		glPushMatrix();
			glTranslatef(_position.x(), _position.y(), _position.z());
			glRotatef(270, 0, 1, 0);
			glScalef(1.2, 1.2, 1.2);
			glCallList(ENEMY_ID);
		glPopMatrix();
	}
private:
	int HP;		//�ͩR��
	int charge; //����
	int gofor;
	bool immortal;	//�L�Ī��A
	bool hitback;	//���h���A
	bool alive;		//�ͦs���A,HP=0->alive=false;
	vector<Vec> path;	//�ĤH�樫�����|�A�������u�B�T���λP����ΤT��
	time_t timer;
};
#endif // !ENEMY_H
