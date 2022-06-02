#include <iostream>
#include "Image.h"
using std::cout;
using std::endl;

int main()
{
	string bottomFile, topFile;
	Image* bottom;
	Image* top;
	Image* result;
	Image* tempResult;
	
	cout << "Running program..." << endl;
	
	// TASK 1
	bottomFile = "input/pattern1.tga";
	topFile = "input/layer1.tga";
	bottom = new Image;
	top = new Image;
	result = new Image;
	
	*bottom = imageFromFile(bottomFile);
	*top = imageFromFile(topFile);
	*result = multiply(*bottom, *top);
	
	result->saveToFile("output/part1.tga");
	
	delete result;
	delete bottom;
	delete top;
	
	// TASK 2
	bottomFile = "input/car.tga";
	topFile = "input/layer2.tga";
	bottom = new Image;
	top = new Image;
	result = new Image;
	
	*bottom = imageFromFile(bottomFile);
	*top = imageFromFile(topFile);
	*result = subtract(*bottom, *top);
	
	result->saveToFile("output/part2.tga");
	
	delete result;
	delete bottom;
	delete top;
	
	// TASK 3
	bottomFile = "input/pattern2.tga";
	topFile = "input/layer1.tga";
	bottom = new Image;
	top = new Image;
	tempResult = new Image;
	result = new Image;
	
	*bottom = imageFromFile(bottomFile);
	*top = imageFromFile(topFile);
	*tempResult = multiply(*bottom, *top);
	
	string topFileScreen = "input/text.tga";
	Image* topScreen = new Image;
	*topScreen = imageFromFile(topFileScreen);
	*result = screen(*tempResult, *topScreen);
	
	result->saveToFile("output/part3.tga");
	
	delete result;
	delete bottom;
	delete top;
	delete tempResult;
	delete topScreen;
	
	// TASK 4
	bottomFile = "input/layer2.tga";
	topFile = "input/circles.tga";
	bottom = new Image;
	top = new Image;
	tempResult = new Image;
	result = new Image;
	
	*bottom = imageFromFile(bottomFile);
	*top = imageFromFile(topFile);
	*tempResult = multiply(*bottom, *top);
	
	string topFileSubtract = "input/pattern2.tga";
	Image* topSubtract = new Image;
	*topSubtract = imageFromFile(topFileSubtract);
	*result = subtract(*tempResult, *topSubtract);
	
	result->saveToFile("output/part4.tga");
	
	delete result;
	delete bottom;
	delete top;
	delete tempResult;
	delete topSubtract;
	
	// TASK 5
	bottomFile = "input/pattern1.tga";
	topFile = "input/layer1.tga";
	bottom = new Image;
	top = new Image;
	result = new Image;
	
	*bottom = imageFromFile(bottomFile);
	*top = imageFromFile(topFile);
	*result = overlay(*bottom, *top);
	
	result->saveToFile("output/part5.tga");
	
	delete result;
	delete bottom;
	delete top;
	
	// TASK 6
	bottomFile = "input/car.tga";
	bottom = new Image;
	
	*bottom = imageFromFile(bottomFile);
	bottom->addAmount(0, 200, 0);
	
	bottom->saveToFile("output/part6.tga");
	
	delete bottom;
	
	// TASK 7
	bottomFile = "input/car.tga";
	bottom = new Image;
	
	*bottom = imageFromFile(bottomFile);
	bottom->scale(4, 1, 0);
	
	bottom->saveToFile("output/part7.tga");
	
	delete bottom;
	
	// TASK 8
	bottomFile = "input/car.tga";
	bottom = new Image;
	Image* rChannel = new Image;
	Image* gChannel = new Image;
	Image* bChannel = new Image;
	
	*bottom = imageFromFile(bottomFile);
	*rChannel = bottom->getChannel(0);
	*gChannel = bottom->getChannel(1);
	*bChannel = bottom->getChannel(2);
	
	Image* part8r = new Image;
	Image* part8g = new Image;
	Image* part8b = new Image;
	
	*part8r = mergeSameChannel(*rChannel, 0);
	*part8g = mergeSameChannel(*gChannel, 1);
	*part8b = mergeSameChannel(*bChannel, 2);
	
	part8r->saveToFile("output/part8_r.tga");
	part8g->saveToFile("output/part8_g.tga");
	part8b->saveToFile("output/part8_b.tga");
	
	
	delete part8r;
	delete part8g;
	delete part8b;
	delete bottom;
	delete rChannel;
	delete gChannel;
	delete bChannel;
	
	// TASK 9
	string redFile = "input/layer_red.tga";
	string greenFile = "input/layer_green.tga";
	string blueFile = "input/layer_blue.tga";
	Image* redImage = new Image;
	Image* greenImage = new Image;
	Image* blueImage = new Image;
	
	*redImage = imageFromFile(redFile);
	*greenImage = imageFromFile(greenFile);
	*blueImage = imageFromFile(blueFile);
	
	result = new Image;
	*result = mergeChannels(*redImage, *greenImage, *blueImage);
	
	result->saveToFile("output/part9.tga");
	
	delete result;
	delete blueImage;
	delete greenImage;
	delete redImage;
	
	// TASK 10
	bottomFile = "input/text2.tga";
	bottom = new Image;
	
	*bottom = imageFromFile(bottomFile);
	bottom->invert();
	
	bottom->saveToFile("output/part10.tga");
	
	delete bottom;
	
	// EXTRA CREDIT
	Image* quad1 = new Image;
	Image* quad2 = new Image;
	Image* quad3 = new Image;
	Image* quad4 = new Image;
	
	*quad1 = imageFromFile("input/car.tga"); // top left
	*quad2 = imageFromFile("input/circles.tga"); // top right
	*quad3 = imageFromFile("input/pattern1.tga"); // bottom right
	*quad4 = imageFromFile("input/text.tga"); // bottom left
	result = new Image;
	Image::Header head = quad1->getHeader();
	
	// Set the header to be the same as quad1's header, but double the height and double the width to accommodate all four images.
	result->setHeader(head._idLength, head._colorMapType, head._dataTypeCode, 0, 0, 0, 0, 0, head._width * 2, head._height * 2, head._bitsPerPixel, head._imageDescriptor);
	Image::Header resultHead = result->getHeader();
	vector<Image::Pixel> pixels1 = quad1->getPixels();
	vector<Image::Pixel> pixels2 = quad2->getPixels();
	vector<Image::Pixel> pixels3 = quad3->getPixels();
	vector<Image::Pixel> pixels4 = quad4->getPixels();
	
	/*
	Idea here: Go through each pixel of the would-be image (i is row number, j is column number, if you treat the image as a matrix).
	If i,j are in quadrant k, where k is 1, 2, 3, 4, then add the next pixel in the vector pixelsk and increment the respective pkCounter
	to keep track of where we are in that vector.  There are four quadrants, so there are four branches in the below if-else chain.
	*/
	unsigned int p1Counter = 0;
	unsigned int p2Counter = 0;
	unsigned int p3Counter = 0;
	unsigned int p4Counter = 0;
	
	for (unsigned int i = 0; i < resultHead._height; i++)
	{
		for (unsigned int j = 0; j < resultHead._width; j++)
		{
			if ((i < resultHead._height / 2) && (j < resultHead._width / 2))
			{
				result->addPixel(pixels4[p4Counter]._rVal, pixels4[p4Counter]._gVal, pixels4[p4Counter]._bVal);
				p4Counter++;
			}
			
			else if ((i < resultHead._height / 2) && (j >= resultHead._width / 2))
			{
				result->addPixel(pixels3[p3Counter]._rVal, pixels3[p3Counter]._gVal, pixels3[p3Counter]._bVal);
				p3Counter++;
			}
			
			else if ((i >= resultHead._height / 2) && (j < resultHead._width / 2))
			{
				result->addPixel(pixels1[p1Counter]._rVal, pixels1[p1Counter]._gVal, pixels1[p1Counter]._bVal);
				p1Counter++;
			}
			
			else
			{
				result->addPixel(pixels2[p2Counter]._rVal, pixels2[p2Counter]._gVal, pixels2[p2Counter]._bVal);
				p2Counter++;
			}
		}
	}
	
	result->saveToFile("output/extracredit.tga");
	
	delete quad1;
	delete quad2;
	delete quad3;
	delete quad4;
	delete result;
	
	return 0;
}