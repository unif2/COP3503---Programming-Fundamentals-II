#pragma once
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::out_of_range;
using std::to_string;
using std::endl;

template<typename T>
class DynamicArray
{
	T* _theData;
	unsigned int _maxCapacity; // how many elements
	unsigned int _actualSize;
	void CheckIndex(unsigned int index);
	
public:
	DynamicArray(int initialCapacity = 1);
	// Copy Constructor
	DynamicArray(const DynamicArray& other);
	
	// Copy Assignment Operator
	DynamicArray& operator=(const DynamicArray& other);
	
	// Add a new element to end of array
	// Resize the array if necessary to accommodate the new element
	void Add(T value);
	void Set(unsigned int index, T value);
	
	unsigned int Size();
	T At(unsigned int index); // Return an element from a specific index
	
	
	~DynamicArray();
	
	// Print the key components of our container
	void Print();
	
	void Clear();
	void EraseLast();
	void EraseIndex(unsigned int indexToRemove);	
	DynamicArray operator+(const DynamicArray& rhs);
	DynamicArray& operator+=(const DynamicArray& rhs);
	bool operator==(const DynamicArray& rhs);
	// operator !=
	T& operator[](int index);	
};

/*==== END CLASS DEFINITION, BEGIN FUNCTION DEFINITIONS ====*/

