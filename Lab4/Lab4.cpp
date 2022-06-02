#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Lego.h"
using namespace std;

const vector<Lego> legosFromFile(int option); // Returns a vector of Lego objects from the file(s)
const Lego legoFromLine(string line); // Returns a Lego object obtained from one line of a file
const Lego mostExpensive(vector<Lego>& legos); // Returns the most expensive Lego object from the vector
const Lego mostPieces(vector<Lego>& legos); // Returns the Lego object in the vector with the most pieces
const Lego leastExpensive(vector<Lego>& legos); // Returns the least expensive Lego object from the vector
const Lego mostMiniFigs(vector<Lego>& legos); // Returns the Lego object in the vector with the most minifigures
double sumPrices(vector<Lego>& legos); // Returns the total price of all Legos in the vector
int sumPieces(vector<Lego>& legos); // Returns the total number of pieces of all Legos in the vector
int sumMiniFigs(vector<Lego>& legos); // Returns the total number of minifigures of all Legos in the vector

int main()
{
	cout << std::fixed << setprecision(2);
	cout << "Which file(s) to open?\n";
	cout << "1. lego1.csv" << endl;
	cout << "2. lego2.csv" << endl;
	cout << "3. lego3.csv" << endl;
	cout << "4. All 3 files" << endl;
	int option;
	cin >> option;
	
	if (option < 1 || option > 4)
	{
		cout << "Invalid choice!  Bye!" << endl;
		return -1;
	}

	/*======= Load data from file(s) =======*/
	vector<Lego> legos = legosFromFile(option);

	cout << "1. Most Expensive set" << endl;
	cout << "2. Largest piece count" << endl;
	cout << "3. Search for set name containing..." << endl;
	cout << "4. Search themes..." << endl;
	cout << "5. Part count information" << endl;
	cout << "6. Price information" << endl;
	cout << "7. Minifigure information" << endl;
	cout << "8. If you bought one of everything..." << endl;
	cout << "0. Exit" << endl;
   
	int choice;
	cin >> choice;
	cin.get();  // Clear newline character for any later input
   
	/*======= Print out how many sets were loaded =======*/
	cout << "Total number of sets: " << legos.size() << endl << endl;
	
	/*======= Based on the choice, execute the appropriate task and show the results =======*/
	switch (choice)
	{
		case 0:
			break;
		
		case 1:
		{
			Lego lego = mostExpensive(legos);
			cout << "The most expensive set is:" << endl;
			lego.print();
			break;
		}
			
		case 2:
		{
			Lego lego = mostPieces(legos);
			cout << "The set with the highest parts count:" << endl;
			lego.print();
			break;
		}
			
		case 3:
		{
			string subStr;
			getline(cin, subStr); // Get a string from the user to search for and store in variable subStr
			vector<Lego> nameMatches; // A vector of Lego objects having a name that contains subStr
			string legoName; // Name of the Lego object
			
			for (unsigned int i = 0; i < legos.size(); i++)
			{
				legoName = legos[i].getName();
				if (legoName.find(subStr) != string::npos) // legoName contains subStr
					nameMatches.push_back(legos[i]);
			}
			
			if (nameMatches.size() > 0)
			{
				cout << "Sets matching \"" << subStr << "\":" << endl;
			
				for (unsigned int i = 0; i < nameMatches.size(); i++)
					nameMatches[i].printOneLine();
			}
			else
			{
				cout << "No sets found matching that search term" << endl;
			}
			break;
		}
			
		case 4:
		{
			string subStr;
			getline(cin, subStr); // Get a string from the user to search for and store in variable subStr
			vector<Lego> themeMatches; // A vector of Lego objects having a theme that contains subStr
			string legoTheme; // Theme of the Lego object
			
			for (unsigned int i = 0; i < legos.size(); i++)
			{
				legoTheme = legos[i].getTheme();
				if (legoTheme.find(subStr) != string::npos) // legoTheme contains subStr
					themeMatches.push_back(legos[i]);
			}
			if (themeMatches.size() > 0)
			{
				cout << "Sets matching \"" << subStr << "\":" << endl;
				
				for (unsigned int i = 0; i < themeMatches.size(); i++)
					themeMatches[i].printOneLine();
			}
			else
			{
				cout << "No sets found matching that search term" << endl;
			}
			break;
		}
		
		case 5:
		{
			int totalPieces = sumPieces(legos);
			int avgPieces = totalPieces / legos.size();
			cout << "Average part count for " << legos.size() << " sets: " << avgPieces << endl;
			break;
		}
		
		case 6:
		{
			double totalPrice = sumPrices(legos);
			Lego lego = mostExpensive(legos);
			Lego lego2 = leastExpensive(legos);
			double avgPrice = totalPrice / legos.size();
			cout << "Average price for " << legos.size() << " sets: $" << avgPrice << endl << endl;
			cout << "Least expensive set:" << endl;
			lego2.print();
			cout << endl << "Most expensive set:" << endl;
			lego.print();
			break;
		}
		
		case 7:
		{
			int totalMiniFigs = sumMiniFigs(legos);
			int avgMiniFigs = totalMiniFigs / legos.size();
			Lego lego = mostMiniFigs(legos);
			cout << "Average number of minifigures: " << avgMiniFigs << endl << endl;
			cout << "Set with the most minifigures:" << endl;
			lego.print();
			break;
		}
		
		case 8:
		{
			double totalPrice = sumPrices(legos);
			int totalPieces = sumPieces(legos);
			int totalMiniFigs = sumMiniFigs(legos);
			
			cout << "If you bought one of everything..." << endl;
			cout << "It would cost: $" << totalPrice << endl;
			cout << "You would have " << totalPieces << " pieces in your collection" << endl;
			cout << "You would have an army of " << totalMiniFigs << " minifigures!" << endl;
			break;
		}			
	}
	return 0;
}

