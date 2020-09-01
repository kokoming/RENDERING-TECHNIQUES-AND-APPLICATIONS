/*********************************
1072成圖技術與應用期末專題-雪球大戰
作者:第三組  
4104056004 資工四 李家駿 
4104056034 資工四 柯冠名
**********************************
This class will implement a 3d vector operation.  
*********************************/
#ifndef VEC_H
#define VEC_H

#include <math.h>
class Vec {
public:
	Vec() {
		_x = 0.0;
		_y = 0.0;
		_z = 0.0;
	}
	Vec(double x, double y, double z) {
		_x = x;
		_y = y;
		_z = z;
	}
	double x() {
		double tmp = _x;
		return tmp;
	}
	double y() {
		double tmp = _y;
		return tmp;
	}
	double z() {
		double tmp = _z;
		return tmp;
	}
	void x(double x) {
		_x = x;
	}
	void y(double y) {
		_y = y;
	}
	void z(double z) {
		_z = z;
	}
	double length() {
		return sqrt(_x*_x + _y*_y + _z*_z);
	}
	Vec plus(Vec b) {
		_x = _x + b.x();
		_y = _y + b.y();
		_z = _z + b.z();
		return Vec(_x , _y , _z );
	}
	Vec minus(Vec b) {
		_x = _x - b.x();
		_y = _y - b.y();
		_z = _z - b.z();
		return Vec(_x , _y , _z );
	}
	double dot(Vec b) {
		return _x*b.x() + _y*b.y() + _z*b.z();
	}
	Vec cross(Vec b) {
		Vec tmp(_y*b.z() - _z*b.y(), _z*b.x() - _x*b.z(), _x*b.y() - _y*b.x());
		return tmp;
	}
	bool equal(Vec b) {
		if (_x == b.x() && _y == b.y() && _z == b.z())
			return true;
		return false;
	}
	bool rangeEqual(Vec b, double range) {
		if (abs(_x - b.x())<=range
			&& abs(_y - b.y()) <= range
			&& abs(_z - b.z()) <= range)
			return true;
		return false;
	}
private:
	double _x;
	double _y;
	double _z;
};
#endif