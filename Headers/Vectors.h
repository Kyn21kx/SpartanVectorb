#pragma once
#include "Utilities.h"

class Vector3 {
public:
	float r = 0.0f, g = 0.0f, b = 0.0f;
	Vector3() {
		Initialize(0, 0, 0);
	}

	Vector3 (float _x, float _y, float _z) {
		Initialize(_x, _y, _z);
	}
	
	//Returns a normalized version of the vector
	Vector3 Normalized() const {
		return Vector3(x / magnitude, y / magnitude, z / magnitude);
	}
	//Normalizes this vector (changing cartesian values)
	void Normalize() {
		SetValues(x / magnitude, y / magnitude, z / magnitude);
	}

	//Sets the values of cartesian properties of the vector (x, y, z)
	void SetValues(float _x, float _y, float _z) {
		Initialize(_x, _y, _z);
	}
	//Returns X component of the vector
	float GetX() const {
		return x;
	}
	//Returns Y component of the vector
	float GetY() const {
		return y;
	}
	//Returns Z component of the vector
	float GetZ() const {
		return z;
	}
	//Returns the magnitude of the vector
	float GetMagnitude() const {
		return magnitude;
	}

	//Displays an ImGUI window for the properties of the vector with the specified vector name
	void DisplayPropertiesWindow(const char* vName) {
		{
			static bool sliderInput = true;
			std::string nameBuffer = "Vector properties of ";
			nameBuffer.append(vName);
			ImGui::Begin(nameBuffer.c_str());
			ImGui::Checkbox("Slider input", &sliderInput);      // Edit bools storing our window open/close state
			if (ImGui::Button("Manual setup")) {
				std::cout << "Set X: ";
				std::cin >> x;
				std::cout << "Set Y: ";
				std::cin >> y;
				std::cout << "Set Z: ";
				std::cin >> z;
			}
			ImGui::Text("Color of the vector: ");
			ImGui::SliderFloat("R", &r, 0.0f, 1.0f);
			ImGui::SliderFloat("G", &g, 0.0f, 1.0f);
			ImGui::SliderFloat("B", &b, 0.0f, 1.0f);
			if (sliderInput) {
				ImGui::SliderFloat("X", &x, -50.0f, 50.0f);
				ImGui::SliderFloat("Y", &y, -50.0f, 50.0f);
				ImGui::SliderFloat("Z", &z, -50.0f, 50.0f);
			}
			else {
				ImGui::DragFloat("X", &x);
				ImGui::DragFloat("Y", &y);
				ImGui::DragFloat("Z", &z);
			}
			ImGui::Text("Magnitude: %f", this->GetMagnitude());
			if (*this != Vector3(0,0,0)) {
				ImGui::Text("Normalized vector: ");
				ImGui::Text(this->Normalized().ToString().c_str());
				ImGui::Text("Theta angle = %f", this->GetAngle());
			}
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
			SetValues(x, y, z);
		}
	}

	std::string ToString() const {
		std::string strVec = "(" + ConvertToString<float>(x) + ", " + ConvertToString<float>(y) + ", " + ConvertToString<float>(z) + ")";
		return strVec;
	}

	float GetAngle() const {
		return angle;
	}
	//Returns scalar multiplication
	Vector3 operator * (const float factor) const {
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

	Vector3 operator + (const Vector3 v) const {
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

	Vector3 operator - (const Vector3 v) const {
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

	bool operator == (const Vector3 v) const {
		return (x == v.x && y == v.y && z == v.z);
	}
	bool operator != (const Vector3 v) const {
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

	static const Vector3 One() {
		return Vector3(1, 1, 1);
	}

	static const Vector3 Zero() {
		return Vector3(0, 0, 0);
	}
	//Displays an ImGui window that manages vector math
	static void CalculationsWindow(std::vector<Vector3> &vList) {
		{
			#pragma region Variables
			static std::string strDis = "distance = ";
			static std::string strDisAp = "";
			static unsigned int winMapRef;
			static WindowCalculations winEnumRef;
			static int selectedId = 0, selectedId2 = 0;
			#pragma endregion

			ImGui::Begin("Vector calculations");
			ImGui::CheckboxFlags("Distance between two vectors", &winMapRef, 1);
			ImGui::CheckboxFlags("Dot product", &winMapRef, 2);
			ImGui::CheckboxFlags("Cross product", &winMapRef, 4);

			winEnumRef = (WindowCalculations)winMapRef;

			switch (winEnumRef) {
			case WindowCalculations::_Distance:
				ImGui::Text("Distance operation:");
				ImGui::DragInt("Id Vector A", &selectedId);
				ImGui::DragInt("Id Vector B", &selectedId2);
				if (ImGui::Button("Get distance")) {
					std::cout << "Id Vector A: ";
					std::cin >> selectedId;
					std::cout << "Id Vector B: ";
					std::cin >> selectedId2;
					strDisAp = std::to_string(Distance(vList[selectedId], vList[selectedId2]));
				}
				strDis = "distance = " + strDisAp;
				ImGui::Text(strDis.c_str());
				break; 
			case WindowCalculations::_Dot:
					
					break;
			case WindowCalculations::_Cross:
				ImGui::Text("Distance operation:");
				ImGui::DragInt("Id Vector A", &selectedId);
				ImGui::DragInt("Id Vector B", &selectedId2);
				if (ImGui::Button("Get cross product")) {
					std::cout << "Id Vector A: ";
					std::cin >> selectedId;
					std::cout << "Id Vector B: ";
					std::cin >> selectedId2;
					vList.push_back(Vector3Math::Cross(vList[selectedId], vList[selectedId2]));
				}
				break;
			}
			ImGui::End();
		}
	}
private:
	enum class WindowCalculations {
		None,
		_Distance,
		_Dot,
		_Cross = 4,
	};

};