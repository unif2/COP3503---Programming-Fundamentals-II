#include <iostream>
#include "Lego.h"
using std::cout;
using std::endl;

Lego::Lego()
{
	_number = 0;
	_theme = "";
	_name = "";
	_miniFigs = 0;
	_pieces = 0;
	_price = 0.0;
}

Lego::Lego(int number, string theme, string name, int miniFigs, int pieces, double price)
{
	_number = number;
	_theme = theme;
	_name = name;
	_miniFigs = miniFigs;
	_pieces = pieces;
	_price = price;
}

int Lego::getNumber()
{
	return _number;
}

string Lego::getTheme()
{
	return _theme;
}

string Lego::getName()
{
	return _name;
}

int Lego::getMiniFigs()
{
	return _miniFigs;
}

int Lego::getPieces()
{
	return _pieces;
}

double Lego::getPrice()
{
	return _price;
}

void Lego::print()
{
	cout << "Name: " << _name << endl;
	cout << "Number: " << _number << endl;
	cout << "Theme: " << _theme << endl;
	cout << "Price: $" << _price << endl;
	cout << "Minifigures: " << _miniFigs << endl;
	cout << "Piece count: " << _pieces << endl;
}

void Lego::printOneLine()
{
	cout << _number << " " << _name << " $" << _price << endl;
}