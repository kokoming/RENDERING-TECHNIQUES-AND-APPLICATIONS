/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:第三組  
4104056004 資工四 李家駿 
4104056034 資工四 柯冠名
**********************************
This object will creating a bounding box around the object.
Isn't used in this project.
*********************************/
//#ifndef BOUNDING_BOX_H
//#define BOUNDING_BOX_H
//#include "snowcraft\objects\Moving_object.h"
//class Bounding_box:public Moving_object{
//public:
//	Bounding_box():Moving_object() {
//		//_x = 0.0;
//		//_y = 0.0;
//		//_z = 0.0;
//		_width=1.0;
//		_height= 1.0;
//		_length= 1.0;
//		_angle_x=0;
//		_angle_y=0;
//		_angle_z=0;
//	}
//	Bounding_box(float x, float y, float z, float width, float height, float length) {
//		//_x = x;
//		//_y = y;
//		//_z = z;
//		//position = Vec(x, y, z);
//		_width = width;
//		_height = height;
//		_length = length;
//		_angle_x = 0;
//		_angle_y = 0;
//		_angle_z = 0;
//	}
//	float width() { return _width; }
//	float height() { return _height; }
//	float length() { return _length; }
//	void Move(float x_step,float y_step,float z_step) {
//		/*Bounding box will move with the object.*/
//		_x += x_step;
//		_y += y_step;
//		_z += z_step;
//	}
//	void Rotate(float angle_x,float angle_y,float angle_z) {
//		/*Bounding box will rotate with the object.*/
//		_angle_x = angle_x;
//		_angle_y = angle_y;
//		_angle_z = angle_z;
//	}
//
//	bool collision(Bounding_box b2) {
//		/*AABB collision*/
//		float minX1 = _x + width() / 2,
//			maxX1 = _x + width() / 2,
//			minY1 = _y - height() / 2,
//			maxY1 = _y + height() / 2,
//			minZ1 = _z - length() / 2,
//			maxZ1 = _z + length() / 2;
//
//		float minX2 = b2.x() - b2.width() / 2,
//			maxX2 = b2.x() + b2.width() / 2,
//			minY2 = b2.y() - b2.height() / 2,
//			maxY2 = b2.y() + b2.height() / 2,
//			minZ2 = b2.z() - b2.length() / 2,
//			maxZ2 = b2.z() + b2.length() / 2;
//
//		if (maxX1 > minX2 && maxX2 > minX1 &&
//			maxY1 > minY2 && maxY2 > minY1 &&
//			maxZ1 > minZ2 && maxZ2 > minZ1) {
//			return true;
//		}
//		else
//			return false;
//	}
//	void Draw() {
//		/*Recreating the bounding box.*/
//		/*Draw a virtual bounding box*/
//		/*if (draw_box) {
//			glPushMatrix();
//			glTranslatef(_x, _y, _z);
//			glRotatef(_angle_x, 1, 0, 0);
//			glRotatef(_angle_y, 0, 1, 0);
//			glRotatef(_angle_z, 0, 0, 1);
//			glScalef(_width, _height, _length);
//			glutWireCube(1.0);
//			glPopMatrix();
//		}*/
//	}
//private:
//	float _width;
//	float _height;
//	float _length;
//	float _angle_x;
//	float _angle_y;
//	float _angle_z;
//};
//#endif