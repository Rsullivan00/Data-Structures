/////////////////////////////////////////
//// File: Hw9.cpp
//// Author: Rick Sullivan
//// COEN 70 Homework 9: Graph ADT
/////////////////////////////////////////

#include <string>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

template<typename vertex>
class NodeB;

///////////////////////////////////////
//// Class: NodeA type for Graph ADT
///////////////////////////////////////

template<typename vertex>
class NodeA{
private:
	vertex data;
	NodeA* nextVertex;
	NodeB<vertex>* list;
public:
	NodeA(const vertex&, NodeA* = NULL, NodeB<vertex>* = NULL);

	vertex& getData();
	NodeA*& getNextVertex();
	NodeB<vertex>*& getList();

	void setData(vertex&);
	void setNextVertex(NodeA*);
	void setList(NodeB<vertex>*);
};

template<typename vertex>
NodeA<vertex>::NodeA(const vertex& _data, NodeA<vertex>* _nextVertex, NodeB<vertex>* _list){
	data = _data;
	nextVertex = _nextVertex;
	list = _list;
}

template<typename vertex>
vertex& NodeA<vertex>::getData(){
	return data;
}

template<typename vertex>
NodeA<vertex>*& NodeA<vertex>::getNextVertex(){
	return nextVertex;
}

template<typename vertex>
NodeB<vertex>*& NodeA<vertex>::getList(){
	return list;
}

template<typename vertex>
void NodeA<vertex>::setData(vertex& _data){
	data = _data;
}

template<typename vertex>
void NodeA<vertex>::setNextVertex(NodeA* _nextVertex){
	nextVertex = _nextVertex;
}

template<typename vertex>
void NodeA<vertex>::setList(NodeB<vertex>* _list){
	list = _list;
}

///////////////////////////////////////
//// Class: NodeB type for Graph ADT
///////////////////////////////////////

template<typename vertex>
class NodeB{
private:
	NodeA<vertex>* vert;
	NodeB* next;
	int weight;
public:
	NodeB(NodeA<vertex>*, NodeB* = NULL, int = 1);

	NodeA<vertex>*& getVert();
	NodeB*& getNext();
	int getWeight();

	void setVert(const NodeA<vertex>*);
	void setNext(NodeB*);
	void setWeight(const int);
};

template<typename vertex>
NodeB<vertex>::NodeB(NodeA<vertex>* _vert, NodeB<vertex>* _next, int _weight){
	vert = _vert;
	next = _next;
	weight = _weight;
}

template<typename vertex>
NodeA<vertex>*& NodeB<vertex>::getVert(){
	return vert;
}

template<typename vertex>
NodeB<vertex>*& NodeB<vertex>::getNext(){
	return next;
}

template<typename vertex>
int NodeB<vertex>::getWeight(){
	return weight;
}

template<typename vertex>
void NodeB<vertex>::setVert(const NodeA<vertex>* _vert){
	vert = _vert;
}

template<typename vertex>
void NodeB<vertex>::setNext(NodeB<vertex>* _next){
	next = _next;
}

template<typename vertex>
void NodeB<vertex>::setWeight(const int _weight){
	weight = _weight;
}

///////////////////////////////////////
//// Class: Graph ADT
///////////////////////////////////////

template<typename vertex>
class Graph{
private:
	NodeA<vertex>* vertices;
	void clear();
	void clear(NodeA<vertex>*& node);
	void clear(NodeB<vertex>*& node);

public:
	Graph();
	Graph(const Graph&);
	~Graph();
	const Graph& operator=(const Graph&);

	bool isFull();
	bool isEmpty();
	void addVertex(const vertex&);
	void addEdge(const vertex&, const vertex&, int = 1);
	void print();
	void getNeighbors(const vertex&, queue<vertex>&);
};

template<typename vertex>
Graph<vertex>::Graph(){
	vertices = NULL;
}

template<typename vertex>
Graph<vertex>::Graph(const Graph& other){
	vertices = NULL;
	*this = other;
}

template<typename vertex>
Graph<vertex>::~Graph(){
	clear();
}

