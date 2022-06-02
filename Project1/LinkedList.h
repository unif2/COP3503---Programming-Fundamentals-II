#pragma once
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::out_of_range;

template<typename T>
class LinkedList
{
	public:
		struct Node
		{
			T data;
			Node* next = nullptr;
			Node* prev = nullptr;
		};
	
	private:
		unsigned int _numNodes;
		Node* _head;
		Node* _tail;
		
	public:
		
		/*==== Construction / Destruction ====*/
		LinkedList();
		LinkedList(const LinkedList<T>& list);
		~LinkedList();
		
		/*==== Operators ====*/
		const T& operator[](unsigned int index) const;
		T& operator[](unsigned int index);
		bool operator==(const LinkedList<T>& rhs) const;
		LinkedList<T>& operator=(const LinkedList<T>& rhs);
		
		/*==== Removal ====*/
		bool RemoveHead();
		bool RemoveTail();
		unsigned int Remove(const T& item);
		bool RemoveAt(unsigned int index);
		void Clear();
		
		/*==== Insertion ====*/
		void AddHead(const T& item);
		void AddTail(const T& item);
		void AddNodesHead(const T* item, unsigned int count);
		void AddNodesTail(const T* item, unsigned int count);
		void InsertAfter(Node* node, const T& item);
		void InsertBefore(Node* node, const T& item);
		void InsertAt(const T& item, unsigned int index);
		
		/*==== Accessors ====*/
		unsigned int NodeCount() const;
		void FindAll(vector<Node*>& outData, const T& value) const;
		const Node* Find(const T& item) const;
		Node* Find(const T& item);
		const Node* GetNode(unsigned int index) const;
		Node* GetNode(unsigned int index);
		Node* Head();
		const Node* Head() const;
		Node* Tail();
		const Node* Tail() const;
		
		/*==== Behaviors ====*/
		void PrintForward() const;
		void PrintReverse() const;
		void PrintForwardRecursive(const Node* node) const;
		void PrintReverseRecursive(const Node* node) const;
};

/*==== END OF CLASS DEFINITION, BEGIN FUNCTION DEFINITIONS ====*/

template<typename T>
LinkedList<T>::LinkedList()
{
	_numNodes = 0;
	_head = nullptr;
	_tail = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
	_numNodes = 0;
	
	Node* temp = list._head;
	for (unsigned int i = 0; i < list._numNodes; i++)
	{
		AddTail(temp->data);
		temp = temp->next;
	}
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	this->Clear();
}

template<typename T>
const T& LinkedList<T>::operator[](unsigned int index) const
{
	if (index < 0 || index > _numNodes - 1)
		throw out_of_range("Index is out of range!");
	
	// Index is in the first half of the list, so it's faster to start at the head and go forward.
	if (index <= _numNodes / 2)
	{
		Node* temp = _head;
		for (unsigned int i = 0; i < index; i++)
			temp = temp->next;
		return temp->data;
	}
	// Index is in the second half of the list, so it's faster to start at the tail and go in reverse.
	else
	{
		Node* temp = _tail;
		for (unsigned int i = 0; i < _numNodes - index - 1; i++)
			temp = temp->prev;
		return temp->data;
	}
}

template<typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
	if (index < 0 || index > _numNodes - 1)
		throw out_of_range("Index is out of range!");
	
	if (index <= _numNodes / 2)
	{
		Node* temp = _head;
		for (unsigned int i = 0; i < index; i++)
			temp = temp->next;
		return temp->data;
	}
	else
	{
		Node* temp = _tail;
		for (unsigned int i = 0; i < _numNodes - index - 1; i++)
			temp = temp->prev;
		return temp->data;
	}
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
	if (_numNodes != rhs._numNodes)
	{
		return false;
	}
	else if (_numNodes == 0 && rhs._numNodes == 0)
	{
		return true;
	}
	else
	{
	   // I could loop through the list and write if ((*this)[i] != rhs[i]) {return false;} but the below code would be faster.
	   // Using the operator[] would result in constantly looping through the list each time a call to operator[] is made.
		Node* right = rhs._head;
		Node* temp = this->_head;
		for (unsigned int i = 0; i < _numNodes; i++)
		{
			if (temp->data != right->data)
				return false;
			
			temp = temp->next;
			right = right->next;
		}
	}
	return true;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
	// If lhs does not equal rhs.
	if (this != &rhs)
	{
	   // Deallocate memory, clear the list, call AddTail on each item of the rhs.
		this->Clear();
		Node* temp = rhs._head;
		for (unsigned int i = 0; i < rhs._numNodes; i++)
		{
			this->AddTail(temp->data);
			temp = temp->next;
		}
	}
	return *this;
}

