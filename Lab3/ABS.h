#pragma once
#include <iostream>
using std::cout;
using std::endl;
using std::runtime_error;

template<typename T>
class ABS
{
	private:
		T* _stackData;
		unsigned int _maxCapacity;
		unsigned int _size;
		float _scaleFactor;
		unsigned int _totalResizes;
		
	public:
		ABS();
		ABS(unsigned int capacity, float scaleFactor);
		ABS(const ABS& d);
		ABS& operator=(const ABS& d);
		~ABS();
		void push(T data);
		T pop();
		T peek();
		unsigned int getSize();
		unsigned int getMaxCapacity();
		T* getData();
		unsigned int getTotalResizes();
};

/*===== END OF CLASS DEFINITION, BEGIN FUNCTION DEFINITIONS =====*/

template<typename T>
ABS<T>::ABS()
{
	_maxCapacity = 1;
	_size = 0;
	_stackData = new T[_maxCapacity];
	_scaleFactor = 2.0f;
	_totalResizes = 0;
}

template<typename T>
ABS<T>::ABS(unsigned int capacity, float scaleFactor)
{
	_maxCapacity = capacity;
	_size = 0;
	_scaleFactor = scaleFactor;
	_totalResizes = 0;
	_stackData = new T[_maxCapacity];
}

template<typename T>
ABS<T>::ABS(const ABS& d)
{
	_maxCapacity = d._maxCapacity;
	_size = d._size;
	_scaleFactor = d._scaleFactor;
	_totalResizes = 0;
	
	_stackData = new T[_maxCapacity];
	
	for (unsigned int i = 0; i < _size; i++)
		_stackData[i] = d._stackData[i];
}
	
template<typename T>
ABS<T>& ABS<T>::operator=(const ABS& d)
{
	if (this != &d)
	{
		_maxCapacity = d._maxCapacity;
		_size = d._size;
		_scaleFactor = d._scaleFactor;
		_totalResizes = d._totalResizes;
	
		delete[] _stackData;
	
		_stackData = new T[_maxCapacity];
	
		for (unsigned int i = 0; i < _size; i++)
			_stackData[i] = d._stackData[i];
	}
	return *this;
}

template<typename T>
ABS<T>::~ABS()
{
	delete[] _stackData;
}

template<typename T>
void ABS<T>::push(T data)
{
	if (_size == _maxCapacity)
	{
		_maxCapacity *= _scaleFactor;
		T* tempStack = new T[_maxCapacity];
		
		for (unsigned int i = 0; i < _size; i++)
			tempStack[i] = _stackData[i];
		
		delete[] _stackData;
		
		_stackData = tempStack;
		_totalResizes++;
	}
	
	_stackData[_size] = data;
	_size++;
}

template<typename T>
T ABS<T>::pop()
{
	if (_size == 0)
		throw runtime_error("Error! No items!");
	
	T lastVal = _stackData[_size - 1];
	_size--;
	
	if (_size < _maxCapacity / _scaleFactor)
	{
		_maxCapacity /= _scaleFactor;
		_totalResizes++;
	}
	
	T* tempStack = new T[_maxCapacity];
	
	for (unsigned int i = 0; i < _size; i++)
		tempStack[i] = _stackData[i];
		
	delete[] _stackData;	
	_stackData = tempStack;
	
	return lastVal;
}

template<typename T>
T ABS<T>::peek()
{
	if (_size == 0)
		throw runtime_error("Error! No items!");
	
	return _stackData[_size - 1];
}

template<typename T>
unsigned int ABS<T>::getSize()
{
	return _size;
}

template<typename T>
unsigned int ABS<T>::getMaxCapacity()
{
	return _maxCapacity;
}

template<typename T>
T* ABS<T>::getData()
{
	return _stackData;
}

template<typename T>
unsigned int ABS<T>::getTotalResizes()
{
	return _totalResizes;
}