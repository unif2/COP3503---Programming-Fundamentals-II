#include <string>
using std::string;

class Color
{
	string _name;
	string _hexVal = "0x";
	unsigned char _rVal;
	unsigned char _gVal;
	unsigned char _bVal;
	
	public:
		// Given an integer value, convert it to RGB and Hex values
		void SetValue(int value);
		void SetName(const char* name);
		
		// Accessors
		unsigned char GetR() const;
		unsigned char GetG() const;
		unsigned char GetB() const;
		string GetHexValue() const;
		string GetName() const;
};