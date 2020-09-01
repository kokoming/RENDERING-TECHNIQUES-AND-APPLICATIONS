/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:第三組  
4104056004 資工四 李家駿 
4104056034 資工四 柯冠名
**********************************
敵人物件
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

		/*根據參數定義移動模式*/
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
		gofor = 1;	//目標為第二個頂點
	}
	/*取得HP數值*/
	int getHP() {
		return HP;
	}
	/*設定為無敵*/
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
	/*射出雪球*/
	Snowball Shot() {
		Vec v(-(snowball_speed+0.8), G, 0);
		Snowball sb = Snowball(_position, v,ENEMY_ID);
		return sb;
	}
	/*被雪球擊中，扣血與進入擊退狀態*/
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
	/*擊退效果*/
	bool HitbackING() {
		if (hitback) {
			if (time(0) - timer == HIT_BACK_TIME) {	//幾秒之後解除擊退狀態
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
	/*敵人自動移動，return true代表走到路徑頂點*/
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
					_position = Vec(path[0]);//強制移動避免卡住
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
					_position = Vec(path[gofor-1]);//強制移動避免卡住
					//Shot
					return true;
				}
			}
		}
		return false;
	}
	/*移動*/
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
	/*死亡狀態設定*/
	void Death() {
		alive = false;
		immortal = true;
	}
	/*繪製敵人*/
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
	int HP;		//生命值
	int charge; //集氣
	int gofor;
	bool immortal;	//無敵狀態
	bool hitback;	//擊退狀態
	bool alive;		//生存狀態,HP=0->alive=false;
	vector<Vec> path;	//敵人行走的路徑，分成直線、三角形與正方形三種
	time_t timer;
};
#endif // !ENEMY_H
