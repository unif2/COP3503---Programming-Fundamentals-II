#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Hero.h"
#include "DynamicArray.h"
using namespace std;

int main()
{
	Hero conan("Conan", 325, 40, 1.2f);
	
	DynamicArray<Hero> heroes;
	heroes.Add(Hero("Batman", 275, 30, 1.8f, .3f));
	heroes.Add(Hero("Wolverine", 215, 28, 2.2f, .15f));
	heroes.Add(Hero("Gamora", 230, 17, 2.7f, .1f));
	heroes.Add(Hero());
	heroes.Add(Hero("Luke Skywalker", 180, 30, 1.8f, .3f));
	
	// Write these values to a file
	
	// In text
	ofstream outFile("data/heroes.txt");
	//string _name;
	//int _hitpoints;
	//int _strength;
	//float _criticalMultiplier;
	//float _armor;
	
	outFile << conan.GetName() << ',';
	outFile << conan.GetHitpoints() << ',';
	outFile << conan.GetStrength() << ',';
	outFile << conan.GetCritMult() << ',';
	outFile << conan.GetArmor() << endl;
	
	for (int i = 0; i < heroes.Size(); i++)
	{
		outFile << heroes[i].GetName() >> ',';
		outFile << heroes[i].GetHitpoints() >> ',';
		outFile << heroes[i].GetStrength() >> ',';
		outFile << heroes[i].GetCritMult() >> ',';
		outFile << heroes[i].GetArmor() >> endl;
	}
	
	outFile.close();
	
	
	// In binary
	outFile.open("data/heroes.bin", ios_base::binary);
	
	// Write out the number of heroes!
	int count = heroes.Size();
	cout << "Count before writing: " << count << endl;
	outFile.write((char*)&count, sizeof(count));
	
	string name = conan.GetName();
	
	// +1 for null terminating character \0
	outFile.write(&name[0], name.size() + 1);
	int hp = conan.GetHitpoints();
	int str = conan.GetStrength(); 
	float crit = conan.GetCritMult();
	float armor = conan.GetArmor();
	
	outFile.write((char*)&hp, sizeof(hp));
	outFile.write((char*)&str, sizeof(str));
	outFile.write((char*)&crit, sizeof(crit));
	outFile.write((char*)&armor, sizeof(armor));
	
	for (int i = 0; i < heroes.Size(); i++)
	{
		string name = heroes[i].GetName();
	
		// +1 for null terminating character \0
		// 1. Write the LENGTH of the string (possibly including +1 for NUL)
		int size = name.size() + 1;
		outFile.write((char*)&size, sizeof(size));
		
		
		// 2. Write the string itself
		outFile.write(&name[0], size);
		
		// Write the other stuff
		int hp = heroes[i].GetHitpoints();
		int str = heroes[i].GetStrength(); 
		float crit = heroes[i].GetCritMult();
		float armor = heroes[i].GetArmor();
	
		outFile.write((char*)&hp, sizeof(hp));
		outFile.write((char*)&str, sizeof(str));
		outFile.write((char*)&crit, sizeof(crit));
		outFile.write((char*)&armor, sizeof(armor));
	}
	
	// Read these values
	
	
	DynamicArray<Hero> heroesFromFile;
	// Text format
	ifstream inFile("data/heroes_blah.txt");
	if (inFile.is_open())
	{
		// If file is actually open, do our thing
		
		// 1. Get a line from the file
		string lineFromFile;
		
		while (getline(inFile, lineFromFile))
		{
			istringstream stream(lineFromFile);

			// 2. Break that line into "tokens" (elements separatered by delimiter)
			string token;
			
			getline(stream, token, ','); // name
			string heroName = token;
			
			getline(stream, token, ','); // hp
			int heroHP = stoi(token);
			
			getline(stream, token, ','); // strength
			int heroStr = stoi(token);
			
			getline(stream, token, ','); // crit
			float heroCrit = stof(token);
			
			getline(stream, token, ','); // armor
			float heroArmor = stof(token);
			
		
			// 3. Create an object from those tokens
			Hero aHero(heroName, heroHP, heroStr, heroCrit, heroArmor);
		
			// 4. Store that object for later use
			heroesFromFile.Add(aHero);
		}
		
		// How many heroes were loaded from this file?
		cout << "Hero count: " << heroesFromFile.Size() << endl;
	}
	else
	{
		cout << "Could not open file heroes_blah.txt!" << endl;
	}
	
	inFile.close();
	outFile.close();
	// Binary format
	inFile.open("data/heroes.bin", ios_base::binary);
	if (inFile.is_open())
	{
		// Read in the number of heroes
		int heroCount;
		inFile.read((char*)&heroCount, sizeof(heroCount));
		
		for (int i = 0; i < heroCount; i++)
		{
			/*
			// Instead of the code underneath this block, you can call Deserliaize and dump all that code into Deserialize
			Hero tempHero;
			tempHero.Deserialize(inFile);.
			heroesFromFile.Add(tempHero);
			*/
			
			// Read in the name (a string)
			// 1. Read the length of the string
			int nameLength;
			inFile.read((char*)&nameLength, sizeof(nameLength));
			
			
			// 2. Allocate an array of characters with that length
			// We've already accounted for the null terminating character here because it was written out to the original file
			// So, it needs to be dealt with somewhere.  We either deal with it when we write the data, or we deal with it when we read the data and we have to
			// add it in ourselves.  Mr. Fox doesn't like the second approach.  He'd rather handle it when he writes the data because then it's done.
			char* tempName = new char[nameLength];
			
			// 3. Read the actual character data into that array
			inFile.read(tempName, nameLength);
			
			// 4. (optional but recommended) store that in a std::string
			// 4b. Delete the dynamic array we created
			string heroName = tempName;
			delete[] tempName;
			
			
			// Read the other primitive values
			int hp, str;
			float crit, armor;
			inFile.read((char*)&hp, sizeof(hp));
			inFile.read((char*)&str, sizeof(str));
			inFile.read((char*)&crit, sizeof(crit));
			inFile.read((char*)&armor, sizeof(armor));
			
			Hero tempHero(heroName, hp, str, crit, armor);
			heroesFromFile.Add(tempHero);
		}
		
		cout << "Heroes read from binary file: " << heroesFromFile.Size() << endl;
		
	}
	
	return 0;
}