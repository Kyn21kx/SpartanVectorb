#pragma once
#include "Utilities.h"

class Vector3 {
public:
	Vector3() {
		Initialize(0, 0, 0);
	}

	Vector3 (float _x, float _y, float _z) {
		Initialize(_x, _y, _z);
	}
	
	//Returns a normalized version of the vector
	Vector3 Normalize() {
		//u = ||v|| / v
		float i = x / magnitude;
		float j = y / magnitude;
		float k = z / magnitude;
		Vector3 normalizedV;
		normalizedV.SetValues(i, j, k);
		return normalizedV;
	}

	void SetValues(float _x, float _y, float _z) {
		Initialize(_x, _y, _z);
	}

	float GetX() {
		return x;
	}
	float GetY() {
		return y;
	}
	float GetZ() {
		return z;
	}

	float GetMagnitude() {
		return magnitude;
	}

	bool Equals(Vector3 v3) {
		return (x == v3.x && y == v3.y && z == v3.z);
	}

	std::string ToString() {
		std::string strVec = "(" + ConvertToString<float>(x) + ", " + ConvertToString<float>(y) + ", " + ConvertToString<float>(z) + ")";
		return strVec;
	}
	template <int n>
	std::array<float, n> ToVertices() {
		std::array<float, 6> vert{
			0, 0, 0,
			x/100.0f, y/100.0f, z/100.0f
		};
		return vert;
	}
	//Define another function that returns an array taking the point B as the origin
	template <int n>
	std::array<float, n> ToVertices(Vector3 originPoint) {
		std::array<float, n> vert{
			originPoint.x/100.0f, originPoint.y/100.0f, originPoint.z/100.0f,
			x/100.0f, y/100.0f, z/100.0f
		};
		return vert;
	}

	float GetAngle() {
		return angle;
	}

	Vector3 operator * (const float factor) {
		return Vector3(x * factor, y * factor, z * factor);
	}

	Vector3 operator *= (const float factor) {
		float i, j, k;
		i = x * factor;
		j = y * factor;
		k = z * factor;
		this->SetValues(i, j, k);
		return *this;
	}

	Vector3 operator + (const Vector3 v) {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator += (const Vector3 v) {
		float i, j, k;
		i = x + v.x;
		j = y + v.y;
		k = z + v.z;
		this->SetValues(i, j, k);
		return *this;
	}

	Vector3 operator - (const Vector3 v) {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator -= (const Vector3 v) {
		float i, j, k;
		i = x - v.x;
		j = y - v.y;
		k = z - v.z;
		this->SetValues(i, j, k);
		return *this;
	}

	bool operator == (const Vector3 v) {
		return (x == v.x && y == v.y && z == v.z);
	}
	bool operator != (const Vector3 v) {
		return (x != v.x || y != v.y || z != v.z);
	}
	


	friend std::istream& operator>>(std::istream& input, Vector3& v) {
		float i, j, k;
		std::cout << "Set X: ";
		input >> i;
		std::cout << "Set Y: ";
		input >> j;
		std::cout << "Set Z: ";
		input >> k;
		v.SetValues(i, j, k);
		return input;
	}



private:
	float x, y, z;
	float angle;
	float magnitude;
	void Initialize(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
		magnitude = sqrt((x * x) + (y * y) + (z * z));
		angle = asinf(y / magnitude) * (180 / 3.1416f);
	}
};
//Delete this from a class and just make it a function
static class Vector3Math {
public:

	static float Distance(Vector3 a, Vector3 b) {
		//sqrt(Sum(comp^2))
		float sum = pow((b.GetX() - a.GetX()), 2) + pow((b.GetY() - a.GetY()), 2) + pow((b.GetZ() - a.GetZ()), 2);
		return sqrt(sum);
	}

	static float Dot(Vector3 a, Vector3 b) {
		float i = a.GetX() * b.GetX();
		float j = a.GetY() * b.GetY();
		float k = a.GetZ() * b.GetZ();
		return i + j + k;
	}

	static Vector3 Cross(Vector3 a, Vector3 b) {
		float x, y, z;
		x = a.GetY() * a.GetZ() - b.GetY() * b.GetZ();
		y = (a.GetX() * b.GetZ() - b.GetX() * a.GetZ()) * -1;
		z = a.GetX() * b.GetY() - b.GetX() * a.GetY();
		return Vector3(x, y, z);
	}

	static Vector3 AngleBetween() {

	}

	static Vector3 One() {
		return Vector3(1, 1, 1);
	}

	static Vector3 Zero() {
		return Vector3(0, 0, 0);
	}

};

//Definition for V4
class Vector4 {
public:
	Vector4() {
		Initialize(0, 0, 0, 0);
	}

	Vector4(float _x, float _y, float _z, float _w) {
		Initialize(_x, _y, _z, _w);
	}

	//Returns a normalized version of the vector
	Vector4 Normalize() {
		//u = ||v|| / v
		float i = x / magnitude;
		float j = y / magnitude;
		float k = z / magnitude;
		float l = w / magnitude;
		Vector4 normalizedV;
		normalizedV.SetValues(i, j, k, l);
		return normalizedV;
	}

	void SetValues(float _x, float _y, float _z, float _w) {
		Initialize(_x, _y, _z, _w);
	}

	bool Equals(Vector4 v4) {
		return (x == v4.x && y == v4.y && z == v4.z && w == v4.w);
	}

	float GetX() {
		return x;
	}
	float GetY() {
		return y;
	}
	float GetZ() {
		return z;
	}
	float GetW() {
		return w;
	}

	float GetMagnitude() {
		return magnitude;
	}

	std::string ToString() {
		std::string strVec = "(" + ConvertToString<float>(x) + ", " + ConvertToString<float>(y) + ", " + ConvertToString<float>(z) +", " + ConvertToString<float>(w) + ")";
		return strVec;
	}

private:
	float x, y, z, w;
	float magnitude;
	void Initialize(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		magnitude = sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}
};
class Vector4Math {
public:

	static float Distance(Vector4 a, Vector4 b) {
		//sqrt(Sum(comp^2))
		float sum = pow((b.GetX() - a.GetX()), 2) + pow((b.GetY() - a.GetY()), 2) + pow((b.GetZ() - a.GetZ()), 2) + pow((b.GetW() - a.GetW()), 2);
		return sqrt(sum);
	}

	static float Dot(Vector4 a, Vector4 b) {
		float i = a.GetX() * b.GetX();
		float j = a.GetY() * b.GetY();
		float k = a.GetZ() * b.GetZ();
		float l = a.GetW() * b.GetW();
		return i + j + k + l;
	}

	static Vector4 Cross(Vector4 a, Vector4 b) {

		return Vector4Math::Zero();
	}

	static Vector4 IncreaseBy(Vector4 v, float factor) {
		float i = v.GetX() * factor;
		float j = v.GetY() * factor;
		float k = v.GetZ() * factor;
		float l = v.GetW() * factor;
		Vector4 increasedV(i, j, k, l);
		return increasedV;
	}

	static Vector4 AngleBetween() {

	}

	static Vector4 One() {
		return Vector4(1, 1, 1, 1);
	}

	static Vector4 Zero() {
		return Vector4(0, 0, 0, 0);
	}

};