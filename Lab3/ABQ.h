#pragma once
#include <iostream>
using std::cout;
using std::endl;
using std::runtime_error;

template<typename T>
class ABQ
{
	private:
		T* _queueData;
		unsigned int _maxCapacity;
		unsigned int _size;
		float _scaleFactor;
		unsigned int _totalResizes;
		
	public:
		ABQ();
		ABQ(unsigned int capacity, float scaleFactor);
		ABQ(const ABQ& d);
		ABQ& operator=(const ABQ& d);
		~ABQ();
		void enqueue(T data);
		T dequeue();
		T peek();
		unsigned int getSize();
		unsigned int getMaxCapacity();
		T* getData();
		unsigned int getTotalResizes();
};

/*===== END OF CLASS DEFINITION, BEGIN FUNCTION DEFINITIONS =====*/

template<typename T>
ABQ<T>::ABQ()
{
	_maxCapacity = 1;
	_size = 0;
	_queueData = new T[_maxCapacity];
	_scaleFactor = 2.0f;
	_totalResizes = 0;
}

template<typename T>
ABQ<T>::ABQ(unsigned int capacity, float scaleFactor)
{
	_maxCapacity = capacity;
	_size = 0;
	_scaleFactor = scaleFactor;
	_totalResizes = 0;
	_queueData = new T[_maxCapacity];
}

template<typename T>
ABQ<T>::ABQ(const ABQ& d)
{
	_maxCapacity = d._maxCapacity;
	_size = d._size;
	_scaleFactor = d._scaleFactor;
	_totalResizes = 0;
	
	_queueData = new T[_maxCapacity];
	
	for (unsigned int i = 0; i < _size; i++)
		_queueData[i] = d._queueData[i];
}

template<typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ& d)
{
	if (this != &d)
	{
		_maxCapacity = d._maxCapacity;
		_size = d._size;
		_scaleFactor = d._scaleFactor;
		_totalResizes = d._totalResizes;
		
		delete[] _queueData;
		
		_queueData = new T[_maxCapacity];
		
		for (unsigned int i = 0; i < _size; i++)
			_queueData[i] = d._queueData[i];
	}
	return *this;
}

template<typename T>
ABQ<T>::~ABQ()
{
	delete[] _queueData;
}

template<typename T>
void ABQ<T>::enqueue(T data)
{
	if (_size == _maxCapacity)
	{
		_maxCapacity *= _scaleFactor;
		T* tempQueue = new T[_maxCapacity];
		
		for (unsigned int i = 0; i < _size; i++)
			tempQueue[i] = _queueData[i];
		
		delete[] _queueData;
		
		_queueData = tempQueue;
		_totalResizes++;
	}
	
	_queueData[_size] = data;
	_size++;
}

template<typename T>
T ABQ<T>::dequeue()
{
	if (_size == 0)
		throw runtime_error("Error! No items!");
	
	T firstVal = _queueData[0];
	_size--;
	
	if (_size < _maxCapacity / _scaleFactor)
	{
		_maxCapacity /= _scaleFactor;
		_totalResizes++;
	}
	
	T* tempQueue = new T[_maxCapacity];
		
	for (unsigned int i = 0; i < _size; i++)
		tempQueue[i] = _queueData[i + 1];
		
	delete[] _queueData;
	_queueData = tempQueue;

	return firstVal;
}

template<typename T>
T ABQ<T>::peek()
{
	if (_size == 0)
		throw runtime_error("Error! No items!");
	
	return _queueData[0];
}

template<typename T>
unsigned int ABQ<T>::getSize()
{
	return _size;
}

template<typename T>
unsigned int ABQ<T>::getMaxCapacity()
{
	return _maxCapacity;
}

template<typename T>
T* ABQ<T>::getData()
{
	return _queueData;
}

template<typename T>
unsigned int ABQ<T>::getTotalResizes()
{
	return _totalResizes;
}