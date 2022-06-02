#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;

class Image
{
	public:
		struct Header
		{
			char _idLength;
			char _colorMapType;
			char _dataTypeCode;
			short _colorMapOrigin;
			short _colorMapLength;
			char _colorMapDepth;
			short _xOrigin;
			short _yOrigin;
			short _width;
			short _height;
			char _bitsPerPixel;
			char _imageDescriptor;
			bool operator==(const Header& rhs) const;
		};
	
	public:
		struct Pixel
		{
			unsigned char _rVal = 0;
			unsigned char _gVal = 0;
			unsigned char _bVal = 0;
		};
	
	private:
		Header _header;
		vector<Pixel> _pixels;
		
	public:
		Header getHeader();
		void setHeader(const Header& h);
		void setHeader(char idLength, char colorMapType, char dataTypeCode, short colorMapOrigin, short colorMapLength, char colorMapDepth, short xOrigin, short yOrigin, short width, short height, char bitsPerPixel, char imageDescriptor);
		vector<Pixel>& getPixels();
		void addPixel(unsigned char rVal, unsigned char gVal, unsigned char bVal);
		void addAmountAt(unsigned char rAmount, unsigned char gAmount, unsigned char bAmount, unsigned int index);
		void addAmount(unsigned char rAmount, unsigned char gAmount, unsigned char bAmount);
		void scale(unsigned int rScale, unsigned int gScale, unsigned int bScale);
		Image getChannel(short channel);
		void invert();
		void saveToFile(string filename);
		bool operator==(const Image& rhs) const;
};

/*==== NON-CLASS MEMBER FUNCTIONS ====*/

Image multiply(Image& bottom, Image& top);
Image subtract(Image& bottom, Image& top);
Image screen(Image& bottom, Image& top);
Image overlay(Image& bottom, Image& top);
Image mergeChannels(Image& redChannel, Image& greenChannel, Image& blueChannel);
Image mergeSameChannel(Image& image, short channel);
Image imageFromFile(string filename);