#include <iostream>
#include <string>
#include "Image.h"
using std::cout;
using std::endl;
using std::string;
using std::to_string;

int main()
{
	Image* image;
	Image* answer;
	
	for (int i = 1; i < 11; i++)
	{
		if (i == 8)
			continue;
		
		image = new Image;
		answer = new Image;
		*image = imageFromFile("../output/part" + to_string(i) + ".tga");
		*answer = imageFromFile("../examples/EXAMPLE_part" + to_string(i) + ".tga");
	
		if (*image == *answer)
			cout << "Your answer for task " << i << " is correct!" << endl;
		else
			cout << "Your answer for task " << i << " is not correct!" << endl;
	
		delete image;
		delete answer;
	}
	
	image = new Image;
	answer = new Image;
	*image = imageFromFile("../output/part8_r.tga");
	*answer = imageFromFile("../examples/EXAMPLE_part8_r.tga");
	
	if (*image == *answer)
		cout << "Your answer for task 8_r is correct!" << endl;
	else
		cout << "Your answer for task 8_r is not correct!" << endl;
	
	delete image;
	delete answer;
	
	image = new Image;
	answer = new Image;
	*image = imageFromFile("../output/part8_g.tga");
	*answer = imageFromFile("../examples/EXAMPLE_part8_g.tga");
	
	if (*image == *answer)
		cout << "Your answer for task 8_g is correct!" << endl;
	else
		cout << "Your answer for task 8_g is not correct!" << endl;
	
	delete image;
	delete answer;
	
	image = new Image;
	answer = new Image;
	*image = imageFromFile("../output/part8_b.tga");
	*answer = imageFromFile("../examples/EXAMPLE_part8_b.tga");
	
	if (*image == *answer)
		cout << "Your answer for task 8_b is correct!" << endl;
	else
		cout << "Your answer for task 8_b is not correct!" << endl;
	
	delete image;
	delete answer;
	
	image = new Image;
	answer = new Image;
	*image = imageFromFile("../output/extracredit.tga");
	*answer = imageFromFile("../examples/EXAMPLE_extracredit.tga");
	
	if (*image == *answer)
		cout << "Your answer for the extra credit is correct!" << endl;
	else
		cout << "Your answer for the extra credit is not correct!" << endl;
	
	delete image;
	delete answer;
	
	return 0;
}