//============================================================================
// Name        : Hw8.cpp
// Author      : Rick Sullivan using Hw7 solution
// Description : AVL Tree
//============================================================================

#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template<class Object>
class BTNode {
private:
	Object n_data;
	BTNode* n_left;
	BTNode* n_right;
public:
	BTNode(const Object& = Object(), BTNode* = NULL, BTNode* = NULL);
	bool is_leaf() const;
	// mutator
	void set_data(const Object&);
	void set_left(BTNode*);
	void set_right(BTNode*);
	// accessor
	Object& data();
	BTNode*& left();
	BTNode*& right();
	const Object& data() const;
	const BTNode* left() const;
	const BTNode* right() const;
};

template<class Object>
BTNode<Object>::BTNode(const Object& init_data, BTNode* init_left,
		BTNode* init_right) {
	n_data = init_data;
	n_left = init_left;
	n_right = init_right;
}

template<class Object>
bool BTNode<Object>::is_leaf() const {
	return (n_left == NULL) && (n_right == NULL);
}

template<class Object>
void BTNode<Object>::set_data(const Object& new_data) {
	n_data = new_data;
}

template<class Object>
void BTNode<Object>::set_left(BTNode* new_left) {
	n_left = new_left;
}

template<class Object>
void BTNode<Object>::set_right(BTNode* new_right) {
	n_right = new_right;
}

template<class Object>
Object& BTNode<Object>::data() {
	return n_data;
}

template<class Object>
BTNode<Object>*& BTNode<Object>::left() {
	return n_left;
}

template<class Object>
BTNode<Object>*& BTNode<Object>::right() {
	return n_right;
}

template<class Object>
const Object& BTNode<Object>::data() const {
	return n_data;
}

template<class Object>
const BTNode<Object>* BTNode<Object>::left() const {
	return n_left;
}

template<class Object>
const BTNode<Object>* BTNode<Object>::right() const {
	return n_right;
}

template<class Object>
class AVLTree {
private:
	BTNode<Object>* root;

	void clear(BTNode<Object>*&);
	BTNode<Object>* copy(const BTNode<Object>*);
	void print(BTNode<Object>*, int);
	int size(const BTNode<Object>*);
	int height(const BTNode<Object>*);
	BTNode<Object>* common(BTNode<Object>*, const Object&, const Object&);
	int distance(BTNode<Object>*, const Object&);
	bool contains(const Object&, BTNode<Object>*);
	void insert(const Object&, BTNode<Object>*&);
	void remove(const Object&, BTNode<Object>*&);
	BTNode<Object>* findMin(BTNode<Object>*);
	BTNode<Object>* findMax(BTNode<Object>*);

	BTNode<Object>* rotateLeft(BTNode<Object>*&);
	BTNode<Object>* rotateRight(BTNode<Object>*&);
	int getBalance(const BTNode<Object>*);

public:
	AVLTree();
	~AVLTree();
	AVLTree(const AVLTree&);
	const AVLTree& operator=(const AVLTree&);
	void print();
	void insert(const Object&);
	void remove(const Object&);
	bool contains(const Object& x);
	int size();
	int height();
	int distance(const Object&, const Object&);
};

template<typename Object>
void AVLTree<Object>::clear(BTNode<Object>*& node_ptr) {
	BTNode<Object>* child;
	if (node_ptr != NULL) {
		child = node_ptr->left();
		clear(child);
		child = node_ptr->right();
		clear(child);
		delete node_ptr;
		node_ptr = NULL;
	}
}

template<typename Object>
BTNode<Object>* AVLTree<Object>::copy(const BTNode<Object>* node_ptr) {
	if (node_ptr == NULL)
		return NULL;
	else
		return new BTNode<Object>(node_ptr->data(), copy(node_ptr->left()),
				copy(node_ptr->right()));
}

template<typename Object>
void AVLTree<Object>::print(BTNode<Object>* node_ptr, int depth) {
	if (node_ptr != NULL) {
		print(node_ptr->right(), depth + 1); // print right subtree
		cout << setw(4 * depth) << ""; // indent 4*depth spaces
		cout << node_ptr->data() // print node's data
				//<< "(" << node_ptr << ")" // DEBUG: print node's address
				<< endl;
		print(node_ptr->left(), depth + 1); // print left subtree
	}
}

template<typename Object>
int AVLTree<Object>::size(const BTNode<Object>* node_ptr) {
	if (node_ptr == NULL)
		return 0;
	else
		return 1 + size(node_ptr->left()) + size(node_ptr->right());
}

template<typename Object>
int AVLTree<Object>::height(const BTNode<Object>* node_ptr) {
	if (node_ptr == NULL)
		return 0;
	else {
		int l = height(node_ptr->left());
		int r = height(node_ptr->right());
		return (l > r) ? l + 1 : r + 1;
	}
}

//getBalance returns left height - right height
template<typename Object>
int AVLTree<Object>::getBalance(const BTNode<Object>* node_ptr){
	if(node_ptr == NULL)
		return 0;
	return height(node_ptr->left()) - height(node_ptr->right());
}

