#include <iostream>
#include "Showroom.h"
using std::cout;
using std::endl;

Showroom::Showroom()
{
   _name = "Unnamed Showroom";
   _capacity = 0;
}

Showroom::Showroom(string name, unsigned int capacity)
{
	_name = name;
	_capacity = capacity;
}

vector<Vehicle> Showroom::GetVehicleList()
{
	return _vehicles;
}

void Showroom::AddVehicle(Vehicle v)
{
	if (_vehicles.size() == _capacity)
		cout << "Showroom is full! Cannot add " << v.GetYearMakeModel() << endl;
	
	else
		_vehicles.push_back(v);
}

void Showroom::ShowInventory()
{
	if (_vehicles.size() == 0)
		cout << _name << " is empty!" << endl;
	
	else
	{
	   cout << "Vehicles in " << _name << endl;
		for (Vehicle& v: _vehicles)
		   v.Display();
	}
}

float Showroom::GetInventoryValue()
{
	float totalValue = 0;
	
	for (Vehicle& v: _vehicles)
		totalValue += v.GetPrice();
	
	return totalValue;
}