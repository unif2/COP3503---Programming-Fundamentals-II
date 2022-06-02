#include <iostream>
#include <string>
#include "Hero.h"
using namespace std;

int main()
{
	Hero conan("Conan", 100);
	
	Hero copy = conan; // Copy assignment operator
	Hero bob("Bob", 24);
	
	/*
	bob.GainExperience(1500);
	conan.TakeDamage(45);
	
	conan.Print(); // 55 hitpoints
	copy.Print(); // 100 hitpoints, all other variables the same as those of conan at the time of copying
	
	cout << "Memory address of Conan: " << &conan << endl;
	cout << "Memory address of copy: " << &copy << endl; // Should be different from conan'sb_type
	
	cout << "Creating a copy of our wounded hero..." << endl;
	Hero damagedCopy = conan;
	damagedCopy.Print(); // 55 hitpoints
	cout << "Memory address of damaged copy: " << &damagedCopy << endl; // Different from conan and copy
	
	conan.Print();
	bob.Print();
	
	cout << "Copying bob to Conan..." << endl;
	conan = bob; // copy assignment operator
	
	conan.Print();
	
	*/
	bob.GainExperience(1500);
	conan.Print();
	bob.Print();
	
	cout << "Copying bob to Conan..." << endl;
	conan = bob; // copy assignment operator
	conan.Print(); // should have same values as bob
	conan.CopyHPFromOtherHero(bob);
	
	return 0;
}