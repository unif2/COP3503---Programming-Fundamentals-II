#include <fstream>
#include <iostream>
#include "Image.h"
using std::ofstream;
using std::ifstream;
using std::ios_base;
using std::cout;
using std::endl;

// Returns true if both headers are the same, otherwise returns false.
bool Image::Header::operator==(const Image::Header& rhs) const
{
	if ((this->_idLength == rhs._idLength) && (this->_colorMapType == rhs._colorMapType) && (this->_dataTypeCode == rhs._dataTypeCode) && (this->_colorMapOrigin == rhs._colorMapOrigin)
		&& (this->_colorMapLength == rhs._colorMapLength) && (this->_colorMapDepth == rhs._colorMapDepth) && (this->_xOrigin ==  rhs._xOrigin) && (this->_yOrigin == rhs._yOrigin)
		&& (this->_width == rhs._width) && (this->_height == rhs._height) && (this->_bitsPerPixel == rhs._bitsPerPixel) && (this->_imageDescriptor == rhs._imageDescriptor))
		return true;
		
	return false;
}

// Returns the image's header.
Image::Header Image::getHeader()
{
	return _header;
}

// Sets the image's header to be the same as the input header.
void Image::setHeader(const Header& h)
{
	this->_header = h;
}

// Sets the image's header to have the values as passed into the function.
void Image::setHeader(char idLength, char colorMapType, char dataTypeCode, short colorMapOrigin, short colorMapLength, char colorMapDepth, short xOrigin, short yOrigin, short width, short height, char bitsPerPixel, char imageDescriptor)
{
	this->_header._idLength = idLength;
	this->_header._colorMapType = colorMapType;
	this->_header._dataTypeCode = dataTypeCode;
	this->_header._colorMapOrigin = colorMapOrigin;
	this->_header._colorMapLength = colorMapLength;
	this->_header._colorMapDepth = colorMapDepth;
	this->_header._xOrigin = xOrigin;
	this->_header._yOrigin = yOrigin;
	this->_header._width = width;
	this->_header._height = height;
	this->_header._bitsPerPixel = bitsPerPixel;
	this->_header._imageDescriptor = imageDescriptor;
}

// Returns a vector of the image's pixels (a vector of Pixel objects, each pixel having an r-value, g-value, and b-value).
vector<Image::Pixel>& Image::getPixels()
{
	return _pixels;
}

// Adds an additional pixel to the vector of Pixel objects having the passed in values for red, green, and blue.
void Image::addPixel(unsigned char rVal, unsigned char gVal, unsigned char bVal)
{
	Pixel p;
	p._rVal = rVal;
	p._gVal = gVal;
	p._bVal = bVal;
	
	_pixels.push_back(p);
}

// Adds a specified amount to the red value, green value, and blue value to the pixel at position index.  Resultant values are clamped at 255.
void Image::addAmountAt(unsigned char rAmount, unsigned char gAmount, unsigned char bAmount, unsigned int index)
{
	int tempR = (int)_pixels[index]._rVal;
	int tempG = (int)_pixels[index]._gVal;
	int tempB = (int)_pixels[index]._bVal;
	
	tempR += rAmount;
	tempG += gAmount;
	tempB += bAmount;
	
	if (tempR > 255)
		tempR = 255;
	
	if (tempG > 255)
		tempG = 255;
	
	if (tempB > 255)
		tempB = 255;
	
	_pixels[index]._rVal = (unsigned char)tempR;
	_pixels[index]._gVal = (unsigned char)tempG;
	_pixels[index]._bVal = (unsigned char)tempB;
}

// Adds a specified amount to the red value, green value, and blue value to all pixels.  Resultant values are clamped at 255.
void Image::addAmount(unsigned char rAmount, unsigned char gAmount, unsigned char bAmount)
{
	for (unsigned int i = 0; i < _pixels.size(); i++)
		this->addAmountAt(rAmount, gAmount, bAmount, i);
}

