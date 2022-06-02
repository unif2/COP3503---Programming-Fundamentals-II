/*======= INCLUDE STATEMENTS =======*/
//"Official" includes first

#include <iostream>
#include <vector>
#include <string>
//"Programmer-defined" files econd
//#include "file.h"
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

/*======= FUNCTION PROTOTYPES =======*/
int GetUserInput();


int main()
{
	int value = GetUserInput();
	return 0;
}

/*======= FUNCTION DEFINITIONS =======*/
int GetUserInput()
{
	cout << "Enter a number: ";
	int someVariable;
	cin >> someVariable;
	cout << "Your number is: " << someVariable << endl;
	return someVariable;
}