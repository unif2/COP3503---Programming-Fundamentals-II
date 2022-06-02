#include <iostream>
#include <vector>
#include <string>
#include "LinkedList.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
	/*
	cout << "=====Testing AddHead() functionality====" << endl;
	LinkedList<int> data;
	for (int i = 0; i < 12; i += 2)
		data.AddTail(i);
	cout << "Node count: " << data.NodeCount() << endl;
	cout << "Print list forward:" << endl;
	data.PrintForward();
	cout << "Print list in reverse:" << endl;
	data.PrintReverse();
	*/
	
		cout << "=====Testing AddNodesHead() and AddNodesTail() =====" << endl;

	string values[5];
	values[0] = "*";
	values[1] = "**";
	values[2] = "***";
	values[3] = "****";
	values[4] = "*****";

	LinkedList<string> list;
	list.AddHead("**");
	/*
	list.AddHead("***");
	list.AddHead("****");
	list.AddHead("*****");
	list.AddHead("******");
	list.AddHead("*******");
	list.AddHead("********");
	list.AddHead("*********");
	list.AddHead("********");
	list.AddHead("*******");
	list.AddHead("******");

	list.AddNodesHead(values, 5);
	list.AddNodesTail(values, 5);
	*/
	list.RemoveHead();
	cout << list.NodeCount() << endl;
	cout << list.NodeCount() << endl;

	list.PrintReverse();
	cout << list.NodeCount() << endl;
	
	return 0;
}