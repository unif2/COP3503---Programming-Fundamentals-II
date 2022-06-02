#pragma once
#include <string>
using std::string;

class Lego
{
	private:
		int _number;
		string _theme;
		string _name;
		int _miniFigs;
		int _pieces;
		double _price;
		
	public:
		Lego();
		Lego(int number, string theme, string name, int miniFigs, int pieces, double price);
		int getNumber();
		string getTheme();
		string getName();
		int getMiniFigs();
		int getPieces();
		double getPrice();
		void print();
		void printOneLine();
};