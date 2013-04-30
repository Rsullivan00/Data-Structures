/////////////////////////////////
////	File: Hw6.cpp
////	Author: Rick Sullivan
////	Coen 70 Homework #6: 
////		Class Inheritance
/////////////////////////////////

#include <iostream>

using namespace std;

class Person{
private:
	string name;
public:
	Person();
	Person(const Person&);
	Person(string _name);
	~Person();
	const Person& operator=(const Person&);
	friend ostream& operator<<(ostream&, const Person&);
	friend istream& operator>>(istream&, Person&);
	string getName();
	void setName(string _name);
};

////////////////////////////////////////
////	Person Class Implementation
////////////////////////////////////////

Person::Person(){
	name = "";
}

Person::Person(const Person& other){
	*this = other;
}

Person::Person(string _name){
	name = _name;
}

Person::~Person(){
	//Do nothing
}

//Operators

const Person& Person::operator=(const Person& other){
	if(this == &other){
		return *this;
	}
	name = other.name;
	return *this;
}

ostream& operator<<(ostream& out_str, const Person& rhs){
	out_str << rhs.name;
	return out_str;
}

istream& operator>>(istream& in_str, Person& rhs){
	in_str >> rhs.name;
	return in_str;
}

//Accessor

string Person::getName(){
	return name;
}

//Mutator

void Person::setName(string _name){
	name = _name;
}

class Vehicle{
private:
	string manufacturer;
	int cylinderCount;
	Person owner;
public:
	Vehicle();
	Vehicle(const Vehicle&);
	~Vehicle();
	const Vehicle& operator=(const Vehicle&);
	friend ostream& operator<<(ostream&, const Vehicle&);
	friend istream& operator>>(istream&, Vehicle&);
	string getManufacturer();
	int getCylinderCount();
	Person getOwner();

	void setManufacturer(string _manufacturer);
	void setCylinderCount(int _cylinderCount);
	void setOwner(Person _owner);
};

////////////////////////////////////////
////	Vehicle Class Implementation
////////////////////////////////////////

Vehicle::Vehicle(){
	manufacturer = "";
	cylinderCount = 0;
	owner = Person();
}

Vehicle::Vehicle(const Vehicle& other){
	*this = other;
}

Vehicle::~Vehicle(){
	//Do nothing
}

//Operators

const Vehicle& Vehicle::operator=(const Vehicle& other){
	if(this == &other){
		return *this;
	}
	manufacturer = other.manufacturer;
	cylinderCount = other.cylinderCount;
	owner = other.owner;
	return *this;
}

ostream& operator<<(ostream& out_str, const Vehicle& rhs){
	out_str << rhs.manufacturer << ' ' << rhs.cylinderCount << ' ' << rhs.owner;
	return out_str;
}

istream& operator>>(istream& in_str, Vehicle& rhs){
	in_str >> rhs.manufacturer >> rhs.cylinderCount >> rhs.owner;
	return in_str;
}

//Accessors

string Vehicle::getManufacturer(){
	return manufacturer;
}

int Vehicle::getCylinderCount(){
	return cylinderCount;
}

Person Vehicle::getOwner(){
	return owner;
}

//Mutators

void Vehicle::setManufacturer(string _manufacturer){
	manufacturer = _manufacturer;
}

void Vehicle::setCylinderCount(int _cylinderCount){
	cylinderCount = _cylinderCount;
}

void Vehicle::setOwner(Person _owner){
	owner = _owner;
}

class Truck: public Vehicle{
private:
	double load;
	int tow;
public:
	Truck();
	Truck(const Truck&);
	~Truck();
	const Truck& operator=(const Truck&);
	friend ostream& operator<<(ostream&, const Truck&);
	friend istream& operator>>(istream&, Truck&);

	double getLoad();
	int getTow();

	void setLoad(double _load);
	void setTow(int _tow);
};

////////////////////////////////////////
////	Truck Class Implementation
////////////////////////////////////////

Truck::Truck(): Vehicle(){
	load = 0;
	tow = 0;
}

Truck::Truck(const Truck& other): Vehicle(other){
	*this = other;
}

Truck::~Truck(){
	//Do nothing
}

//Operators

const Truck& Truck::operator=(const Truck& other){
	if(this == &other){
		return *this;
	}
	Vehicle::operator=(other);
	load = other.load;
	tow = other.tow;
	return *this;
}

ostream& operator<<(ostream& out_str, const Truck& rhs){
	out_str << static_cast <Vehicle>(rhs) << ' ' << rhs.load << ' ' << rhs.tow;
	return out_str;
}

istream& operator>>(istream& in_str, Truck& rhs){
	in_str >> dynamic_cast <Vehicle&>(rhs) >> rhs.load >> rhs.tow;
	return in_str;
}

//Accessors

double Truck::getLoad(){
	return load;
}

int Truck::getTow(){
	return tow;
}

//Mutators

void Truck::setLoad(double _load){
	load = _load;
}

void Truck::setTow(int _tow){
	tow = _tow;
}

//Test function
int main(){
	Person A;
	A.setName("Rick");
	cout << A << endl;
	Person B(A);	
	cout << B << endl;

	cin >> B;
	cout << B << endl;
	Person A2("Adam");
	cout << A2 << endl;
	A2 = A;
	cout << A2 << endl;
	cout << A2.getName() << endl;

	Vehicle C;
	C.setManufacturer("Honda");
	C.setCylinderCount(6);
	C.setOwner(A);
	cout << C << endl;

	Vehicle C2(C);	
	cout << C2 << endl;

	cin >> C2;
	cout << C2 << endl;
	cout << C2.getOwner() << ' ' << C2.getManufacturer() << ' '
	<< C2.getCylinderCount() << endl;

	C = C2;
	cout << C << endl;

	Truck D;
	D.setManufacturer("Honda");
	D.setCylinderCount(6);
	D.setOwner(A);
	D.setLoad(1200);
	D.setTow(500);
	cout << D << endl;

	Truck E(D);	
	cout << E << endl;

	cin >> E;
	cout << E << endl;

	D = E;
	cout << D.getManufacturer() << ' ' << D.getCylinderCount() << ' '
	<< D.getOwner() << ' ' << D.getLoad() << ' ' << D.getTow() << endl;
	return 0;
}

/* Test Function Output:
	Rick
	Rick
	Eddie	//Input
	Eddie
	Adam
	Rick
	Rick
	Honda 6 Rick
	Honda 6 Rick
	Pagani 12 Willy		//Input
	Pagani 12 Willy
	Willy Pagani 12
	Pagani 12 Willy
	Honda 6 Rick 1200 500
	Honda 6 Rick 1200 500
	Ferrari 10 Jacob 5000 1000		//Input
	Ferrari 10 Jacob 5000 1000
	Ferrari 10 Jacob 5000 1000
*/
