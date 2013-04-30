//////////////////////////////////////////////////
////File: Hw4.cpp
////Author: Rick Sullivan
////31 January 2013
////Homework 4: Queue ADT
////Queue using doubly linked list
//////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

#define Object int

class Queue{
	public:
		//Constructors
		Queue();
		Queue(const Queue& other);
		
		//Destructor
		~Queue();
	
		//Operators
		const Queue& operator=(const Queue& other);
		friend ostream& operator<<(ostream& out_str, const Queue& rhs);
		
		//Methods
		void enqueue(Object _data);
		Object dequeue();
		Object peek(int position);
		Object getSize();
	
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
Queue::node::node(Object _data, node* _next, node* _prev){
	data = _data;
	next = _next;
	prev = _prev;
}

//Queue constructor
Queue::Queue(){
	init();
}

//Queue copy constructor
Queue::Queue(const Queue& other){
	init();
	*this = other;
}

//Destructor
Queue::~Queue(){
	clear();
}

///////////////////////////////////////////////
////	Class Operators
///////////////////////////////////////////////

//Assignment operator for Queue class
//Traverses the 'other' queue backwards,
//using the enqueue method to add to queue.
const Queue& Queue::operator=(const Queue& other){
	if(this == &other){
		return *this;
	}
	node* temp = other.tail;
	while(temp!= NULL){
		enqueue(temp->data);
		temp = temp->prev;
	}
	return *this;
}

//Output operator for the Queue class
//Uses a loop to traverse the queue. 
//Outputs "Queue of length x" and then
//the data of the queue on the next line.
ostream& operator<<(ostream& out_str, const Queue& rhs){
	Queue::node* temp = rhs.head;
	out_str << "Queue of length " << rhs.size << ":" << endl;
	while(temp != NULL){
		out_str << temp->data << ' ';
		temp = temp->next;
	}
	return out_str;
}

////////////////////////////////////////////
////	Class Methods
////////////////////////////////////////////

//Enqueue function for Queue class
//Adds a node with Object data to the beginning of the queue.
void Queue::enqueue(Object _data){
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

//Dequeue function for Queue class
//Removes the node at the end of the queue.
//Returns the Object data stored in the removed node.
Object Queue::dequeue(){
	assert(size > 0);
	node* temp = tail;
	tail = temp->prev;
	tail->next = NULL;
	delete temp;
	size--;
}

//Peek function for Queue class
//Returns the Object data value at the specified position.
Object Queue::peek(int position){
	assert(position < size);
	node* temp = head;
	for(int i = 0; i < position; i++){
		temp = temp->next;
	}
	return temp->data;
}

//getSize function for Queue class
//Returns the size of the queue
int Queue::getSize(){
	return size;
}

//Private Methods

//Initialization function for Queue class
void Queue::init(){
	head = NULL;
	tail = NULL;
	size = 0;
}

//Clear function removes all nodes and deallocates memory.
//Also resets members of queue with init() function.
void Queue::clear(){
	node* temp = head;
	while(temp != NULL){
		head = head-> next;
		delete temp;
		temp = head;
	}
	init();
}

//Test function
int main(){
	Queue A;
	cout << A << endl;
	A.enqueue(1);
	A.enqueue(2);
	A.enqueue(3);
	A.enqueue(4);
	A.enqueue(5);
	cout << A << endl;
	A.dequeue();
	cout << A << endl;
	A.dequeue();
	cout << A << endl;
	A.dequeue();
	cout << A << endl;
	Queue B(A);
	cout << B << endl;
	B.enqueue(12345);
	cout << B << endl;
	cout << B.peek(1) << endl;
	return 0;
}

/* Output:
Queue of length 0:

Queue of length 5:
5 4 3 2 1
Queue of length 4:
5 4 3 2
Queue of length 3:
5 4 3
Queue of length 2:
5 4
Queue of length 2:
5 4
Queue of length 3:
12345 5 4
5
*/


