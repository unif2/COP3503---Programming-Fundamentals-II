#include <iostream>
#include <fstream>
#include "Starship.h"
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ios_base;

const vector<Starship> shipsFromFile(int option); // Returns a vector of Starship objects from the specified file(s)
const vector<Starship> readShipData(ifstream& inputFile); // Reads the data from the given file, creates Starship objects, and returns a vector of Starship objects
const Starship strongestWeap(vector<Starship>& ships); // Returns the Starship object from the vector having the strongest weapon
const Starship strongestShip(vector<Starship>& ships); // Returns the Starship object from the vector having the highest combined power rating
const Starship weakestShip(vector<Starship>& ships); // Returns the Starship object from the vector having the lowest combined power rating
void printUnarmedShips(vector<Starship>& ships); // Prints all unarmed Starship objects from the vector of Starship objects

int main()
{

	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;
	
	if (option < 1 || option > 3)
	{
		cout << "Invalid choice!  Bye!" << endl;
		return -1;
	}

   /* Load files here */
   vector<Starship> ships = shipsFromFile(option);

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;
	
	cin >> option;
	
	/* Work your magic here */
	switch (option)
	{
		case 1:
		{
			for (unsigned int i = 0; i < ships.size(); i++)
				ships[i].print();
			break;
		}
		
		case 2:
		{
			Starship ship = strongestWeap(ships);
			ship.print();
			break;
		}
		
		case 3:
		{
			Starship ship = strongestShip(ships);
			ship.print();
			break;
		}
		
		case 4:
		{
			Starship ship = weakestShip(ships);
			ship.print();
			break;
		}
		
		case 5:
		{
			printUnarmedShips(ships);
			break;
		}
	}
   return 0;
}

const vector<Starship> shipsFromFile(int option)
{
	vector<Starship> ships;
	vector<vector<Starship>> allShips;
	vector<string> files{"friendlyships.shp", "enemyships.shp"};
	string filename;
	
	if (option == 1)
	{
		filename = files[0];
		ifstream inputFile;
		inputFile.open(filename, ios_base::binary);

		if (inputFile.is_open())
			ships = readShipData(inputFile);
	}
	else if (option == 2)
	{
		filename = files[1];
		ifstream inputFile;
		inputFile.open(filename, ios_base::binary);

		if (inputFile.is_open())
			ships = readShipData(inputFile);
	}
	else
	{
		for (int i = 0; i < 2; i++) // Loop through both files, get the vector of ships for each file, put in allShips
		{
			filename = files[i];
			ifstream inputFile;
			inputFile.open(filename, ios_base::binary);

			if (inputFile.is_open())
				allShips.push_back(readShipData(inputFile));
		}
		
		for (unsigned int i = 0; i < allShips.size(); i++) // Loop through the two vectors in allShips and combine all ships into one vector
		{
			for (unsigned int j = 0; j < allShips[i].size(); j++)
				ships.push_back(allShips[i][j]);
		}	
	}
	return ships;
}

const vector<Starship> readShipData(ifstream& inputFile)
{
	vector<Starship> ships;
	unsigned int shipCount;
	inputFile.read((char*)&shipCount, 4);
			
	for (unsigned int i = 0; i < shipCount; i++)
	{
		int nameLength;
		inputFile.read((char*)&nameLength, 4);
				
		char* tempName = new char[nameLength];
		inputFile.read(tempName, nameLength);

		string shipName = tempName;
		delete[] tempName;
				
		int classLength;
		inputFile.read((char*)&classLength, 4);
				
		tempName = new char[classLength];
		inputFile.read(tempName, classLength);
				
		string shipClass = tempName;
		delete[] tempName;
				
		short shipLength;
		inputFile.read((char*)&shipLength, 2);
				
		int shipCapacity;
		inputFile.read((char*)&shipCapacity, 4);
				
		float shipWarp;
		inputFile.read((char*)&shipWarp, 4);
				
		Starship ship(shipName, shipClass, shipLength, shipCapacity, shipWarp);
				
		unsigned int weaponCount;
		inputFile.read((char*)&weaponCount, 4);
				
		for (unsigned int i = 0; i < weaponCount; i++)
		{
			int weapNameLength;
			inputFile.read((char*)&weapNameLength, 4);
				
			tempName = new char[weapNameLength];
			inputFile.read(tempName, weapNameLength);
				
			string weaponName = tempName;
			delete[] tempName;
				
			int weapRating;
			inputFile.read((char*)&weapRating, 4);
				
			float powConsumption;
			inputFile.read((char*)&powConsumption, 4);
					
			ship.AddWeapon(weaponName, weapRating, powConsumption);
		}
		ships.push_back(ship);
	}
	return ships;
}

const Starship strongestWeap(vector<Starship>& ships)
{
	int maxRating = ships[0].getHighestPowerRating();
	unsigned int index = 0;
	
	for (unsigned int i = 0; i < ships.size(); i++)
	{
		int highestRating = ships[i].getHighestPowerRating();
		if (highestRating > maxRating)
		{
			maxRating = highestRating;
			index = i;
		}
	}
	return ships[index];
}

const Starship strongestShip(vector<Starship>& ships)
{
	int maxTotalRating = ships[0].getTotalRating();
	unsigned int index = 0;
	
	for (unsigned int i = 0; i < ships.size(); i++)
	{
		int totalRating = ships[i].getTotalRating();
		if (totalRating > maxTotalRating)
		{
			maxTotalRating = totalRating;
			index = i;
		}
	}
	return ships[index];
}

const Starship weakestShip(vector<Starship>& ships)
{
	vector<Starship> armedShips;
	
	for (unsigned int i = 0; i < ships.size(); i++)
	{
		if (ships[i].getWeapons().size() > 0)
			armedShips.push_back(ships[i]);
	}
	
	int minTotalRating = armedShips[0].getTotalRating();
	unsigned int index = 0;
	
	for (unsigned int i = 0; i < armedShips.size(); i++)
	{
		int totalRating = armedShips[i].getTotalRating();
		if (totalRating < minTotalRating)
		{
			minTotalRating = totalRating;
			index = i;
		}
	}
	return armedShips[index];
}

void printUnarmedShips(vector<Starship>& ships)
{
	for (unsigned int i = 0; i < ships.size(); i++)
	{
		vector<Starship::Armament> weapons = ships[i].getWeapons();
		if (weapons.size() == 0)
			ships[i].print();
	}
}