template<typename T>
void DynamicArray<T>::CheckIndex(unsigned int index)
{
	if (index >= _actualSize)
	{
		// Build the error message
		string errorMsg = "ERROR index out of range! Expected: 0-";
		errorMsg.append(to_string(_actualSize - 1)); // append is the same as +=
		errorMsg += ". Index value: ";
		errorMsg += to_string(index);
		
		// Throw the exception with that message
		throw out_of_range(errorMsg);
	}

template<typename T>
DynamicArray<T>::DynamicArray<T>(unsigned int initialCapacity)
{
	_maxCapacity = initialCapacity;
	
	_theData = new T[_maxCapacity];
	_actualSize = 0; // Start at the beginning
	
}

// Copy assignment operator
template<typename T>
DynamicArray& DynamicArray<T>::operator=(const DynamicArray& other)
{
	// If "this" is pointing to the same address as "other"...
	// no need to copy an object into itself
	if (this != &other)
	{
	// Clear out any old data
	delete[] _theData;
	
	_maxCapacity = other._maxCapacity;
	_actualSize = other._actualSize;
	
	_theData = new T[_maxCapacity];
	for (unsigned int i = 0; i < _actualSize; i++)
		_theData[i] = other._theData[i];
	}
	
	return *this;

// Copy constructor
template<typename T>
DynamicArray::DynamicArray<T>(const DynamicArray& other)
{
	// Not _theData = other._theData; // Shallow Copy
	_maxCapacity = other._maxCapacity;
	_actualSize = other._actualSize;
	_theData = new T[_maxCapacity];
	
	for (unsigned int i = 0; i < _actualSize; i++)
		_theData[i] = other._theData[i];
}

template<typename T>
DynamicArray<T>::~DynamicArray()
{
	
	delete[] _theData;
	
}

template<typename T>
void DynamicArray<T>::Add(T value)
{
	// If the data was cleared out...
	if (_theData == nullptr)
	{
		_theData = new T[_maxCapacity];
	}
	else if (_actualSize == _maxCapacity || _theData == nullptr) // If we're full
	{
		// Resize the container
		cout << "Resized container!" << endl;
		
		// 1. Allocate space for the new container
		// (Include the current size + space for 1 more)
		T* tempPtr = new T[_maxCapacity + 1];
		
		// 2. Copy current data to that new location
		for (unsigned int i = 0; i < _actualSize; i++)
			tempPtr[i] = _theData[i];
			
		// 3. Delete the current (soon to be old) data
		delete[] _theData;
		
		// 4. Redirect our pointer to that new location
		// Temporary pointer will fall out of scope when function returns, so we won't need to
		// set it to null.
		_theData = tempPtr; // _theData is a member variable, so it will last.  Once function exits, tempPtr will fall
		// out of scope, so it will get deleted.
		
		// 5. Update our capacity variable to reflect the new value.
		_maxCapacity++;
	}
	
	// 1. Add the incoming element to the right location
	_theData[_actualSize] = value;
	
	// 2. Increment our size
	_actualSize++;
	
}

template<typename T>
unsigned int DynamicArray<T>::Size()
{
	return _actualSize;
}

template<typename T>
void DynamicArray<T>::Print()
{
	cout << "Capacity: " << _maxCapacity << endl;
	cout << "Size: " << _actualSize << endl;
	
	if (_actualSize == 0)
	{
		cout << "Array is empty!" << endl;
	}
	else
	{
		for (unsigned int i = 0; i < _actualSize; i++)
			cout << _theData[i] << endl;
	}
	
}

template<typename T>
int DynamicArray<T>::At(unsigned int index)
{
	CheckIndex(index);
	return _theData[index];
}

template<typename T>
void DynamicArray<T>::Set(unsigned int index, T value)
{
	_theData[index] = value;
}

template<typename T>
void DynamicArray<T>::Clear()
{
	
	// 1. Delete all our current data
	delete[] _theData;
	// Set our pointer to nullptr, to indicate it explicitly points to nothing at all
	_theData = nullptr; // Not required for freeing the memory but can be necessary to prevent certain errors.
	
	// 2. Set our size to 0
	_actualSize = 0;
}

template<typename T>
void DynamicArray<T>::EraseLast()
{
	// TO DO: Write an edge case for a capacity of 0
	//
	// 1. Allocate space for the smaller array
	T* smallerArray = new T[_maxCapacity - 1];
	
	if (_actualSize == _maxCapacity)
		_actualSize--;
	
	// 2. Copy the data (except the last element) to that new location
	for (int i = 0; i < _actualSize; i++)
		smallerArray[i] = _theData[i];
	
	// 3. Delete the current array
	delete[] _theData;
	
	// 4. Redirect pointer to the new location
	_theData = smallerArray;
	
	// 5. Update our size/capacity to reflect these changes
	_maxCapacity--;
}

template<typename T>
void DynamicArray<T>::EraseIndex(unsigned int indexToRemove)
{
	CheckIndex(indexToRemove);
	// 1. Allocate space for the smaller array
	T* smallerArray = new T[_maxCapacity - 1];
	
	// 2. Copy the data (except the element to be removed) to that new location
	for (unsigned int currentIndex = 0, smallIndex = 0; currentIndex < _actualSize; currentIndex++)
	{
		if (currentIndex != indexToRemove)
		{
			smallerArray[smallIndex] = _theData[currentIndex];
			smallIndex++;
		}
	}
	/*
	Can also do it this way:
	for (unsigned int i = 0; (i < _actualSize) && (i != indexToRemove); i++)
	{
		if (i < indexToRemove)
		{
			smallerArray[i] = _theData[i];
		}
		else
		{
			smallerArray[i - 1] = _theData[i];
		}
	}
	*/
	
	// 3. Delete the current array
	delete[] _theData;
	
	// 4. Redirect pointer to the new location
	_theData = smallerArray;
	
	// 5. Update our size/capacity to reflect these changes
	_maxCapacity--;
	_actualSize--;
}

template<typename T>
DynamicArray<T> DynamicArray<T>::operator+(const DynamicArray& rhs)
{
	// 1. Create an array large enough to hold both (Initial capacity == sum of both sizes)
	DynamicArray<T> newArray(_actualSize + rhs._actualSize);
	
	// 2. Add container 1 to the new array
	for (unsigned int i = 0; i < _actualSize; i++)
		newArray.Add(_theData[i]);
	
	// 3. Add container 2 to the new array
	for (unsigned int i = 0; i < rhs._actualSize; i++)
		newArray.Add(rhs._theData[i]);
	
	// 4. Return the new array
	return newArray;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator+=(const DynamicArray& rhs)
{
	// 1. Go through the other object's array data
	// 1A. Add each element to "this"
	for (unsigned int i = 0; i < rhs._actualSize; i++)
		Add(rhs._theData[i]);
	
	return *this;
}

template<typename T>
bool DynamicArray<T>::operator==(const DynamicArray& rhs)
{
	if (_actualSize != rhs._actualSize) return false;
	// if (_maxCapacity != rhs._maxCapacity) return false; // Should we check this at all?
	
	for (unsigned int i = 0; i < _actualSize; i++)
	{
		if (_theData[i] != rhs._theData[i])
			return false;
	}
	
	return true;
}

template<typename T>
T& DynamicArray<T>::operator[](int index)
{
	CheckIndex(index);
	return _theData[index];
}
	