template<typename Object>
BTNode<Object>* AVLTree<Object>::rotateLeft(BTNode<Object>*& node_ptr){ 
	BTNode<Object>* old_node = node_ptr;
	node_ptr = node_ptr->right();
	old_node->set_right(node_ptr->left());
	node_ptr->set_left(old_node);
	if(root == old_node)
		root = node_ptr;
}

template<typename Object>
BTNode<Object>* AVLTree<Object>::rotateRight(BTNode<Object>*& node_ptr){
	BTNode<Object>* old_node = node_ptr;
	node_ptr = node_ptr->left();
	old_node->set_left(node_ptr->right());
	node_ptr->set_right(old_node);
	if(root == old_node)
		root = node_ptr;
}

template<typename Object>
BTNode<Object>* AVLTree<Object>::common(BTNode<Object>* node_ptr,
		const Object& x, const Object& y) {
	if (node_ptr == NULL || !contains(x) || !contains(y))
		return NULL;
	while (true) {
		if (node_ptr->data() > x && node_ptr->data() > y)
			node_ptr = node_ptr->left();
		else if (node_ptr->data() < x && node_ptr->data() < y)
			node_ptr = node_ptr->right();
		else
			break;
	}
	return node_ptr;
}

template<typename Object>
int AVLTree<Object>::distance(BTNode<Object>* node_ptr, const Object& x) {
	if (node_ptr == NULL)
		return 0;
	if (node_ptr->data() < x)
		return distance(node_ptr->right(), x) + 1;
	else if (node_ptr->data() > x)
		return distance(node_ptr->left(), x) + 1;
	else
		return 0;
}

template<typename Object>
bool AVLTree<Object>::contains(const Object& x, BTNode<Object>* node_ptr) {
	if (node_ptr == NULL)
		return false;
	else if (x < node_ptr->data())
		return contains(x, node_ptr->left());
	else if (x > node_ptr->data())
		return contains(x, node_ptr->right());
	else
		return true;
}

template<typename Object>
void AVLTree<Object>::insert(const Object& x, BTNode<Object>*& node_ptr) {
	if (node_ptr == NULL)
		node_ptr = new BTNode<Object>(x);
	else if (x < node_ptr->data()){
		insert(x, node_ptr->left());
		if(getBalance(node_ptr) > 1){ //if left heavy
			//do stuff-- right rotation?
			if(getBalance(node_ptr->left()) < 0)
				rotateLeft(node_ptr->left());
			rotateRight(node_ptr);
		}
	} else if (x > node_ptr->data()){
		insert(x, node_ptr->right());
		if(getBalance(node_ptr) < -1){ //if right heavy
			//do stuff-- left rotation?
			if(getBalance(node_ptr->right()) > 0)
				rotateRight(node_ptr->right());
			rotateLeft(node_ptr);
		}
	}
	return;
}

template<typename Object>
void AVLTree<Object>::remove(const Object& x, BTNode<Object>*& node_ptr) {
	if (node_ptr == NULL)
		return;
	if (x < node_ptr->data()){
		remove(x, node_ptr->left());
		//check balance here?
		if(getBalance(node_ptr) < -1){ //if right heavy
			//do stuff-- left rotation?
			if(getBalance(node_ptr->right()) > 0)
				rotateRight(node_ptr->right());
			rotateLeft(node_ptr);
		}
	}
	else if (x > node_ptr->data()){
		remove(x, node_ptr->right());
		//check balance here?
		if(getBalance(node_ptr) > 1){ //if left heavy
			//do stuff-- right rotation?
			if(getBalance(node_ptr->left()) < 0)
				rotateLeft(node_ptr->left());
			rotateRight(node_ptr);
		}
	}
	else if (node_ptr->left() != NULL && node_ptr->right() != NULL) {
		node_ptr->data() = findMin(node_ptr->right())->data();
		remove(node_ptr->data(), node_ptr->right());
	} else {
		BTNode<Object>* old_ptr = node_ptr;
		node_ptr =
				(node_ptr->left() != NULL) ?
						node_ptr->left() : node_ptr->right();
		delete old_ptr;
		if(getBalance(node_ptr) < -1){ //if right heavy
			//do stuff-- left rotation?
			if(getBalance(node_ptr->right()) > 0)
				rotateRight(node_ptr->right());
			rotateLeft(node_ptr);
		}
		if(getBalance(node_ptr) > 1){ //if left heavy
			//do stuff-- right rotation?
			if(getBalance(node_ptr->left()) < 0)
				rotateLeft(node_ptr->left());
			rotateRight(node_ptr);
		}
	}
	return;
}

template<typename Object>
BTNode<Object>* AVLTree<Object>::findMin(BTNode<Object>* node_ptr) {
	if (node_ptr == NULL)
		return NULL;
	if (node_ptr->left() == NULL)
		return node_ptr;
	return findMin(node_ptr->left());
}

template<typename Object>
BTNode<Object>* AVLTree<Object>::findMax(BTNode<Object>* node_ptr) {
	if (node_ptr != NULL)
		while (node_ptr->right() != NULL)
			node_ptr = node_ptr->right();
	return node_ptr;
}

