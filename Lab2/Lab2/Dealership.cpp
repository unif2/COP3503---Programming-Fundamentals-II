#include <iostream>
#include "Dealership.h"
using std::cout;
using std::endl;

Dealership::Dealership()
{
	_name = "Generic Dealership";
	_capacity = 0;
}

Dealership::Dealership(string name, unsigned int capacity)
{
	_name = name;
	_capacity = capacity;
}

void Dealership::AddShowroom(Showroom s)
{
	if (_showrooms.size() == _capacity)
		cout << "Dealership is full, can't add another showroom!" << endl;
	
	else
		_showrooms.push_back(s);
}

float Dealership::GetAveragePrice()
{
	float totalValue = 0;
	float sumVehicles = 0;
	
	for (Showroom& s: _showrooms)
	{
		totalValue += s.GetInventoryValue();
		sumVehicles += s.GetVehicleList().size();
	}
	
	if (sumVehicles == 0)
	{
		cout << _name << " is empty!" << endl;
		return sumVehicles;
	}
	
	return totalValue / sumVehicles;
}

void Dealership::ShowInventory()
{
	if (_showrooms.size() == 0)
	{
		cout << _name << " is empty!" << endl;
		cout << "Average car price: $0.00";
		return;
	}
	
	for (Showroom& s: _showrooms)
	{
		s.ShowInventory();
		cout << endl;
	}
	
	cout << "Average car price: " << "$" << this->GetAveragePrice();
}
		
		