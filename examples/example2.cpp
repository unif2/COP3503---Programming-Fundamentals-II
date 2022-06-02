#include <iostream>
#include <string>
#include "C:\Users\veloc\Desktop\COP3503\examples\Hero.h"
using namespace std;

int main()
{
	Hero hero("Conan", 100);
	hero.Print();
	
	//Print the hero's name;
	cout << hero.GetName();
	hero.TakeDamage(25);
	hero.Print();
	return 0;
}