// Scales the red, green, and blue values of all pixels by the specified factors.  Resultant values are clamped at 255.
void Image::scale(unsigned int rScale, unsigned int gScale, unsigned int bScale)
{
	for (unsigned int i = 0; i < _pixels.size(); i++)
	{
		int tempR = (int)_pixels[i]._rVal;
		int tempG = (int)_pixels[i]._gVal;
		int tempB = (int)_pixels[i]._bVal;
		
		tempR *= rScale;
		tempG *= gScale;
		tempB *= bScale;
		
		if (tempR > 255)
			tempR = 255;
	
		if (tempG > 255)
			tempG = 255;
	
		if (tempB > 255)
			tempB = 255;
		
		_pixels[i]._rVal = (unsigned char)tempR;
		_pixels[i]._gVal = (unsigned char)tempG;
		_pixels[i]._bVal = (unsigned char)tempB;
	}
}

// Returns an image with just the specified channel (all other values are set to 0).  Channels are specified as 0 (red), 1 (green), or 2 (blue).
Image Image::getChannel(short channel)
{
	Image newImage;
	newImage._header = this->_header;
	
	for (unsigned int i = 0; i < this->_pixels.size(); i++)
	{
		newImage.addPixel(0, 0, 0);
		switch (channel)
		{
			case 0:
			{
				newImage.addAmountAt(this->_pixels[i]._rVal, 0, 0, i);
				break;
			}
			
			case 1:
			{
				newImage.addAmountAt(0, this->_pixels[i]._gVal, 0, i);
				break;
			}
			
			case 2:
			{
				newImage.addAmountAt(0, 0, this->_pixels[i]._bVal, i);
				break;
			}
		}
	}
	return newImage;
}

// Returns an image that is the same as the original, only upside-down.
void Image::invert()
{
	for (unsigned int i = 0; i < _pixels.size() / 2; i++)
	{
		Pixel temp = _pixels[i];
		unsigned int targetIndex = _pixels.size() - 1 - i;
		_pixels[i] = _pixels[targetIndex];
		_pixels[targetIndex] = temp;
	}
}

// Saves the image as a .tga file.
void Image::saveToFile(string filename)
{
	ofstream outFile;
	outFile.open(filename, ios_base::binary);
	
	outFile.write(&_header._idLength, 1);
	outFile.write(&_header._colorMapType, 1);
	outFile.write(&_header._dataTypeCode, 1);
	outFile.write((char*)&_header._colorMapOrigin, 2);
	outFile.write((char*)&_header._colorMapLength, 2);
	outFile.write(&_header._colorMapDepth, 1);
	outFile.write((char*)&_header._xOrigin, 2);
	outFile.write((char*)&_header._yOrigin, 2);
	outFile.write((char*)&_header._width, 2);
	outFile.write((char*)&_header._height, 2);
	outFile.write(&_header._bitsPerPixel, 1);
	outFile.write(&_header._imageDescriptor, 1);
	
	for (unsigned int i = 0; i < _pixels.size(); i++)
	{
		outFile.write((char*)&_pixels[i]._bVal, 1);
		outFile.write((char*)&_pixels[i]._gVal, 1);
		outFile.write((char*)&_pixels[i]._rVal, 1);
	}
	outFile.close();
	cout << "Image saved to file!" << endl;
}

// Returns true if both images are exactly the same (same headers, same pixels).  Otherwise, returns false.
bool Image::operator==(const Image& rhs) const
{
	if (!(this->_header == rhs._header))
		return false;
	
	for (unsigned int i = 0; i < this->_pixels.size(); i++)
	{
		if ((this->_pixels[i]._rVal != rhs._pixels[i]._rVal) || (this->_pixels[i]._gVal != rhs._pixels[i]._gVal) || (this->_pixels[i]._bVal != rhs._pixels[i]._bVal))
			return false;
	}
	return true;
}

/*==== NON-CLASS MEMBER FUNCTIONS ====*/

// Returns an image that is the result of applying the Multiply blending mode on two images.
Image multiply(Image& bottom, Image& top)
{
	Image newImage;
	Image::Header bHeader = bottom.getHeader();
	newImage.setHeader(bHeader);
	
	vector<Image::Pixel> bPixels = bottom.getPixels();
	vector<Image::Pixel> tPixels = top.getPixels();
	
	for (unsigned int i = 0; i < bPixels.size(); i++)
	{
		float newR = bPixels[i]._rVal / 255.0;
		newR *= tPixels[i]._rVal;
		newR += 0.5f;
		
		float newG = bPixels[i]._gVal / 255.0;
		newG *= tPixels[i]._gVal;
		newG += 0.5f;
		
		float newB = bPixels[i]._bVal / 255.0;
		newB *= tPixels[i]._bVal;
		newB += 0.5f;
		
		newImage.addPixel((unsigned char)newR, (unsigned char)newG, (unsigned char)newB);
	}
	return newImage;
}