template<typename T>
bool LinkedList<T>::RemoveHead()
{
	if (_numNodes == 0)
	{
		return false;
	}
	else if (_numNodes == 1)
	{
		delete _head;
		_head = nullptr;
		_tail = nullptr;
	}
	// Remove the head and set head to be the second item.
	else
	{
		Node* temp = _head->next;
		delete _head;
		_head = temp;
		_head->prev = nullptr;
	}
	_numNodes--;
	return true;
}

template<typename T>
bool LinkedList<T>::RemoveTail()
{
	if (_numNodes == 0)
	{
		return false;
	}
	else if (_numNodes == 1)
	{
		delete _tail;
		_tail = nullptr;
		_head = nullptr;
	}
	// Remove tail and set tail to be the second-to-last item.
	else
	{
		Node* temp = _tail->prev;
		delete _tail;
		_tail = temp;
		_tail->next = nullptr;
	}
	_numNodes--;
	return true;
}

template<typename T>
unsigned int LinkedList<T>::Remove(const T& item)
{
	unsigned int numRemoved = 0;
	vector<Node*> nodes;
	this->FindAll(nodes, item);
	if (nodes.size() != 0)
	{
		for (auto node: nodes)
		{
			if (_numNodes == 1)
			{
				delete _head;
			}
			else
			{
				Node* nodeBefore = node->prev;
				Node* nodeAfter = node->next;
				delete node;
				nodeBefore->next = nodeAfter;
				nodeAfter->prev = nodeBefore;
			}
			numRemoved++;
			_numNodes--;
		}
	}
	return numRemoved;
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index)
{
	if (index < 0 || index > _numNodes - 1)
		return false;
	
	Node* temp = nullptr;
	
	if (index == 0)
	{
		return this->RemoveHead();
	}
	else if (index == _numNodes - 1)
	{
		return this->RemoveTail();
	}
	else if (index <= _numNodes / 2)
	{
		temp = _head;
		for (unsigned int i = 0; i < index; i++)
			temp = temp->next;
	}
	else
	{
		temp = _tail;
		for (unsigned int i = 0; i < _numNodes - index - 1; i++)
			temp = temp->prev;
	}
	Node* nodeBefore = temp->prev;
	Node* nodeAfter = temp->next;
	delete temp;
	nodeBefore->next = nodeAfter;
	nodeAfter->prev = nodeBefore;
	_numNodes--;
	return true;
}
	
template<typename T>
void LinkedList<T>::Clear()
{
	while (_numNodes > 0)
	{
		this->RemoveHead();
	}
}

template<typename T>
void LinkedList<T>::AddHead(const T& item)
{
	Node* temp = new Node;
	temp->data = item;
	
	if (_numNodes == 0)
	{
		_head = temp;
		_tail = temp;
	}
	else
	{
		_head->prev = temp;
		temp->prev = nullptr;
		temp->next = _head;
		_head = temp;
	}
	_numNodes++;
}

template<typename T>
void LinkedList<T>::AddTail(const T& item)
{
	Node* temp = new Node;
	temp->data = item;
	
	if (_numNodes == 0)
	{
		_head = temp;
		_tail = temp;
	}
	else
	{
		_tail->next = temp;
		temp->next = nullptr;
		temp->prev = _tail;
		_tail = temp;
	}
	_numNodes++;
}

template<typename T>
void LinkedList<T>::AddNodesHead(const T* item, unsigned int count)
{
	for (unsigned int i = 0; i < count; i++)
	{
		this->AddHead(item[count - 1 - i]);
	}
}

template<typename T>
void LinkedList<T>::AddNodesTail(const T* item, unsigned int count)
{
	for (unsigned int i = 0; i < count; i++)
	{
		this->AddTail(item[i]);
	}
}

template<typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& item)
{
	if (node == _tail)
	{
		this->AddTail(item);
	}
	else
	{
		Node* temp = new Node;
		temp->data = item;
		temp->next = node->next;
		temp->next->prev = temp;
		node->next = temp;
		temp->prev = node;
	}
	_numNodes++;
}

template<typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& item)
{
	if (node == _head)
	{
		this->AddHead(item);
	}
	else
	{
		Node* temp = new Node;
		temp->data = item;
		temp->prev = node->prev;
		temp->prev->next = temp;
		node->prev = temp;
		temp->next = node;
	}
	_numNodes++;
}

