#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "SimpleTimer.h"
#include "Random.h"
using namespace std;

void BubbleSort(vector<int>& numbers);
void SelectionSort(vector<int>& numbers);
void InsertionSort(vector<int>& numbers);
bool BinarySearch(vector<int>& numbers, int val);
bool LinearSearch(vector<int>& numbers, int val)

int main()
{
	vector<int> numbers;
	const int count = 30;
	for (int i = 0; i < count; i++)
	{
		int random = Random::Int(1, 50);
		numbers.push_back(random);
	}
	
	// Make copies of the original list for a fair comparison
	vector<int> numbers2 = numbers;
	vector<int> numbers3 = numbers;
	vector<int> numbers4 = numbers;
	
	SimpleTimer t("Bubble Sort: ");
	BubbleSort(numbers); // 0.027s for 300 numbers, 0.076s for 600, 2.88s for 2200.  Already sorted data: 0.00067s for 2200
	
	SimpleTimer t("Selection Sort: ");
	SelectionSort(numbers2); // 0.0066s for 300 numbers, 0.038s for 600, 0.96s for 2200.  Already sorted data: 1.08s for 2200
	
	SimpleTimer t("Insertion Sort: ");
	InsertionSort(numbers3); // 0.0086s for 300 numbers, 0.032s for 600, 0.82s for 2200.  Already sorted data: 0.0004s for 2200
	
	SimpleTimer t("std::sort: ");
	sort(numbers4.begin(), numbers4.end()); // 0.005s for 2200 numbers.  Already sorted data: 0.003s for 2200.
	
	vector<int> numbers5;
	const int count2 = 100000;
	for (int i = 0; i < count; i++)
		numbers5.push_back(i + 1);
	
	sort(numbers5.begin(), numbers5.end());
	
	float totalTime = 0;
	
	for (int i = 0; i < 10000; i++)
	{
		{
			SimpleTimer t("Linear Search: ");
			LinearSearch(numbers5, 5000);
			totalTime += t.ElapsedTime();
		}
	}
	float avg = totalTime / 10000;
	
	SimpleTimer t("Binary Search: ");
	BinarySearch(numbers5, 5000);
	
	LinearSearch(numbers5, 500000);
	BinarySearch(numbers5, 500000);
	LinearSearch(numbers5, 1);
	BinarySearch(numbers5, 1);
	
	return 0;
}

void BubbleSort(vector<int>& numbers)
{
	bool swapWasMade = true;
	while (swapWasMade)
	{
		bool swapWasMade = false;
		// 1 pass through the list
		for (unsigned int i = 0; i < numbers.size() - 1; i++)
		{
			if (numbers[i] > numbers[i + 1])
			{
				int temp = numbers[i];
				numbers[i] = numbers[i + 1];
				numbers[i + 1] = temp;
				
				swapWasMade = true;
			}
		}
	}
}

void SelectionSort(vector<int>& numbers)
{
	for (unsigned int i = 0; i < numbers.size() - 1; i++)
	{
		unsigned int minIndex = i; // Assume the start is the correct value_comp
		
		for (unsigned int j = i + 1; j < numbers.size(); j++)
		{
			// If we find a smaller number than our current winner (i.e. smallest)
			if (numbers[j] < numbers[minIndex])
			{
				// Update the index to "point to" the new smallest number
				minIndex = j;
			}
		}
		// Have we found a new smallest value?
		if (minIndex != i)
		{
			int temp = numbers[minIndex];
			numbers[minIndex] = numbers[i];
			numbers[i] = temp;
		}
	}
}

void InsertionSort(vector<int>& numbers)
{
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		int j = i;
		
		// As long as the current value is "out of order" with what comes before it...
		// Swap with what comes before it
		while (j > 0 && numbers[j] < numbers[j - 1])
		{
			// Swap the two
			int temp = numbers[j];
			numbers[j] = numbers[j - 1];
			numbers[j - 1] = temp;
			
			// Update the j index variable
			j--;
		}
	}
}

bool BinarySearch(vector<int>& numbers, int val)
{
	int numTries = 0;
	int lowIndex = 0, highIndex = numbers.size() - 1;
	
	while (lowIndex <= highIndex)
	{
		numTries++;
		int midPoint = (highIndex + lowIndex) / 2;
		if (numbers[midPoint] == val)
		{
			cout << "Found " << val << " in " << numTries << " searches!" << endl;
			return true;
		}
		else if (numbers[midPoint] > val)
			highIndex = midPoint - 1;
		else if (numbers[midPoint] < val)
			lowIndex = midPoint + 1;
	}
	
	cout << "After " << numTries << " searches, the value " << val << " was not found in the list." << endl;
	return false;
}

bool LinearSearch(vector<int>& numbers, int val)
{
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		if (numbers[i] == val)
		{
			cout << "Found " << val << " in " << i + 1 << " searches!" << endl;
			return true;
		}
	}
	cout << "After " << numbers.size() << " searches, the value " << val << " was not found in the list." << endl;
	return false;
}