const vector<Lego> legosFromFile(int option)
{
	vector<Lego> legos;
	
	if (option != 4)
	{
		string filename = "lego" + to_string(option) + ".csv"; // options 1-3 correspond to lego1.csv - lego3.csv
		ifstream inputFile(filename);
		if (inputFile.is_open())
		{
			string line;
			getline(inputFile, line); // Skip first line which is a row of column names
			while (getline(inputFile, line))
			{
				Lego l = legoFromLine(line);
				legos.push_back(l);
			}
		}
	}
	else
	{
		string filename;
		for (int i = 1; i < 4; i++) // Loop through integers 1 - 3 to get Legos from all three CSV files
		{
			filename = "lego" + to_string(i) + ".csv";
			ifstream inputFile(filename);
			if (inputFile.is_open())
			{
				string line;
				getline(inputFile, line); // Skip first line which is a row of column names
				while (getline(inputFile, line))
				{
					Lego l = legoFromLine(line);
					legos.push_back(l);
				}
			}
		}
	}

	return legos;
}

const Lego legoFromLine(string line)
{
	istringstream stream(line);
	string token;
	
	getline(stream, token, ',');
	int num = stoi(token);
					
	getline(stream, token, ',');
	string theme = token;
					
	getline(stream, token, ',');
	string name = token;
					
	getline(stream, token, ',');
	int miniFigs = stoi(token);
					
	getline(stream, token, ',');
	int pieces = stoi(token);
					
	getline(stream, token, ',');
	double price = stod(token);
					
	Lego l(num, theme, name, miniFigs, pieces, price);
	return l;
}

const Lego mostExpensive(vector<Lego>& legos)
{
	double maxPrice = legos[0].getPrice();
	unsigned int index = 0;
	
	for (unsigned int i = 0; i < legos.size(); i++)
	{
		double price = legos[i].getPrice();
		if (price > maxPrice)
		{
			maxPrice = price;
			index = i;
		}
	}
	return legos[index];
}

const Lego mostPieces(vector<Lego>& legos)
{
	int maxPieces = legos[0].getPieces();
	unsigned int index = 0;
	
	for (unsigned int i = 0; i < legos.size(); i++)
	{
		int pieces = legos[i].getPieces();
		if (pieces > maxPieces)
		{
			maxPieces = pieces;
			index = i;
		}
	}
	return legos[index];
}

const Lego leastExpensive(vector<Lego>& legos)
{
	double minPrice = legos[0].getPrice();
	unsigned int index = 0;
	
	for (unsigned int i = 0; i < legos.size(); i++)
	{
		double price = legos[i].getPrice();
		if (price < minPrice)
		{
			minPrice = price;
			index = i;
		}
	}
	return legos[index];
}

const Lego mostMiniFigs(vector<Lego>& legos)
{
	int maxMiniFigs = legos[0].getMiniFigs();
	unsigned int index = 0;
	
	for (unsigned int i = 0; i < legos.size(); i++)
	{
		int miniFigs = legos[i].getMiniFigs();
		if (miniFigs > maxMiniFigs)
		{
			maxMiniFigs = miniFigs;
			index = i;
		}
	}
	return legos[index];
}

double sumPrices(vector<Lego>& legos)
{
	double sum = 0;
	
	for (unsigned int i = 0; i < legos.size(); i++)
		sum += legos[i].getPrice();
	
	return sum;
}

int sumPieces(vector<Lego>& legos)
{
	int sum = 0;
	
	for (unsigned int i = 0; i < legos.size(); i++)
		sum += legos[i].getPieces();
	
	return sum;
}

int sumMiniFigs(vector<Lego>& legos)
{
	int sum = 0;
	
	for (unsigned int i = 0; i < legos.size(); i++)
		sum += legos[i].getMiniFigs();
	
	return sum;
}