template<typename vertex>
const Graph<vertex>& Graph<vertex>::operator=(const Graph& other){
	if(this == &other)
		return *this;
	clear();
	vertices = NULL;
	//Now copy
	if(other.vertices == NULL)
		return *this;
	NodeA<vertex>* temp = other.vertices;
	//Add all vertices
	while(temp != NULL){
		addVertex(temp->getData());
		temp = temp->getNextVertex();
	}
	//Add all edges
	NodeB<vertex>* edge;
	temp = other.vertices;
	while(temp != NULL){
		edge = temp->getList();
		while(edge != NULL){
			addEdge(temp->getData(), edge->getVert()->getData(), edge->getWeight());
			edge = edge->getNext();
		}
		temp = temp->getNextVertex();
	}
	return *this;
}

template<typename vertex>
void Graph<vertex>::clear(){
	clear(vertices);
}

template<typename vertex>
void Graph<vertex>::clear(NodeA<vertex>*& node){
	if(node == NULL)
		return;
	clear(node->getList());
	clear(node->getNextVertex());
	delete node;
}

template<typename vertex>
void Graph<vertex>::clear(NodeB<vertex>*& node){
	if(node == NULL)
		return;
	clear(node->getNext());
	delete node;
}

//Always returns false because the linked lists
//are almost never going to fill all memory.
//Could always add a maxVertices variable, if necessary.  
template<typename vertex>
bool Graph<vertex>::isFull(){
	return false;
}

template<typename vertex>
bool Graph<vertex>::isEmpty(){
	if(vertices == NULL)
		return true;
	return false;
}

template<typename vertex>
void Graph<vertex>::addVertex(const vertex& v){
	NodeA<vertex>* temp = vertices;
	NodeA<vertex>* tail = vertices;
	while(temp != NULL){
		tail = temp;
		temp = temp->getNextVertex();
	}
	temp = new NodeA<vertex>(v);
	if(vertices == NULL)
		vertices = temp;
	if(tail != NULL)
		tail->setNextVertex(temp);
}

template<typename vertex>
void Graph<vertex>::addEdge(const vertex& f, const vertex& t, int weight){
	NodeA<vertex>* tempF = vertices;
	NodeA<vertex>* tempT = vertices;
	bool foundT = false;
	bool foundF = false;
	//Move to find each NodeA corresponding to each vertex
	while(tempF != NULL && tempT != NULL && !(foundF && foundT)){
		if(tempF->getData() != f)
			tempF = tempF->getNextVertex();
		else
			foundF = true;
		if(tempT->getData() != t)
			tempT = tempT->getNextVertex();
		else
			foundT = true;
	}
	//Check that both exist
	if(tempF == NULL || tempT == NULL)
		return;
	//Move to NULL space at end of from neighbor list
	NodeB<vertex>* edge = tempF->getList();
	NodeB<vertex>* tail = NULL;
	while(edge != NULL){
		//Check if edge already exists
		if(edge->getVert() == tempT){
			edge->setWeight(weight);	
			return;
		}
		tail = edge;
		edge = edge->getNext();		
	}
	//Add NodeB to end of list with weight and other vertex
	edge = new NodeB<vertex>(tempT, NULL, weight);
	//If empty list
	if(tail == NULL)
		tempF->setList(edge);
	else
		tail->setNext(edge);
}

//Prints the graph by printing each vertex
//	followed by its neighbors on newlines
//	each followed by its weight.
template<typename vertex>
void Graph<vertex>::print(){
	NodeA<vertex>* tempV = vertices;
	if(vertices == NULL){
		cout << "Empty Graph" << endl;
	}
	NodeB<vertex>* edge;
	while(tempV != NULL){
		edge = tempV->getList();
		cout << "Vertex: " << tempV->getData() << endl; 
		while(edge != NULL){
			cout << "   V:" << edge->getVert()->getData() 
			<< " Weight:" << edge->getWeight() << endl;
			edge = edge->getNext();
		}
		tempV = tempV->getNextVertex();
	}
}