// Returns an image that is the result of applying the Subtract blending mode on two images.
Image subtract(Image& bottom, Image& top)
{
	Image newImage;
	Image::Header bHeader = bottom.getHeader();
	newImage.setHeader(bHeader);
	
	vector<Image::Pixel> bPixels = bottom.getPixels();
	vector<Image::Pixel> tPixels = top.getPixels();
	
	for (unsigned int i = 0; i < bPixels.size(); i++)
	{
		int newR = (int)bPixels[i]._rVal - (int)tPixels[i]._rVal;
		int newG = (int)bPixels[i]._gVal - (int)tPixels[i]._gVal;
		int newB = (int)bPixels[i]._bVal - (int)tPixels[i]._bVal;
		
		if (newR < 0)
			newR = 0;
		
		if (newG < 0)
			newG = 0;
		
		if (newB < 0)
			newB = 0;
		
		newImage.addPixel((unsigned char)newR, (unsigned char)newG, (unsigned char)newB);
	}
	return newImage;
}

// Returns an image that is the result of applying the Screen blending mode on two images.
Image screen(Image& bottom, Image& top)
{
	Image newImage;
	Image::Header bHeader = bottom.getHeader();
	newImage.setHeader(bHeader);
	
	vector<Image::Pixel> bPixels = bottom.getPixels();
	vector<Image::Pixel> tPixels = top.getPixels();
	
	for (unsigned int i = 0; i < bPixels.size(); i++)
	{
		float newBottR = bPixels[i]._rVal / 255.0;
		float newTopR = tPixels[i]._rVal / 255.0;
		float newR = (1 - (1 - newBottR) * (1 - newTopR)) * 255.0;
		newR += 0.5f;
		
		float newBottG = bPixels[i]._gVal / 255.0;
		float newTopG = tPixels[i]._gVal / 255.0;
		float newG = (1 - (1 - newBottG) * (1 - newTopG)) * 255.0;
		newG += 0.5f;
		
		float newBottB = bPixels[i]._bVal / 255.0;
		float newTopB = tPixels[i]._bVal / 255.0;
		float newB = (1 - (1 - newBottB) * (1 - newTopB)) * 255.0;
		newB += 0.5f;
		
		newImage.addPixel((unsigned char)newR, (unsigned char)newG, (unsigned char)newB);
	}
	return newImage;
}

// Returns an image that is the result of applying the Overlay blending mode on two images.
Image overlay(Image& bottom, Image& top)
{
	Image newImage;
	Image::Header bHeader = bottom.getHeader();
	newImage.setHeader(bHeader);
	
	vector<Image::Pixel> bPixels = bottom.getPixels();
	vector<Image::Pixel> tPixels = top.getPixels();
	
	for (unsigned int i = 0; i < bPixels.size(); i++)
	{
		float newBottR = bPixels[i]._rVal / 255.0;
		float newTopR = tPixels[i]._rVal / 255.0;
		float newBottG = bPixels[i]._gVal / 255.0;
		float newTopG = tPixels[i]._gVal / 255.0;
		float newBottB = bPixels[i]._bVal / 255.0;
		float newTopB = tPixels[i]._bVal / 255.0;
		
		float newR, newG, newB;
		if (newBottR <= 0.5f)
		{
			newR = 2 * newBottR * newTopR * 255.0 + 0.5f;
		}
		
		else
		{
			newR = (1 - 2 * (1 - newBottR) * (1 - newTopR)) * 255.0 + 0.5f;
		}
		
		if (newBottG <= 0.5f)
		{
			newG = 2 * newBottG * newTopG * 255.0 + 0.5f;
		}
		
		else
		{
			newG = (1 - 2 * (1 - newBottG) * (1 - newTopG)) * 255.0 + 0.5f;
		}
		
		if (newBottB <= 0.5f)
		{
			newB = 2 * newBottB * newTopB * 255.0 + 0.5f;
		}
		
		else
		{
			newB = (1 - 2 * (1 - newBottB) * (1 - newTopB)) * 255.0 + 0.5f;
		}
		
		newImage.addPixel((unsigned char)newR, (unsigned char)newG, (unsigned char)newB);
	}
	return newImage;
}

