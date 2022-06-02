#include <iostream>
#include "Hero.h"
using std::cout;
using std::endl;

Hero::Hero(string name, int hp, int strength)
{
	
_name = name;
_hitpoints = hp;
_maximumHitpoints = _hitpoints;
_strength = strength;
_level = 1;
_experiencePoints = 0;

}

Hero& Hero::operator=(const Hero& other)
{
	_name = other._name;
	_hitpoints = other._hitpoints;
	_maximumHitpoints = other._maximumHitpoints;
	_strength = other._strength;
	_level = other._level;
	_experiencePoints = other._experiencePoints;
	
	return *this;
}

void Hero::Print()
{
	cout << "Name: " << _name << endl;
	cout << "HP: " << _hitpoints << endl;
	cout << " / ";
	cout << _maximumHitpoints << endl;
	
	cout << "Strength: " << _strength << endl;
	cout << "Attack Power: " << GetAttackPower() << endl;
	cout << "Level: " << _level << endl;
	cout << "EXP: " << _experiencePoints << endl;
}

string Hero::GetName()
{
	return _name;
}

int Hero::GetHitpoints()
{
	return _hitpoints;
}

int Hero::GetStrength()
{
	return _strength;
}

int Hero::GetAttackPower()
{
	return _strength * 5;
	//return _level + _strength;
}

void Hero::TakeDamage(int damage)
{
	_hitpoints -= damage;
	if (_hitpoints < 0)
	{
		_hitpoints = 0;
	}
}

void Hero::CopyHPFromOtherHero(const Hero& other)
{
	_hitpoints = other._hitpoints;
	_maximumHitpoints = other._maximumHitpoints;
}

void Hero::Heal(int amount)
{
	_hitpoints += amount;
	
	if (_hitpoints > _maximumHitpoints)
		_hitpoints = _maximumHitpoints;
}

void Hero::GainExperience(int amount)
{
	_experiencePoints += amount;
	
	if (_experiencePoints >= EXP_NEEDED)
	{
		LevelUp();
		
		if (_experiencePoints >= EXP_NEEDED)
		{
			_experiencePoints -= EXP_NEEDED;
		}
	}
}

void Hero::LevelUp()
{
	_level++;
	
	_strength += rand() % 3 + 1;
	
	_maximumHitpoints += rand() % 6 + 5;
}

int Hero::GetLevel()
{
	return _level;
}

int Hero::GetXP
{
	return _experiencePoints;
}

float Hero::GetCritMult()
{
	return _criticalMultiplier;
}

float Hero::GetArmor()
{
	return _armor;
}