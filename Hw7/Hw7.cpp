/////////////////////////////
//// File: Hw7.cpp
//// Author: Rick Sullivan
//// COEN 70 Lab 7: Binary Search Tree
/////////////////////////////

#include <iostream>
using namespace std;

#define Object char

class BSTree{
private:
	class Node{
	private:
		Object data;
		Node* left;
		Node* right;

	public:
		Node(const Object& = Object(), Node* = NULL, Node* = NULL);
		Object& getData();
		Node* getLeft();
		Node* getRight();
		void setData(Object&);
		void setLeft(Node*);
		void setRight(Node*);
	};

	Node* root;

	void clear(Node*);
	Node* copy(Node*);
	void insert(const Object&, Node*);
	Node* maxNode(Node*);
	Node* minNode(Node*);
	bool isLeaf(Node*);
	bool contains(const Object&, Node*);
	int size(Node*);
	int height(Node*);
	Node* findCommon(const Object&, const Object&, Node*);
	int BSTree::distance(const Object& _data, Node* _node);
	void inOrder(Node*);
	void preOrder(Node*);
	void postOrder(Node*);

public:
	BSTree();
	BSTree(const BSTree&);
	~BSTree();
	const BSTree& operator=(const BSTree&);

	void insert(const Object&);
	void remove(const Object&);
	bool contains(const Object&);
	int size();
	int height();
	int distance(const Object&, const Object&);
	void inOrder();
	void preOrder();
	void postOrder();
};

///////////////////////////////
//// Node class implementation
///////////////////////////////

BSTree::Node::Node(const Object& _data, Node* _left, Node* _right){
	data = _data;
	left = _left;
	right = _right;
}

Object& BSTree::Node::getData(){
	return data;
}

BSTree::Node* BSTree::Node::getLeft(){
	return left;
}

BSTree::Node* BSTree::Node::getRight(){
	return right;
}

void BSTree::Node::setData(Object & _data){
	data = _data;
}

void BSTree::Node::setLeft(Node* _left){
	left = _left;
}

void BSTree::Node::setRight(Node* _right){
	right = _right;
}

///////////////////////////////
//// BSTree class implementation
///////////////////////////////

BSTree::BSTree(){
	root = NULL;
}

BSTree::BSTree(const BSTree& other){
	root = NULL;
	*this = other;
}

BSTree::~BSTree(){
	clear(root);
}

void BSTree::clear(Node* _node){
	if(_node == NULL)
		return;
	clear(_node->getLeft());
	clear(_node->getRight());
	delete _node;
}

const BSTree& BSTree::operator=(const BSTree& other){
	if(this == &other)
		return *this;
	clear(root);
	root = copy(other.root);
	return *this;
}

void BSTree::inOrder(){
	inOrder(root);
	cout << endl;
}

void BSTree::inOrder(Node* _node){
	if(_node == NULL)
		return;
	inOrder(_node->getLeft());
	cout << _node->getData() << ' ';
	inOrder(_node->getRight());
} 

void BSTree::preOrder(){
	preOrder(root);
	cout << endl;
}

void BSTree::preOrder(Node* _node){
	if(_node == NULL)
		return;
	cout << _node->getData() << ' ';
	preOrder(_node->getLeft());
	preOrder(_node->getRight());
}

void BSTree::postOrder(){
	postOrder(root);
	cout << endl;
}

void BSTree::postOrder(Node* _node){
	if(_node == NULL)
		return;
	postOrder(_node->getLeft());
	postOrder(_node->getRight());
	cout << _node->getData() << ' ';
}

BSTree::Node* BSTree::copy(Node* _node){
	if(_node == NULL)
		return NULL;
	Node* temp = new Node(_node->getData(), copy(_node->getLeft()), copy(_node->getRight()));
	return temp;
}

void BSTree::insert(const Object& _data){
	//Empty tree
	if(root == NULL){
		root = new Node(_data);
		return;
	}
	insert(_data, root);
}

void BSTree::insert(const Object& _data, Node* currentNode){
	if(_data == currentNode->getData()){
		//Do nothing
		return;
	}
	else if(_data < currentNode->getData())
		if(currentNode->getLeft() == NULL){
			currentNode->setLeft(new Node(_data));
			return;
		}
		else{
			insert(_data, currentNode->getLeft());
		}
	else{	//_data > currentNode->getData()
		if(currentNode->getRight() == NULL){
			currentNode->setRight(new Node(_data));
			return;
		}
		else{
			insert(_data, currentNode->getRight());
		}
	}
}