// Returns an image that merges the specified red channel pixels, green channel pixels, and blue channel pixels.
Image mergeChannels(Image& redChannel, Image& greenChannel, Image& blueChannel)
{
	Image newImage;
	Image::Header rHeader = redChannel.getHeader();
	newImage.setHeader(rHeader);
	
	vector<Image::Pixel> rPixels = redChannel.getPixels();
	vector<Image::Pixel> gPixels = greenChannel.getPixels();
	vector<Image::Pixel> bPixels = blueChannel.getPixels();

	for (unsigned int i = 0; i < rPixels.size(); i++)
	{
		newImage.addPixel(0, 0, 0);
		newImage.addAmountAt(rPixels[i]._rVal, 0, 0, i);
		newImage.addAmountAt(0, gPixels[i]._gVal, 0, i);
		newImage.addAmountAt(0, 0, bPixels[i]._bVal, i);
	}
	return newImage;
}

// This function takes in a source image and channel, and returns an image such that each channel has the same value taken from the specified channel.
Image mergeSameChannel(Image& image, short channel)
{
	Image newImage;
	Image::Header header = image.getHeader();
	newImage.setHeader(header);
	
	vector<Image::Pixel> imagePixels = image.getPixels();
	
	for (unsigned int i = 0; i < imagePixels.size(); i++)
	{
		newImage.addPixel(0, 0, 0);
		switch (channel)
		{
			case 0: // Red
			{
				newImage.addAmountAt(imagePixels[i]._rVal, imagePixels[i]._rVal, imagePixels[i]._rVal, i);
				break;
			}
			
			case 1: // Green
			{
				newImage.addAmountAt(imagePixels[i]._gVal, imagePixels[i]._gVal, imagePixels[i]._gVal, i);
				break;
			}
			
			case 2: // Blue
			{
				newImage.addAmountAt(imagePixels[i]._bVal, imagePixels[i]._bVal, imagePixels[i]._bVal, i);
				break;
			}
		}
	}
	return newImage;
}

// Opens a .tga file, reads in the header and pixel data, and constructs an Image object from the data.
Image imageFromFile(string filename)
{
	Image newImage;
	ifstream inputFile;
	inputFile.open(filename, ios_base::binary);
	
	char idLength, colorMapType, dataTypeCode, colorMapDepth, bitsPerPixel, imageDescriptor;
	short colorMapOrigin, colorMapLength, xOrigin, yOrigin, width, height; 
	
	inputFile.read(&idLength, 1);
	inputFile.read(&colorMapType, 1);
	inputFile.read(&dataTypeCode, 1);
	inputFile.read((char*)&colorMapOrigin, 2);
	inputFile.read((char*)&colorMapLength, 2);
	inputFile.read(&colorMapDepth, 1);
	inputFile.read((char*)&xOrigin, 2);
	inputFile.read((char*)&yOrigin, 2);
	inputFile.read((char*)&width, 2);
	inputFile.read((char*)&height, 2);
	inputFile.read(&bitsPerPixel, 1);
	inputFile.read(&imageDescriptor, 1);
	
	newImage.setHeader(idLength, colorMapType, dataTypeCode, colorMapOrigin, colorMapLength, colorMapDepth, xOrigin, yOrigin, width, height, bitsPerPixel, imageDescriptor);

	unsigned int numPixels = width * height;
	for (unsigned int i = 0; i < numPixels; i++)
	{
		unsigned char bVal;
		inputFile.read((char*)&bVal, 1);
		unsigned char gVal;
		inputFile.read((char*)&gVal, 1);
		unsigned char rVal;
		inputFile.read((char*)&rVal, 1);
		
		newImage.addPixel(rVal, gVal, bVal);
	}
	inputFile.close();
	return newImage;
}