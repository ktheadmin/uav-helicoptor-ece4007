#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>
#include <iostream>

class Vector3 {

	private:
		double x;
		double y;
		double z;

		friend std::ostream& operator<<(std::ostream &os, const Vector3 &v);

	public:
		Vector3() : x(0), y(0), z(0) {
		}

		Vector3(double x, double y, double z) : x(x), y(y), z(z) {
		}

		Vector3(const Vector3 &cpy) {
			x = cpy.x;
			y = cpy.y;
			z = cpy.z;
		}

		double dot(const Vector3 &v) {
			return x*v.x + y*v.y + z*v.z;
		}

		double xydot(const Vector3 &v) {
			return x*v.x + y*v.y;
		}

		Vector3 cross(const Vector3 &v) {
			return Vector3(y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x);
		}

		Vector3 normalize() {
			double l = sqrt(x*x + y*y + z*z);
			if(l == 0.0) {
				Vector3 v(1,0,0);
				return v;
			}
			l = 1/l;
			return Vector3(x*l,y*l,z*l);
		}

		double mag() {
			return sqrt(x*x + y*y + z*z);
		}

		double xymag() {
			return sqrt(x*x + y*y);
		}

		double squared_mag() {
			return x*x + y*y + z*z;
		}

		void toArray(double *array) {
			array[0] = x;
			array[1] = y;
			array[2] = z;
		}

		Vector3	operator+(const Vector3 &rhs) {
			return Vector3(x+rhs.x,y+rhs.y,z+rhs.z);
		}

		Vector3	operator-(const Vector3 &rhs) {
			return Vector3(x-rhs.x,y-rhs.y,z-rhs.z);
		}

		double& operator[](const int &ind) {
			return ((ind > 0) ? ((ind > 1) ? z : y) : x);
		}

		Vector3 operator*(const double &rhs) {
			return Vector3(x*rhs,y*rhs,z*rhs);
		}

		Vector3 operator*(const Vector3 &rhs) {
			return Vector3(x*rhs.x,y*rhs.y,z*rhs.z);
		}

		Vector3& operator=(const Vector3 &rhs) {
			x = rhs.x; y = rhs.y; z = rhs.z;
			return *this;
		}

		Vector3& operator=(const double &rhs) {
			x = rhs; y = rhs; z = rhs;
			return *this;
		}

		bool operator==(const Vector3 &rhs) {
			return (x==rhs.x && y==rhs.y && z==rhs.z);
		}

		bool operator!=(const Vector3 &rhs) {
			return !(x==rhs.x && y==rhs.y && z==rhs.z);
		}
};

std::ostream& operator<<(std::ostream &os, const Vector3 &v) {
	os << "(" << v.x << "," << v.y << "," << v.z << ")";
	return os;
}

namespace vector3 {

	Vector3 i() {
		return Vector3(1.0,0.0,0.0);
	}

	Vector3 j() {
		return Vector3(0.0,1.0,0.0);
	}

	Vector3 k() {
		return Vector3(0.0,0.0,1.0);
	}

}

#endif
