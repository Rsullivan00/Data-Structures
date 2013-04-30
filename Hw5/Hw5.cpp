//////////////////////////////////////////////////
////File: Hw5.cpp
////Author: Rick Sullivan
////31 January 2013
////Homework 5: Deque ADT
////Deque using doubly linked list
//////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

template <typename Object>
class Deque;

template <typename Object>
ostream & operator<<(ostream&, const Deque<Object> &);

template <typename Object>
class Deque{
	public:
		//Constructors
		Deque();
		Deque(const Deque& other);
		
		//Destructor
		~Deque();
	
		//Operators
		const Deque& operator=(const Deque& other);
		friend ostream& operator<< <>(ostream& out_str, const Deque& rhs);
		
		//Methods
		void push_front(Object _data);
		void push_back(Object _data);
		void pop_front();
		void pop_back();
		Object front();
		Object back();
		int getSize();
		bool isEmpty();
	
	private:
		class node{
			public:
				node(Object _data = 0, node* _next = NULL, node* _prev = NULL);
				Object data;
				node* next;
				node* prev;
		};

		node* head;
		node* tail;
		int size;
		
		//Private methods
		void init();
		void clear();
};

////////////////////////////////////////////////
////	Class Implementation
////////////////////////////////////////////////

//Node subclass constructor
template <typename Object>
Deque<Object>::node::node(Object _data, node* _next, node* _prev){
	data = _data;
	next = _next;
	prev = _prev;
}

//Deque constructor
template <typename Object>
Deque<Object>::Deque(){
	init();
}

//Deque copy constructor
template <typename Object>
Deque<Object>::Deque(const Deque<Object>& other){
	init();
	*this = other;
}

//Destructor
template <typename Object>
Deque<Object>::~Deque(){
	clear();
}

///////////////////////////////////////////////
////	Class Operators
///////////////////////////////////////////////

//Assignment operator for Deque class
//Traverses the 'other' Deque backwards,
//using the push_front method to add to Deque.
template <typename Object>
const Deque<Object>& Deque<Object>::operator=(const Deque<Object>& other){
	if(this == &other){
		return *this;
	}
	clear();
	node* temp = other.tail;
	for(int i = 0; i < other.size; i++){
		push_front(temp->data);
		temp = temp->prev;
	}
	return *this;
}

//Output operator for the Deque class
//Uses a loop to traverse the Deque. 
//Outputs "Deque of length x" and then
//the data of the Deque on the next line.
template <typename Object>
ostream& operator<<(ostream& out_str, const Deque<Object>& rhs){
	typename Deque<Object>::node* temp = rhs.head;
	out_str << "Deque of length " << rhs.size << ":" << endl;
	for(int i = 0; i < rhs.size; i++){
		out_str << temp->data << ' ';
		temp = temp->next;
	}
	return out_str;
}

////////////////////////////////////////////
////	Class Methods
////////////////////////////////////////////

//push_front function for Deque class
//Adds a node with Object data to the beginning of the Deque.
template <typename Object>
void Deque<Object>::push_front(Object _data){
	node* temp = new node(_data, head, NULL);
	
	if(size > 0){
		head->prev = temp;
	}
	head = temp;
	if(size == 0){
		tail = temp;
	}
	size++;
}

//push_back function for Deque class
//Adds a node with Object data to the end of the Deque.
template <typename Object>
void Deque<Object>::push_back(Object _data){
	node* temp = new node(_data, NULL, tail);
	
	if(size > 0){
		tail->next = temp;
	}
	tail = temp;
	if(size == 0){
		head = temp;
	}
	size++;
}

//pop_front function for Deque class
//Removes the node at the beginning of the Deque.
template <typename Object>
void Deque<Object>::pop_front(){
	if(size == 0){
		return;
	}
	node* temp = head;
	head = head->next;
	size--;
	delete temp;
}

//pop_front function for Deque class
//Removes the node at the end of the Deque.
template <typename Object>
void Deque<Object>::pop_back(){
	if(size == 0){
		return;
	}
	node* temp = tail;
	tail = tail->prev;
	size--;
	delete temp;
}

//front function for Deque class
//Returns the Object data of the first node in the Deque.
template <typename Object>
Object Deque<Object>::front(){
	assert(size > 0);
	return head->data;
}

//back function for Deque class
//Returns the Object data of the last node in the Deque.
template <typename Object>
Object Deque<Object>::back(){
	assert(size > 0);
	return tail->data;
}

//size function for Deque class
//Returns the size of the Deque
template <typename Object>
int Deque<Object>::getSize(){
	return size;
}

//Initialization function for Deque class
template <typename Object>
void Deque<Object>::init(){
	head = NULL;
	tail = NULL;
	size = 0;
}

//Clear function removes all nodes and deallocates memory.
//Also resets members of Deque with init() function.
template <typename Object>
void Deque<Object>::clear(){
	node* temp = head;
	for(int i = 0; i < size; i++){
		head = head-> next;
		delete temp;
		temp = head;
	}
	init();
}

//Test function
int main(){
	Deque<int> A;
	cout << A << endl;
	A.push_front(1);
	A.push_front(2);
	A.push_back(3);
	A.push_back(4);
	A.push_front(5);
	cout << A << endl;
	A.pop_front();
	cout << A << endl;
	A.pop_back();
	cout << A << endl;
	
	Deque <int>B(A);
	cout << B << endl;
	B.push_front(12345);
	cout << B << endl;
	cout << B.front() << ' ' << B.back() << endl;

	Deque<string> C;
	cout << C << endl;
	C.push_front("ONE");
	C.push_back("TWO");
	cout << C << endl;

	return 0;
}

/* Output:
Deque of length 0:

Deque of length 5:
5 2 1 3 4
Deque of length 4:
2 1 3 4
Deque of length 3:
2 1 3
Deque of length 3:
2 1 3
Deque of length 4:
12345 2 1 3
12345 3
Deque of length 0:

Deque of length 2:
ONE TWO
*/


