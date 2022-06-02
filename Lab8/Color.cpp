#include "Color.h"

void Color::SetValue(int value)
{
	_rVal = (value >> 16) & 255;
	_gVal = (value >> 8) & 255;
	_bVal = value & 255;
	
	unsigned char element;
	string temp = "00";
	
	element = _rVal / 16;
	/*
	If data element is greater than 9, convert to A, B, C, D, E, or F by finding the difference between data element and 10, 
	add the difference to character 'A', cast as char, then assign to first or second element of temp.  
	Else, assign the element as is by adding element to '0' to get the character representation of element.
	After temp is assigned, add to string _hexVal.  Do this for all rgb values.
	*/
	temp[0] = element > 9 ? (char)('A' + element - 10) : '0' + element;
	
	element = _rVal % 16;
	temp[1] = element > 9 ? (char)('A' + element - 10) : '0' + element;
	_hexVal += temp;
	
	element = _gVal / 16;
	temp[0] = element > 9 ? (char)('A' + element - 10) : '0' + element;
	
	element = _gVal % 16;
	temp[1] = element > 9 ? (char)('A' + element - 10) : '0' + element;
	_hexVal += temp;
	
	element = _bVal / 16;
	temp[0] = element > 9 ? (char)('A' + element - 10) : '0' + element;
	
	element = _bVal % 16;
	temp[1] = element > 9 ? (char)('A' + element - 10) : '0' + element;
	_hexVal += temp;
}

void Color::SetName(const char* name)
{
	_name = name;
}

unsigned char Color::GetR() const
{
	return _rVal;
}

unsigned char Color::GetG() const
{
	return _gVal;
}

unsigned char Color::GetB() const
{
	return _bVal;
}

string Color::GetHexValue() const
{
	return _hexVal;
}

string Color::GetName() const
{
	return _name;
}