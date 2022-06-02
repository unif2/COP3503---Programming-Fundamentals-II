#pragma once
#include "Showroom.h"

class Dealership
{
	private:
		string _name;
		vector<Showroom> _showrooms;
		unsigned int _capacity;
		
	public:
		Dealership();
		Dealership(string name, unsigned int capacity);
		void AddShowroom(Showroom s);
		float GetAveragePrice();
		void ShowInventory();
};