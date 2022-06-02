#include <iostream>
#include <string>
#include "Hero.h"
using namespace std;

// This function needs a pointer but does not require you to dynamically allocate something.
// Just pass it the address of a Hero object because a pointer holds an address.
// You also don't need to do Hero* ptr = &hero; because all you need to do is pass &hero.  No need to have a middle-man.
void Foo(Hero* somePtr)
{
	somePtr->Print();
}

// Return an int pointer.  Purpose: Allocate an array of integers based on passed in size.
int* AllocateSomeIntMemory(unsigned int howMany)
{
	int* someData = new int[howMany];
	cout << "Memory address of allocation: " << someData << endl;
	return someData; // Can also just do one line: return new int[howMany];
	// When function returns, the pointer someData gets deleted from stack, but the allocated memory int[howMany] lives on in the heap until you
	// delete it.  The memory is not leaked because you could still delete it later.
}

int main()
{
	Hero hero("Conan", 100); // on the stack
	hero.TakeDamage(20);
	Foo(&hero);
	Hero* dynamicHero = new Hero("Bronan", 150); // stack variable dynamicHero pointing to memory on the heap
	dynamicHero->TakeDamage(10);
	Foo(dynamicHero);
	
	
	
	
	// Be sure to delete anything that needs deleting.
	delete dynamicHero;
	
	// We can allocate dynamic memory in a function, as long as we delete that memory later on:
	int* theArray = AllocateSomeIntMemory(50); // Catching the dynamically-allocated int array in this pointer, theArray.  
	// theArray is a pointer to the address of this dynamically-allocated array.
	cout << "Memory address of pointer: " << theArray << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << theArray->at(i) << endl;
	}
	
	delete[] theArray; // No leak, problem solved!
	// If you didn't delete theArray, the program would still run and execute normally and you'd think nothing bad was happening.
	
	return 0;
	
}