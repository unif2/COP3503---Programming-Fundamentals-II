#pragma once
#include <string>
using std::string;

class Vehicle
{
	private:
		string _make;
		string _model;
		unsigned int _year;
		float _price;
		unsigned int _mileage;
	
	public:
		Vehicle();
		Vehicle(string make, string model, unsigned int year, float price, unsigned int mileage);
		void Display();
		string GetYearMakeModel();
		float GetPrice();
};