template<typename Object>
AVLTree<Object>::AVLTree() {
	root = NULL;
}

template<typename Object>
AVLTree<Object>::~AVLTree() {
	clear(root);
}

template<typename Object>
AVLTree<Object>::AVLTree(const AVLTree& rhs) {
	root = NULL;
	*this = rhs;
}

template<typename Object>
const AVLTree<Object>& AVLTree<Object>::operator=(const AVLTree& rhs) {
	if (this == &rhs)
		return *this; // check for self-assignment
	clear(root); // clear current tree
	root = copy(rhs.root); // copy rhs's tree
	return *this;
}

template<typename Object>
void AVLTree<Object>::print() {
	print(root, 1);
}

template<typename Object>
void AVLTree<Object>::insert(const Object& x) {
	insert(x, root);
}

template<typename Object>
void AVLTree<Object>::remove(const Object& x) {
	remove(x, root);
}

template<typename Object>
bool AVLTree<Object>::contains(const Object& x) {
	return contains(x, root);
}

template<typename Object>
int AVLTree<Object>::size() {
	return size(root);
}

template<typename Object>
int AVLTree<Object>::height() {
	return height(root);
}

template<typename Object>
int AVLTree<Object>::distance(const Object& x, const Object& y) {
	BTNode<Object>* node_ptr = common(root, x, y);
	if (node_ptr != NULL)
		return distance(node_ptr, x) + distance(node_ptr, y);
	return 0;
}

int main() {
	//Copy constructor, operator=, accessors, mutators are unchanged
	//Will only test insert/remove (the only changed methods)
	srand(time(NULL));
	AVLTree<int> A;
	int N;
	int var = 100;

	cout << "Enter the number of nodes: ";
	cin >> N;
	cout << "Creating binary search tree..." << endl;
	for (int i = 1; i <= N; i++)
		A.insert((rand() % var) - 5);
	cout << "A size() = " << A.size() << " & height() = " << A.height() << endl;
	A.print();
	
	cout << "Adding more to A ..." << endl;
	for (int i = N; i >= 1; i--)
		A.insert((rand() % var) - 5);
	cout << "A size() = " << A.size() << " & height() = " << A.height() << endl;
	A.print();

	if (A.contains(0))
		cout << "Found 0." << endl;
	else
		cout << "Did not find 0." << endl;

	for(int i = 0; i < N/2; i++){
		int num = (rand() % var) - 5;
		A.remove(num);
		cout << "Removing " << num << ":" << endl << endl; 
		A.print();
	}

	cout << endl << endl;
	cout << "Size = " << A.size() << " & height = " << A.height() << endl;
	cout << "Path length (-4,2) = " << A.distance(-4, 2) << endl;
	cout << "Path length (2,-4) = " << A.distance(2, -4) << endl;
	cout << "Path length (2,2) = " << A.distance(2, 2) << endl;
	cout << "Path length (-4,-4) = " << A.distance(-4, -4) << endl;
	cout << "Path length (0,2) = " << A.distance(0, 2) << endl;
	cout << "Path length (-4,0) = " << A.distance(-4, 0) << endl;

	return 0;
}

/* Test function output:
Enter the number of nodes: 20
Creating binary search tree...
A size() = 14 & height() = 5
                14
            12
        11
                9
            8
                    7
                6
    5
                2
            0
                -2
        -3
                -4
            -5
Adding more to A ...
A size() = 19 & height() = 5
                14
            13
                12
        11
                9
            8
                    7
                6
    5
                    4
                3
            2
                1
        0
                    -1
                -2
            -3
                    -4
                -5
Found 0.
Removing 13:

            14
                12
        11
                9
            8
                    7
                6
    5
                    4
                3
            2
                1
        0
                    -1
                -2
            -3
                    -4
                -5
Removing -1:

            14
                12
        11
                9
            8
                    7
                6
    5
                    4
                3
            2
                1
        0
                -2
            -3
                    -4
                -5
Removing 7:

            14
                12
        11
                9
            8
                6
    5
                    4
                3
            2
                1
        0
                -2
            -3
                    -4
                -5
Removing 8:

            14
                12
        11
            9
                6
    5
                    4
                3
            2
                1
        0
                -2
            -3
                    -4
                -5
Removing -4:

            14
                12
        11
            9
                6
    5
                    4
                3
            2
                1
        0
                -2
            -3
                -5
Removing 9:

            14
                12
        11
            6
    5
                    4
                3
            2
                1
        0
                -2
            -3
                -5
Removing 12:

                14
            11
                6
        5
                4
            3
    2
            1
        0
                -2
            -3
                -5
Removing 4:

                14
            11
                6
        5
            3
    2
            1
        0
                -2
            -3
                -5
Removing 5:

                14
            11
        6
            3
    2
            1
        0
                -2
            -3
                -5
Removing 3:

            14
        11
            6
    2
            1
        0
                -2
            -3
                -5


Size = 9 & height = 4
Path length (-4,2) = 0
Path length (2,-4) = 0
Path length (2,2) = 0
Path length (-4,-4) = 0
Path length (0,2) = 1
Path length (-4,0) = 0
*/