template<typename vertex>
void Graph<vertex>::getNeighbors(const vertex& v, queue<vertex>& q){
	NodeA<vertex>* tempV = vertices;
	while(tempV != NULL && tempV->getData() != v){
		tempV = tempV->getNextVertex();
	}
	if(tempV == NULL){
		cout << "Vertex " << v << " cannot be found." << endl;
		return;
	}
	//tempV is pointing to the correct vertex
	NodeB<vertex>* edge = tempV->getList();
	//Add neighbors to queue
	while(edge != NULL){
		q.push(edge->getVert()->getData());
		edge = edge->getNext();
	}
}

int main(){
	Graph<int> A;
	cout << A.isEmpty() << endl;
	cout << A.isFull() << endl;
	A.addVertex(1);
	A.addVertex(2);
	A.addVertex(3);
	A.addVertex(4);
	A.addVertex(5);	
	A.print();
	cout << endl;
	A.addEdge(1,2,4);
	A.addEdge(3,2,5);
	A.addEdge(4,2,6);
	A.addEdge(3,4,7);

	A.print();
	cout << endl;

	Graph<int> C(A);
	C.print();
	cout << endl;

	A.addEdge(5,1);
	A.addEdge(3,5,7);
	A.addEdge(1,4,7);
	A.print();
	cout << endl;
	queue<int> q;
	A.getNeighbors(3, q);
	while(!q.empty()){
		cout << q.front() << ' ';
		q.pop();
	}
	cout << endl << endl;

	C = A;
	C.print();
	cout << endl;

	Graph<string> B;
	cout << B.isEmpty() << endl;
	cout << B.isFull() << endl;
	B.addVertex("Portland");
	B.addVertex("Seattle");
	B.addVertex("San Francisco");
	B.addVertex("Los Angeles");
	B.addVertex("Sacremento");	
	B.print();
	cout << endl;
	B.addEdge("Portland","Seattle", 400);
	B.addEdge("Seattle","San Francisco", 800);
	B.addEdge("San Francisco","Los Angeles", 600);
	B.addEdge("Los Angeles","Seattle", 700);
	B.addEdge("Los Angeles","San Francisco", 800);
	B.addEdge("Los Angeles","Portland", 750);
	B.addEdge("Portland","San Francisco", 789);
	B.print();
	cout << endl;
	queue<string> q2;
	B.getNeighbors("Los Angeles", q2);
	while(!q2.empty()){
		cout << q2.front() << ' ';
		q2.pop();
	}
	cout << endl;
	return 0;
}

/* Test Function Output
1
0
Vertex: 1
Vertex: 2
Vertex: 3
Vertex: 4
Vertex: 5

Vertex: 1
   V:2 Weight:4
Vertex: 2
Vertex: 3
   V:2 Weight:5
   V:4 Weight:7
Vertex: 4
   V:2 Weight:6
Vertex: 5

Vertex: 1
   V:2 Weight:4
Vertex: 2
Vertex: 3
   V:2 Weight:5
   V:4 Weight:7
Vertex: 4
   V:2 Weight:6
Vertex: 5

Vertex: 1
   V:2 Weight:4
   V:4 Weight:7
Vertex: 2
Vertex: 3
   V:2 Weight:5
   V:4 Weight:7
   V:5 Weight:7
Vertex: 4
   V:2 Weight:6
Vertex: 5
   V:1 Weight:1

2 4 5

Vertex: 1
   V:2 Weight:4
   V:4 Weight:7
Vertex: 2
Vertex: 3
   V:2 Weight:5
   V:4 Weight:7
   V:5 Weight:7
Vertex: 4
   V:2 Weight:6
Vertex: 5
   V:1 Weight:1

1
0
Vertex: Portland
Vertex: Seattle
Vertex: San Francisco
Vertex: Los Angeles
Vertex: Sacremento

Vertex: Portland
   V:Seattle Weight:400
   V:San Francisco Weight:789
Vertex: Seattle
   V:San Francisco Weight:800
Vertex: San Francisco
   V:Los Angeles Weight:600
Vertex: Los Angeles
   V:Seattle Weight:700
   V:San Francisco Weight:800
   V:Portland Weight:750
Vertex: Sacremento

Seattle San Francisco Portland
*/
