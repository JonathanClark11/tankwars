#ifndef __VECTOR__
#define __VECTOR__
#include <math.h>
class Vec3 {
public:
	// constructor
	Vec3(double x, double y, double z) {
		coord[0] = x;
		coord[1] = y;
		coord[2] = z;
	};
	// destructor
	~Vec3() {};
    
	// access to individual elements
	double& operator[] (int i) {
		return coord[i];
	};
    
	// dot product with other vector
	double dot(Vec3 other) {
		return coord[0]*other[0] + coord[1]*other[1] + coord[2]*other[2];
	};
    
	// cross product with other vector
	Vec3 cross(Vec3 other) {
		return Vec3(coord[1]*other[2] - coord[2]*other[1],
					coord[2]*other[0] - coord[0]*other[2],
					coord[0]*other[1] - coord[1]*other[0] );
	};
    
	// magnitude/length of this vector
	double length() {
		return sqrt(coord[0]*coord[0] + coord[1]*coord[1] + coord[2]*coord[2]);
	};
    
	// normalized vector
	void normalize() {
		double l=length();
		coord[0] /= l;
		coord[1] /= l;
		coord[2] /= l;
	};
    
	double coord[3];
    
};
#endif