#pragma once
#include <vector>
#include "Vehicle.h"
using std::vector;

class Showroom
{
	private:
		string _name;
		vector<Vehicle> _vehicles;
		unsigned int _capacity;
		
	public:
		Showroom();
		Showroom(string name, unsigned int capacity);
		vector<Vehicle> GetVehicleList();
		void AddVehicle(Vehicle v);
		void ShowInventory();
		float GetInventoryValue();
};