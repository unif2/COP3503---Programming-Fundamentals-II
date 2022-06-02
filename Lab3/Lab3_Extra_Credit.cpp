#include <iostream>
#include <vector>
#include <chrono>
#include "ABS.h"
#include "ABQ.h"
using std::cout;
using std::endl;
using std::vector;

void stackTask(float scale, int N, unsigned int capacity);
void queueTask(float scale, int N, unsigned int capacity);

int main()
{	
	unsigned int capacity = 2;
	float scales[5] = {1.5f, 2.0f, 3.0f, 10.0f, 100.0f};
	int nVals[5] = {10000, 30000, 50000, 75000, 100000, 300000, 500000, 750000, 1000000};

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			stackTask(scales[i], nVals[j], capacity);
	}
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			queueTask(scales[i], nVals[j], capacity);
	}
	return 0;
}

void stackTask(float scale, int N, unsigned int capacity)
{
	ABS<int> stack(capacity, scale);
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < N; i++)
		stack.push(i);
	auto end = std::chrono::high_resolution_clock::now();
	double elapsed = std::chrono::duration<double, std::nano>(end - start).count();
	cout << "Scale Factor: " << scale << endl;
	cout << "N: " << N << endl;
	cout << "Total Resizes: " << stack.getTotalResizes() << endl;
	cout << "Total Push Time: " << elapsed << endl << endl;
	
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < N; i++)
		stack.pop();
	end = std::chrono::high_resolution_clock::now();
	elapsed = std::chrono::duration<double, std::nano>(end - start).count();
	cout << "Scale Factor: " << scale << endl;
	cout << "N: " << N << endl;
	cout << "Total Resizes: " << stack.getTotalResizes() << endl;
	cout << "Total Pop Time: " << elapsed << endl << endl << endl;
}

void queueTask(float scale, int N, unsigned int capacity)
{
	ABQ<int> queue(capacity, scale);
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < N; i++)
		queue.enqueue(i);
	auto end = std::chrono::high_resolution_clock::now();
	double elapsed = std::chrono::duration<double, std::nano>(end - start).count();
	cout << "Scale Factor: " << scale << endl;
	cout << "N: " << N << endl;
	cout << "Total Resizes: " << queue.getTotalResizes() << endl;
	cout << "Total Enqueue Time: " << elapsed << endl << endl;
	
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < N; i++)
		queue.dequeue();
	end = std::chrono::high_resolution_clock::now();
	elapsed = std::chrono::duration<double, std::nano>(end - start).count();
	cout << "Scale Factor: " << scale << endl;
	cout << "N: " << N << endl;
	cout << "Total Resizes: " << queue.getTotalResizes() << endl;
	cout << "Total Dequeue Time: " << elapsed << endl << endl << endl;
}
