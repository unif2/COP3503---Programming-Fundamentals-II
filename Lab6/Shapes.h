#pragma once
#include <string>
using std::string;

const float PI = 3.14159f;

class Shape
{
	public:
		virtual void Scale(float scaleFactor) = 0;
		virtual void Display() const = 0;
		virtual ~Shape();
};

class Shape2D : virtual public Shape
{
	public:
		virtual float Area() const = 0;
		void ShowArea() const;
		virtual string GetName2D() const = 0;
		bool operator>(const Shape2D& rhs) const;
		bool operator<(const Shape2D& rhs) const;
		bool operator==(const Shape2D& rhs) const;
};

class Shape3D : virtual public Shape
{
	public:
		virtual float Volume() const = 0;
		void ShowVolume() const;
		virtual string GetName3D() const = 0;
		bool operator>(const Shape3D& rhs) const;
		bool operator<(const Shape3D& rhs) const;
		bool operator==(const Shape3D& rhs) const;
};

class Square : public Shape2D
{
	float _sideLength;
	
	public:
		Square();
		Square(float sideLength);
		void Scale(float scaleFactor);
		void Display() const;
		float Area() const;
		string GetName2D() const;
};

class Triangle : public Shape2D
{
	float _base;
	float _height;
	
	public:
		Triangle();
		Triangle(float base, float height);
		void Scale(float scaleFactor);
		void Display() const;
		float Area() const;
		string GetName2D() const;
};

class Circle : public Shape2D
{
	float _radius;
	
	public:
		Circle();
		Circle(float radius);
		void Scale(float scaleFactor);
		void Display() const;
		float Area() const;
		string GetName2D() const;
		float GetRadius() const;
};

class TriangularPyramid : public Shape3D, private Triangle
{
	float _height;
	
	public:
		TriangularPyramid();
		TriangularPyramid(float height, float triBase, float triHeight);
		void Scale(float scaleFactor);
		void Display() const;
		float Volume() const;
		string GetName3D() const;
};

class Cylinder : public Shape3D, private Circle
{
	float _height;
	
	public:
		Cylinder();
		Cylinder(float height, float radius);
		void Scale(float scaleFactor);
		void Display() const;
		float Volume() const;
		string GetName3D() const;
};

class Sphere : public Shape3D, private Circle
{
	public:
		Sphere();
		Sphere(float radius);
		void Scale(float scaleFactor);
		void Display() const;
		float Volume() const;
		string GetName3D() const;
};