void BSTree::remove(const Object& _data){
	if(root == NULL)
		return;
	if(!contains(_data))
		return;

	//Move to correct node to delete with temp
	//parent keeps parent location
	Node* temp = root;
	Node* parent = temp;
	while(_data != temp->getData()){
		parent = temp;
		if(_data < temp->getData()){
			temp = temp->getLeft();
		}
		else if(_data > temp->getData()){
			temp = temp->getRight();
		}
	}

	//Case 1: Temp is a leaf (no children)
	if(isLeaf(temp)){
		if(parent->getLeft() == temp)
			parent->setLeft(NULL);
		else if(parent->getRight() == temp)
			parent->setRight(NULL);
		if(root == temp)
			root = NULL;
		delete temp;
	}

	//Case 2: Temp has one child
	//Point parent at temp's child
	else if(temp->getLeft() == NULL || temp->getRight() == NULL){
		if(temp->getLeft() != NULL){
			if(root == temp)
				root = temp->getLeft();
			else if(parent->getLeft() == temp)
				parent->setLeft(temp->getLeft());
			else
				parent->setRight(temp->getLeft());
		}
		else{
			if(root == temp)
				root = temp->getRight();
			else if(parent->getLeft() == temp)
				parent->setLeft(temp->getRight());
			else
				parent->setRight(temp->getRight());
		}
		delete temp;
	}

	//Case 3: Temp has two children
	//Replace temp's value with the highest value
	//in its left subtree
	else{
		Node* max = maxNode(temp->getLeft());
		temp->setData(max->getData());
		temp->setLeft(max->getLeft());
		delete max;
	}
}

//Returns a pointer to the maximum node in the BST
BSTree::Node* BSTree::maxNode(Node* _node){
	while(_node->getRight() != NULL){
		_node = _node->getRight();
	}
	return _node;
}

//Returns a pointer to the minimum node in the BST
BSTree::Node* BSTree::minNode(Node* _node){
	while(_node->getLeft() != NULL){
		_node = _node->getLeft();
	}
	return _node;
}

bool BSTree::isLeaf(Node* _node){
	if(_node == NULL)
		return false;
	if(_node->getLeft() == NULL && _node->getRight() == NULL)
		return true;
	return false;
}

bool BSTree::contains(const Object& _data){
	return contains(_data, root);
}

bool BSTree::contains(const Object& _data, Node* _node){
	if(_node == NULL)
		return false;
	if(_data == _node->getData())
		return true;
	return contains(_data, _node->getLeft()) || contains(_data, _node->getRight());
}

int BSTree::size(){
	return size(root);
}

int BSTree::size(Node* _node){
	if(_node == NULL)
		return 0;
	return (size(_node->getLeft()) + size(_node->getRight()) + 1);
}

int BSTree::height(){
	return height(root);
}

int BSTree::height(Node* _node){
	if(_node == NULL)
		return 0;
	const int lDepth = height(_node->getLeft());
	const int rDepth = height(_node->getRight());
	return (lDepth < rDepth) ? (rDepth + 1) : (lDepth + 1);
	//		Conditional			True 			False
}

BSTree::Node* BSTree::findCommon(const Object& _data1, const Object& _data2, Node* _node){
	//Both in left subtree
	if(_data1 < _node->getData() && _data2 < _node->getData())
		return findCommon(_data1, _data2, _node->getLeft());
	//Both in right subtree
	if(_data1 > _node->getData() && _data2 > _node->getData())
		return findCommon(_data1, _data2, _node->getRight());
	//In opposite subtrees, so we are at the common parent
	return _node;
}

int BSTree::distance(const Object& _data, Node* _node){
	if(_data < _node->getData())
		return 1 + distance(_data, _node->getLeft());
	if(_data > _node->getData())
		return 1 + distance(_data, _node->getRight());
	return 0;
}

int BSTree::distance(const Object& _data1, const Object& _data2){
	if(root == NULL)
		return 0;
	if( (!contains(_data1)) || (!contains(_data2)) )
		return 0;
	//Both exist
	Node* common = findCommon(_data1, _data2, root);
	return (distance(_data1, common) + distance(_data2, common));
}


int main(){
	BSTree A;
	A.insert('C');
	A.insert('A');
	A.insert('F');
	A.insert('B');
	A.insert('E');
	A.insert('D');
	A.insert('H');
	A.insert('G');
	cout << A.height() << endl;
	cout << A.size() << endl;
	cout << A.distance('B', 'E') << endl;
	cout << A.distance('G', 'D') << endl;
	A.inOrder();
	A.preOrder();
	A.postOrder();

	BSTree B(A);	//Also tests assignment operator
	B.inOrder();
	B.remove('A');
	B.inOrder();
	B.remove('C');
	B.inOrder();
	B.remove('G');
	B.inOrder();
	B.remove('F');
	B.inOrder();
	cout << B.height() << endl;
	cout << B.size() << endl;
	cout << B.contains('A') << endl;
	cout << B.contains('B') << endl;
	cout << B.distance('B', 'B') << endl;
	cout << B.distance('Z', 'B') << endl;
	return 0;
}

/* OUTPUT:
4
8
4
4
A B C D E F G H
C A B F E D H G
B A D E G H F C
A B C D E F G H
B C D E F G H
B D E F G H
B D E F H
B D E H
3
4
0
1
0
0
*/

