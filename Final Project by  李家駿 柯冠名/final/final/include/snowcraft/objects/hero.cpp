/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:第三組  
4104056004 資工四 李家駿 
4104056034 資工四 柯冠名
**********************************
可操作人物
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
	/*回傳HP數值*/
	int getHP() {
		return HP;
	}
	/*開啟無敵*/
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
	/*回傳集氣比率*/
	double charge_persent() {
		return (double)charge / 1;
	}
	/*雪球集氣射擊*/
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
	/*雪球普通射擊*/
	Snowball Shot(Vec v) {
		Snowball sb = Snowball(_position, v, HERO_ID);
		return sb;
	}
	/*雪球擊中扣血與進入擊退狀態*/
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
	/*擊退效果*/
	bool HitbackING() {
		if (hitback) {
			if (time(0) - timer == HIT_BACK_TIME) {	//幾秒之後解除擊退狀態
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
	/*移動*/
	bool Moveto(Vec step){
		if (stoping)		//stoping狀態下不可移動
			return false;
		step.plus(Vec(0, _position.y(), 0));
		//_position.plus(step);
		if (step.x() > 30 || step.x() < -90
			|| step.z() > 90 || step.z() < -90)	//出界檢查
		{
			return false;
		}
		else
		{
			position(step);
			return true;
		}
	}
	/*繪製人物*/
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
	int HP;		//生命值
	double charge; //集氣
	bool immortal;	//無敵狀態
	bool alive;		//生存狀態,HP=0->alive=false;
	bool hitback;	//擊退狀態
	time_t timer;
	GLMmodel * model;
};
#endif // !HERO_H
