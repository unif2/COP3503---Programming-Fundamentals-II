#include <iostream>
#include "Starship.h"
using std::cout;
using std::endl;

/*==== Starship Class Functions ====*/

Starship::Starship()
{
	_name = "";
	_class = "";
	_length = 0;
	_capacity = 0;
	_maxWarp = 0.0;
}

Starship::Starship(string name, string shipClass, short length, int capacity, float maxWarp)
{
	_name = name;
	_class = shipClass;
	_length = length;
	_capacity = capacity;
	_maxWarp = maxWarp;
}

string Starship::getName()
{
	return _name;
}

string Starship::getClass()
{
	return _class;
}

short Starship::getLength()
{
	return _length;
}

int Starship::getCapacity()
{
	return _capacity;
}

float Starship::getMaxWarp()
{
	return _maxWarp;
}

vector<Starship::Armament> Starship::getWeapons()
{
	return _weapons;
}

int Starship::getTotalRating()
{
	int sumRating = 0;
	
	for (unsigned int i = 0; i < _weapons.size(); i++)
		sumRating += _weapons[i].getRating();
	
	return sumRating;
}

void Starship::print()
{
	cout << "Name: " << _name << endl;
	cout << "Class: " << _class << endl;
	cout << "Length: " << _length << endl;
	cout << "Shield capacity: " << _capacity << endl;
	cout << "Maximum Warp: " << _maxWarp << endl;
	cout << "Armaments:" << endl;
	
	if (_weapons.size() == 0)
	{
		cout << "Unarmed" << endl;
	}
	else
	{
		for (unsigned int i = 0; i < _weapons.size(); i++)
			cout << _weapons[i].getWeapName() << ", " << _weapons[i].getRating() << ", " << _weapons[i].getConsumption() << endl;
		
		cout << "Total firepower: " << this->getTotalRating() << endl;
	}
}

void Starship::AddWeapon(string weapName, int rating, float consumption)
{
	Armament weapon(weapName, rating, consumption); // Create Armament object
	_weapons.push_back(weapon);
}

int Starship::getHighestPowerRating()
{
	if (_weapons.size() == 0)
		return 0;
	
	int maxRating = _weapons[0].getRating();
	
	for (unsigned int i = 0; i < _weapons.size(); i++)
	{
		int rating = _weapons[i].getRating();
		if (rating > maxRating)
			maxRating = rating;
	}
	
	return maxRating;
}

/*==== Armament Class Functions ====*/
	
Starship::Armament::Armament()
{
	_weapName = "";
	_rating = 0;
	_consumption = 0.0;
}

Starship::Armament::Armament(string weapName, int rating, float consumption)
{
	_weapName = weapName;
	_rating = rating;
	_consumption = consumption;
}

string Starship::Armament::getWeapName()
{
	return _weapName;
}

int Starship::Armament::getRating()
{
	return _rating;
}

float Starship::Armament::getConsumption()
{
	return _consumption;
}