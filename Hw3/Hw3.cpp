//============================================================================
// Name        : Hw3.cpp
// Author      : Rick Sullivan using Lab3.cpp by Hien T. Vu
// Description : COEN70 Homework4
//============================================================================


#include <iostream>
#include <iomanip>
#include <assert.h>
using namespace std;

///////////////////////////////
// Class interface
///////////////////////////////

class List {
public:
	// Function: Constructors
	List();

	// Function: Destructor
	~List();

	// Function: Copy constructor
	List(const List& R);

	// Function: Assignment operator
	const List& operator=(const List& R);

	// Function: output operator
	friend ostream& operator<<(ostream& out_str, const List& R);

	// Function: Insert an item to the list
	// Postcondition: insert after the pointer and
	//                move the pointer to the new item
	void insert(const int& item);

	// Function: Remove all items from the list
	// Postcondition: reset all members to the initial state
	void clear();

	// Function: Remove an item from the list
	// Postcondition: remove the item at the pointer and
	// move the pointer to the followed item
	void remove();

	// Function: Replace an item in the list
	// Postcondition: replace the item at the pointer and
	// the pointer remains at the same item
	void replace(const int& item);

	// Function: Return true if the list is empty, false otherwise
	bool isEmpty();

	// Function: Reset pointer to the beginning of the list
	// Postcondition: move the pointer to the first item
	void goToFirst();

	// Function: Move pointer to the end of the list
	// Postcondition: move the pointer to the last item
	void goToLast();

	// Function: Move pointer forward
	// Postcondition: move the pointer to the next item and do not
	// move pass the last item
	void goToNext();

	// Function: Move pointer backward
	// Postcondition: move the pointer to the previous item and do
	// not move pass the first item
	void goToPrevious();

	// Postcondition: return the pointer item
	int getCurrent();

private:
	class node {
	public:
		node(const int& data = 0, node* next = NULL);
		int _data;
		node* _next;
	};
	node* _list;
	int _size;
	node* _current;
	static const int _display_width = 5;
	static const int _display_num = 10;
};

///////////////////////////////
// Class implementation
///////////////////////////////

List::node::node(const int& data, node* next) {
	_data = data;
	_next = next;
}

List::List() {
	_list = NULL;
	_size = 0;
	_current = NULL;
}

List::~List() {
	clear();
}

List::List(const List& R) {
	_list = NULL; // initialize to use the operator=
	*this = R;
}

const List& List::operator=(const List& R) {
	if (this == &R) // self-assignment
		return *this;
	clear();
	node* Rtmp = R._list;
	node* current_save;
	while (Rtmp != NULL) {
		insert(Rtmp->_data); // copying node and move current
		if (Rtmp == R._current) // save current
			current_save = _current;
		Rtmp = Rtmp->_next; // next node in the R list
	}
	_size = R._size; // copy size
	_current = current_save; // correctly set current
	return *this;
}

ostream& operator<<(ostream& out_str, const List& R) {
	List::node* Rtmp = R._list;
	int Rn = 0;
	while (Rtmp != R._current) {
		Rn++;
		Rtmp = Rtmp->_next;
	}
	Rtmp = R._list;
	out_str << R._size << " items:" << endl;
	for (int i = 0; i < R._size; i++) {
		out_str << setw(R._display_width) << Rtmp->_data;
		Rtmp = Rtmp->_next;
		if ((i + 1) % R._display_num == 0 || i == R._size - 1) {
			cout << endl;
			if ((i / R._display_num) == (Rn / R._display_num))
				cout << setw(R._display_width * ((Rn % R._display_num) + 1))
						<< "*" << endl;
		}
	}
	return out_str;
}

void List::insert(const int& item) {
	if (_current == NULL) { // inserting first node
		_list = new node(item, NULL); // allocate first node
		_current = _list; // first node is the tail node
	} else {
		_current->_next = new node(item, _current->_next); // allocate new tail node
		_current = _current->_next; // move current to the new item
	}
	_size++; // increase size
}

void List::clear() {
	node* tmp;
	while (_list != NULL) {
		tmp = _list;
		_list = _list->_next;
		delete tmp;
	}
	_size = 0;
	_current = NULL;
}

// Function: Remove an item from the list
// Postcondition: remove the item at the pointer and
// move the pointer to the followed item
void List::remove(){
	if(_current == NULL)	//Empty list or invalid cursor
		return;
	node* temp = _current;
	if(_list == _current){	//Head of list
		temp = _current->_next;
		_list = temp;
	}
	else{					//In middle/end of list
		temp = _list;
		while(temp->_next != _current){
			temp = temp->_next;	//Move to node before _current
		}
		temp->_next = _current->_next;
	}
	delete _current;	//Delete memory
	_current = temp;	//Move cursor
	_size--;			//Decrement size
}

// Function: Replace an item in the list
// Postcondition: replace the item at the pointer and
// the pointer remains at the same item
void List::replace(const int& item){
	_current->_data = item;
}

// Function: Return true if the list is empty, false otherwise
bool List::isEmpty(){
	if(_size == 0){
		return true;
	}
	return false;	//Else
}

// Function: Reset pointer to the beginning of the list
// Postcondition: move the pointer to the first item
void List::goToFirst(){
	_current = _list;
}

// Function: Move pointer to the end of the list
// Postcondition: move the pointer to the last item
void List::goToLast(){
	while(_current->_next != NULL){
		_current = _current->_next;
	}
}

// Function: Move pointer forward
// Postcondition: move the pointer to the next item and do not
// move pass the last item
void List::goToNext(){
	if(_current->_next != NULL){
		_current = _current->_next;
	}
}

// Function: Move pointer backward
// Postcondition: move the pointer to the previous item and do
// not move pass the first item
void List::goToPrevious(){
	if(_current == _list){	//First item or empty list
		return;				//Do nothing
	}
	node* temp = _list;
	while(temp->_next != _current){
		temp = temp->_next;	//Move temp to item before _current
	}
	_current = temp;
}

// Postcondition: return the pointer item
int List::getCurrent(){
	assert(_current != NULL);
	return _current->_data;
}

///////////////////////////////
// Test program
///////////////////////////////

int main() {
	List A;
	cout << A;
	A.insert(1); A.insert(2); A.insert(3);
	cout << A;
	A.insert(4);
	cout << A;
	List B = A;
	B.insert(5);
	cout << B;
	List C(A); C.insert(6);
	cout << C;
	//New test code:
	A.replace(9);
	cout << A;
	A.goToPrevious();
	cout << A;
	A.goToFirst();
	cout << A;
	A.goToPrevious();	//Does nothing
	cout << A;
	A.remove(); 	//Remove from beginning
	cout << A;
	A.goToNext();
	cout << A;
	A.goToLast();
	cout << A;
	A.goToNext();	//Does nothing
	cout << A;
	A.remove();		//Remove from end
	cout << A;
	cout << A.getCurrent() << endl;
	A.clear();
	if(A.isEmpty())
		cout << A << "A is empty" << endl;
	return 0;
}

/***********************************************
OUTPUT:
0 items:
3 items:
    1    2    3
              *
4 items:
    1    2    3    4
                   *
5 items:
    1    2    3    4    5
                        *
5 items:
    1    2    3    4    6
                        *
4 items:
    1    2    3    9
                   *
4 items:
    1    2    3    9
              *
4 items:
    1    2    3    9
    *
4 items:
    1    2    3    9
    *
3 items:
    2    3    9
    *
3 items:
    2    3    9
         *
3 items:
    2    3    9
              *
3 items:
    2    3    9
              *
2 items:
    2    3
         *
3
0 items:
A is empty
***************************************/


