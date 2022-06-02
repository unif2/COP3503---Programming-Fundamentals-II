#include <iostream>
#include "Vehicle.h"
using std::cout;
using std::endl;
using std::to_string;

Vehicle::Vehicle()
{
	_make = "COP3503";
	_model = "Rust Bucket";
	_year = 1900;
	_price = 0;
	_mileage = 0;
}

Vehicle::Vehicle(string make, string model, unsigned int year, float price, unsigned int mileage)
{
	_make = make;
	_model = model;
	_year = year;
	_price = price;
	_mileage = mileage;
}

void Vehicle::Display()
{
	cout << _year << " " << _make << " " << _model << " " << "$" << _price << " " << _mileage << endl;
}

string Vehicle::GetYearMakeModel()
{
	return to_string(_year) + " " + _make + " " + _model;
}

float Vehicle::GetPrice()
{
	return _price;
}
	

