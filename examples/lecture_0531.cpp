#include <iostream>
#include "DynamicArray.h"
#include "Hero.h"
using namespace std;

int main()
{
	/*int* dynArray = new int[5];
	
	for (int i = 0; i < 5; i++)
		dynArray[i] = i;
	
	// 1. Allocate some space for the new, larger array
	int* temporaryPointer = new int[6];
	
	// 2. Copy our current data into that new array (starting at [0])
	for (int i = 0; i < 5; i++)
		temporaryPointer[i] = dynArray[i];
	
	// 3. Delete the current (soon to be "old" array)
	delete[] dynArray;
	
	// 4. Redirect our pointer to that new location
	dynArray = temporaryPointer;
	
	temporaryPointer = nullptr;
	
	// Add something to the end of the array
	dynArray[5] = 99;
	
	// One final delete before program exits
	delete[] dynArray;
	*/
	
	DynamicArray dynArray(2);
	dynArray.Print();
	
	dynArray.Add(2);
	dynArray.Add(5);
	dynArray.Add(15);
	dynArray.Add(22);
	
	dynArray.Print();
	
	cout << "Value at index 2: " << dynArray.At(2) << endl;
	dynArray.Set(2, -105);
	cout << "Value at index 2: " << dynArray.At(2) << endl;
	
	dynArray.Clear(); // Clear will delete the memory that _theData points to.  But the destructor will try to delete it as well.  The destructor
	// is called when main() exits.  Attempting to delete/free the memory the pointer points to a second time will result in an exception.
	// One thing we can do is, in our Clear() function, after _theData is deleted, we set _theData to nullptr and then we can use 
	// if (_theData == nullptr) in other functions that may give us trouble (eg. Add function).
	dynArray.Add(999);
	dynArray.add(998);
	dynArray.add(997);
	dynArray.add(996);
	dynArray.add(995);
	dynArray.Print();
	
	try
	{
		int value = 0;
		int value = dynArray.At(2000); // It may break and throw an exception or not (undefined behavior) because there is only 1 element.
		// Need to address this by throwing an out_of_range exception.
		cout << value << endl;
	}
	catch (out_of_range& ex)
	{
		cout << ex.what() << endl;
	}
	
	dynArray.Print();
	
	/*
	// Eg. with solution
	int* somePointer = new int[100];
	delete[] somePointer; // Free the memory, all set. Nothing else to do!
	// If I do delete[] somePointer; again, an exception will be thrown.
	somePointer = nullptr; // Solution is to set somePointer to null after freeing the memory.
	
	delete[] somePointer; // Free this memory...again? No exception thrown because somePointer is null.
	// If you try to delete a null pointer, it turns into a null op (null operation).
	*/
	
	DynamicArray d1;
	
	d1.Add(999);
	d1.Add(998);
	d1.Add(997);
	d1.Add(996);
	d1.Add(77777);
	
	d1.Print();
	d1.EraseLast();
	d1.Print();
	d1.Add(42);
	d1.Print();
	d1.EraseIndex(2);
	d1.Print();
	d1.Add(50);
	d1.Add(555);
	d1.Print();
	
	// Same as DynamicArray copy(d1);
	DynamicArray copy = d1; // Using copy constructor
	copy.Print();
	
	
	DynamicArray<Hero> arrayOHeroes;
	Hero conan("Conan"), bob("Bob"), batman("The Caped Crusader");
	arrayOHeroes.Add(conan);
	arrayOHeroes.Add(bob);
	arrayOHeroes.Add(batman);
	arrayOHeroes.Print(); // Will not work because the compiler doesn't know how to substitute T with Hero when calling the Print function.
	for (unsigned int i = 0; i < arrayOHeroes.Size(); i++)
		arrayOHeroes.At(i).Print();
	// Note: Instead of having the At() function, we can define operator[] 
	// To combine two arrays together, we can define operator+=
	// Instead of having an Add() function, we can define operator+
	// This is operator overloading
	
	DynamicArray<int> dynArray, dynArray2;
	dynArray.Add(111);
	dynArray.Add(122);
	dynArray.Add(133);
	
	dynArray2.Add(211);
	dynArray2.Add(222);
	dynArray2.Add(233);
	
	DynamicArray<int> combined = dynArray + dynArray2;
	for (unsigned int i = 0; i < combined.Size(); i++)
		cout << combined[i] << endl;
	
	
	// Add the contents of the two containers and create a new, third container
	// The copy constructor of "combined" is being called on this line
	DynamicArray<int> combined = dynArray + dynArray2;
	
	// Add the contents of array2 to the first array
	dynArray += combined;
	for (unsigned int i = 0; i < dynArray.Size(); i++)
		cout << dynArray[i] << endl;
	
	DynamicArray<int> dynArray3 = dynArray2;
	if (dynArray3 == dynArray2)
		cout << "The two lists are equal!" << endl;
	
	/*
	if (dynArray != dynArray2)
	{
		cout << "The two lists are not equal!" << endl;
	}
	*/
	
	return 0;
	
}