template<typename T>
void LinkedList<T>::InsertAt(const T& item, unsigned int index)
{
	if (index < 0 || index > _numNodes)
		throw out_of_range("Index is out of range!");
	
	if (index == 0)
	{
		this->AddHead(item);
	}
	else if (index == _numNodes)
	{
		this->AddTail(item);
	}
	else if (index <= _numNodes / 2)
	{
		Node* temp = _head;
		for (unsigned int i = 0; i < index - 1; i++)
			temp = temp->next;
		
		this->InsertAfter(temp, item);
	}
	else
	{
		Node* temp = _tail;
		for (unsigned int i = 0; i < _numNodes - index - 1; i++)
			temp = temp->prev;
		
		this->InsertBefore(temp, item);
	}
}
		
template<typename T>
unsigned int LinkedList<T>::NodeCount() const
{
	return _numNodes;
}

template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const
{
	if (_numNodes == 0)
	{
		cout << "List is empty!" << endl;
		return;
	}
	
	Node* temp = _head;
	
	for (unsigned int i = 0; i < _numNodes; i++)
	{
		if (temp->data == value)
		{
			outData.push_back(temp);
		}
		
		if (temp->next != nullptr)
			temp = temp->next;
	}
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& item) const
{
	if (_numNodes == 0)
	{
		cout << "List is empty!" << endl;
		return nullptr;
	}
	
	Node* temp = _head;
	
	for (unsigned int i = 0; i < _numNodes; i++)
	{
		if (temp->data == item)
			return temp;
		
		temp = temp->next;
	}
	return temp;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& item)
{
	if (_numNodes == 0)
	{
		cout << "List is empty!" << endl;
		return nullptr;
	}
	
	Node* temp = _head;
	
	for (unsigned int i = 0; i < _numNodes; i++)
	{
		if (temp->data == item)
			return temp;
		
		temp = temp->next;
	}
	return temp;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const
{
	if (index < 0 || index > _numNodes - 1)
		throw out_of_range("Index is out of range!");
	
	Node* temp = nullptr;
	
	if (index <= _numNodes / 2)
	{
		temp = _head;
		for (unsigned int i = 0; i < index; i++)
			temp = temp->next;
	}
	else
	{
		temp = _tail;
		for (unsigned int i = 0; i < _numNodes - index - 1; i++)
			temp = temp->prev;
	}
	return temp;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)
{
	if (index < 0 || index > _numNodes - 1)
		throw out_of_range("Index is out of range!");
	
	Node* temp = nullptr;
	
	if (index <= _numNodes / 2)
	{
		temp = _head;
		for (unsigned int i = 0; i < index; i++)
			temp = temp->next;
	}
	else
	{
		temp = _tail;
		for (unsigned int i = 0; i < _numNodes - index - 1; i++)
			temp = temp->prev;
	}
	return temp;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head()
{
	return _head;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const
{
	return _head;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
	return _tail;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const
{
	return _tail;
}

template<typename T>
void LinkedList<T>::PrintForward() const
{
	if (_numNodes == 0)
	{
		cout << "List is empty!" << endl;
		return;
	}
	
	// Start at the head, print the head's data, and move onto the next node up the list.
	Node* temp = _head;
	
	for (unsigned int i = 0; i < _numNodes; i++)
	{
		cout << temp->data << endl;
		temp = temp->next;
	}
}

template<typename T>
void LinkedList<T>::PrintReverse() const
{
	if (_numNodes == 0)
	{
		cout << "List is empty!" << endl;
		return;
	}
	
	// Start at the tail, print the tail's data, and move onto the next node down the list.
	Node* temp = _tail;
	
	for (unsigned int i = 0; i < _numNodes; i++)
	{
		cout << temp->data << endl;
		temp = temp->prev;
	}
}

template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const
{
	// Base case: Current item is the tail, print the tail's data and return.
	if (node->next == nullptr)
	{
		cout << node->data << endl;
		return;
	}

   // Print the current data and do a recursive call on the next node.
	cout << node->data << endl;
	PrintForwardRecursive(node->next);
}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const
{
	// Base case: Current item is the head, print the head's data and return.
	if (node->prev == nullptr)
	{
		cout << node->data << endl;
		return;
	}
	
	// Print the current data and do a recursive call on the previous node.	
	cout << node->data << endl;
	PrintReverseRecursive(node->prev);
}