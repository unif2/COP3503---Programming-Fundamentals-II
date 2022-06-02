#include <iostream>
#include "Shapes.h"
using std::cout;
using std::endl;

Shape::~Shape(){}

void Shape2D::ShowArea() const
{
	cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
}

bool Shape2D::operator>(const Shape2D& rhs) const
{
	if (Area() > rhs.Area())
		return true;
	
	return false;
}

bool Shape2D::operator<(const Shape2D& rhs) const
{
	if (Area() < rhs.Area())
		return true;
	
	return false;
}

bool Shape2D::operator==(const Shape2D& rhs) const
{
	if (Area() == rhs.Area())
		return true;
	
	return false;
}

void Shape3D::ShowVolume() const
{
	cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
}

bool Shape3D::operator>(const Shape3D& rhs) const
{
	if (Volume() > rhs.Volume())
		return true;
	
	return false;
}

bool Shape3D::operator<(const Shape3D& rhs) const
{
	if (Volume() < rhs.Volume())
		return true;
	
	return false;
}

bool Shape3D::operator==(const Shape3D& rhs) const
{
	if (Volume() == rhs.Volume())
		return true;
	
	return false;
}

Square::Square()
{
	_sideLength = 0.0;
}

Square::Square(float sideLength)
{
	_sideLength = sideLength;
}

void Square::Scale(float scaleFactor)
{
	_sideLength *= scaleFactor;
}

void Square::Display() const
{
	ShowArea();
	cout << "Length of a side: " << _sideLength << endl;
}

float Square::Area() const
{
	return _sideLength * _sideLength;
}

string Square::GetName2D() const
{
	return "Square";
}

Triangle::Triangle()
{
	_base = 0.0;
	_height = 0.0;
}

Triangle::Triangle(float base, float height)
{
	_base = base;
	_height = height;
}

void Triangle::Scale(float scaleFactor)
{
	_base *= scaleFactor;
	_height *= scaleFactor;
}

void Triangle::Display() const
{
	ShowArea();
	cout << "Base: " << _base << endl;
	cout << "Height: " << _height << endl;
}

float Triangle::Area() const
{
	return (0.5) * _base * _height;
}

string Triangle::GetName2D() const
{
	return "Triangle";
}

Circle::Circle()
{
	_radius = 0.0;
}

Circle::Circle(float radius)
{
	_radius = radius;
}

void Circle::Scale(float scaleFactor)
{
	_radius *= scaleFactor;
}

void Circle::Display() const
{
	ShowArea();
	cout << "Radius: " << _radius << endl;
}

float Circle::Area() const
{
	return PI * _radius * _radius;
}

string Circle::GetName2D() const
{
	return "Circle";
}

float Circle::GetRadius() const
{
	return _radius;
}

TriangularPyramid::TriangularPyramid()
{
	_height = 0.0;
}

TriangularPyramid::TriangularPyramid(float height, float triBase, float triHeight) : Triangle(triBase, triHeight)
{
	_height = height;
}

void TriangularPyramid::Scale(float scaleFactor)
{
	Triangle::Scale(scaleFactor);
	_height *= scaleFactor;
}

void TriangularPyramid::Display() const
{
	ShowVolume();
	cout << "The height is: " << _height << endl;
	Triangle::Display();
}

float TriangularPyramid::Volume() const
{
	return (1.0 / 3.0) * _height * Area();
}

string TriangularPyramid::GetName3D() const
{
	return "TriangularPyramid";
}

Cylinder::Cylinder()
{
	_height = 0.0;
}

Cylinder::Cylinder(float height, float radius) : Circle(radius)
{
	_height = height;
}

void Cylinder::Scale(float scaleFactor)
{
	Circle::Scale(scaleFactor);
	_height *= scaleFactor;
}

void Cylinder::Display() const
{
	ShowVolume();
	cout << "The height is: " << _height << endl;
	Circle::Display();
}

float Cylinder::Volume() const
{
	return _height * Area();
}

string Cylinder::GetName3D() const
{
	return "Cylinder";
}

Sphere::Sphere(){}

Sphere::Sphere(float radius) : Circle(radius){}

void Sphere::Scale(float scaleFactor)
{
	Circle::Scale(scaleFactor);
}

void Sphere::Display() const
{
	ShowVolume();
	Circle::Display();
}

float Sphere::Volume() const
{
	return (4.0 / 3.0) * Circle::Area() * GetRadius();
}

string Sphere::GetName3D() const
{
	return "Sphere";
}