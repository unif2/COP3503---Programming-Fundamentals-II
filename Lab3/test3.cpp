#include <iostream>
#include <chrono>
using std::cout;
using std::endl;

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	cout << "hello" << endl;
	auto end = std::chrono::high_resolution_clock::now();
	float elapsed = std::chrono::duration<float, std::nano>(end - start).count();
	cout << elapsed << endl;
	return 0;
}
