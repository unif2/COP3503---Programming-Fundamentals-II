#pragma once
#include <string>
using std::string;

class Hero
{
	// This section is private by default
	string _name;
	int _hitpoints;
	int _maximumHitpoints;
	int _strength;
	float _criticalMultiplier;
	float _armor;
	
	// Leveling variables
	int _level;
	int _experiencePoints;
	
	const int EXP_NEEDED = 1000;
	
	// Private function, no one can use this outside of this class
	void LevelUp();
	
	public:
	Hero(string name = "Bob", int hp = 100, int strength = 1);
	Hero& operator=(const Hero& other);
	void Print();
	
	// Accessors
	string GetName();
	int GetHitpoints();
	int GetStrength();
	int GetAttackPower();
	int GetLevel();
	int GetXP;
	float GetCritMult();
	float GetArmor();
	
	// Mutators
	void TakeDamage(int damage);
	void Heal(int amount);
	
	void GainExperience(int amount);
	
	void CopyHPFromOtherHero(const Hero& other);
	
	// Serialization
	void Serialize(ofstream& outputFile);
	void Deserialize(ifstream& inputFile);
	
	
	
};