#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

mt19937 random_mt;

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

class State
{
	public:
		string _name;
		int _perCapIncome;
		int _population;
		int _medHouseIncome;
		int _numHouseholds;
		//State(string name, int perCapIncome, int population, int medHouseIncome, int numHouseholds);
		void displayState();
};

void State::displayState()
{
	cout << _name << endl;
	cout << "Population: " << _population << endl;
	cout << "Per Capita Income: " << _perCapIncome << endl;
	cout << "Median Household Income: " << _medHouseIncome << endl;
	cout << "Number of Households: " << _numHouseholds << endl;
}

void RollDice(int numberOfRolls, int numberOfSides);
const State stateFromLine(string line);
const map<string, State> statesFromFile();

int main()
{
	int numRolls;
	int numSides;
   
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);


		cout << "Number of times to roll the die: ";
		cin >> numRolls;

		cout << "Number of sides on this die: ";
		cin >> numSides;

		// Roll dice
		RollDice(numRolls, numSides);
	}
	else if (option == 2)
	{
	   // Load the states
	   map<string, State> states = statesFromFile();
	   int choice;
	   
	   // Get input for option 1 (show all states) or 2 (do a search for a particular state)
	   cout << "1. Print all states" << endl;
	   cout << "2. Search for a state" << endl;
	   cin >> choice;
	   
	   if (choice == 1)
	   {
		   map<string, State>::iterator iter = states.begin();
		   
		   for (; iter != states.end(); ++iter)
		   {
			   string name = iter->first;
			   State s = iter->second;
			   s.displayState();
		   }
	   }
	   else
	   {
		   string searchString;
		   cin >> searchString;
		   
		   map<string, State>::iterator iter = states.find(searchString);
		   if (iter != states.end()) // Matching state was found
		   {
			   string name = iter->first;
			   State s = iter->second;
			   s.displayState();
		   }
		   else
			   cout << "No match found for " << searchString << endl;
	   }
	}

	return 0;
}

void RollDice(int numberOfRolls, int numberOfSides)
{
	map<int, int> rolls;
	
	for (int side = 1; side <= numberOfSides; side++)
	{
		rolls[side] = 0;
	}
	
	for (int trial = 1; trial <= numberOfRolls; trial++)
	{
		int result = Random(1, numberOfSides);
		rolls[result] += 1;
	}
	
	for (int side = 1; side <= numberOfSides; side++)
	{
		cout << side << ": " << rolls[side] << endl;
	}
}

const State stateFromLine(string line)
{
	istringstream stream(line);
	string token;
	
	getline(stream, token, ',');
	string name = token;
					
	getline(stream, token, ',');
	int perCapitaIncome = stoi(token);
					
	getline(stream, token, ',');
	int population = stoi(token);
					
	getline(stream, token, ',');
	int medHouseIncome = stoi(token);
					
	getline(stream, token, ',');
	int numHouseholds = stoi(token);
					
	State s;
	
	s._name = name;
	s._perCapIncome = perCapitaIncome;
	s._population = population;
	s._medHouseIncome = medHouseIncome;
	s._numHouseholds = numHouseholds;
	
	return s;
}

const map<string, State> statesFromFile()
{
	map<string, State> states;
	ifstream inputFile("states.csv");
	
	if (inputFile.is_open())
	{
		string line;
		getline(inputFile, line); // Skip first line which is a row of column names
		while (getline(inputFile, line))
		{
			State s = stateFromLine(line);
			states.emplace(s._name, s);
		}
	}
	return states;
}