#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Starship
{
	public:
		class Armament
		{
			private:
				string _weapName; // Name of weapon
				int _rating; // Power rating of weapon
				float _consumption; // Power consumption of weapon
				
			public:
				Armament();
				Armament(string weapName, int rating, float consumption);
				string getWeapName();
				int getRating();
				float getConsumption();
		};
	
	private:
		string _name; // Name of ship
		string _class; // Class of ship
		short _length; // Length of ship
		int _capacity; // Shield capacity of ship
		float _maxWarp; // Maximum warp speed of ship
		vector<Armament> _weapons; // All weapons on the ship
		
	public:
		Starship();
		Starship(string name, string shipClass, short length, int capacity, float maxWarp);
		string getName();
		string getClass();
		short getLength();
		int getCapacity();
		float getMaxWarp();
		vector<Armament> getWeapons(); // Returns a vector of weapons the ship has
		int getTotalRating(); // Returns the sum of power ratings for all weapons on the ship
		void print();
		void AddWeapon(string weapName, int rating, float consumption); // Adds a weapon to the ship
		int getHighestPowerRating(); // Returns the highest power rating of the ship
};