/************************************
Rick Sullivan
Homework 3
23 January 2013
*************************************/
#include <iostream>
#include <string>

using namespace std;

class StudentRecord {
	public:
		// constructors
		StudentRecord();
		StudentRecord(string fName, string lName, int identification, float gradePoint, string enrollmentStatus, int enrollmentNumber);
		// destructor
		~StudentRecord();
		// copy constructor
		StudentRecord(const StudentRecord& other);
		// assignment operator
		const StudentRecord& operator=(const StudentRecord& other);
		// input/output operators
		friend ostream& operator<<(ostream& out_str, const StudentRecord& rhs);
		friend istream& operator>>(istream& in_str, StudentRecord& rhs);
		// accessors
		string getFirstName();
		string getLastName();
		int getID();
		float getGPA();
		string getEnrollment();
		int getNumEnroll();
		// mutators
		void setFirstName(string name);
		void setLastName(string name);
		void setID(int intNum);
		void setGPA(float floatNum);
		void setEnrollment(string openOrClosed);
		void setNumEnroll(int intCredits);
	private:
		string _firstName;
		string _lastName;
		int _id;
		float _gpa;
		//I cannot find any information on a 'string*' type, so I just used string. 
		//If we are supposed to use char*, I can change my code very easily.
		//I tried to keep some pointer concepts in my commening.
		string _enrollment;
		int _numEnroll;
};

//constructors
StudentRecord::StudentRecord(){
	_firstName = "first";
	_lastName = "last";
	_id = 0;
	_gpa = 0;
	//If string* was an actual pointer type, we would allocate memory:
	//if(_enrollment == NULL)
	//	_enrollment = new string;
	_enrollment = "closed";
	_numEnroll = 0;
}

StudentRecord::StudentRecord(string fName, string lName, int identification, float gradePoint, string enrollmentStatus, int enrollmentNumber){
	_firstName = fName;
	_lastName = lName;
	_id = identification;
	_gpa = gradePoint;
	_enrollment = enrollmentStatus;
	_numEnroll = enrollmentNumber;
}

// destructor
StudentRecord::~StudentRecord(){
	/* If string* actually existed we would have to deallocate the memory:
	if(_enrollment != NULL){
		delete _enrollment;
	}
	*/
}

// copy constructor
StudentRecord::StudentRecord(const StudentRecord& other){
	//Initialize pointer
	//_enrollment = NULL;
	*this = other;
}

// assignment operator
const StudentRecord& StudentRecord::operator=(const StudentRecord& other){
	if(this == &other){
		return *this;
	}
	_firstName = other._firstName;
	_lastName = other._lastName;
	_id = other._id;
	_gpa = other._gpa;
	/*
	if(_enrollment == NULL){
		_enrollment = new string;
	}
	*/
	_enrollment = other._enrollment;
	_numEnroll = other._numEnroll;
	return *this;
}

// input/output operators
ostream& operator<<(ostream& out_str, const StudentRecord& rhs){
	out_str << rhs._firstName << ' ' << rhs._lastName << " ID #: " << rhs._id << " GPA: " << rhs._gpa 
			<< " Enrollment: " << rhs._enrollment << " Number of Credits: " << rhs._numEnroll;
	return out_str;
}

istream& operator>>(istream& in_str, StudentRecord& rhs){
	in_str >> rhs._firstName >> rhs._lastName >> rhs._id >> rhs._gpa >> rhs._enrollment >> rhs._numEnroll;
	return in_str;
}

// accessors
string StudentRecord::getFirstName(){
	return _firstName;
}

string StudentRecord::getLastName(){
	return _lastName;
}

int StudentRecord::getID(){
	return _id;
}

float StudentRecord::getGPA(){
	return _gpa;
}

string StudentRecord::getEnrollment(){
	return _enrollment;
}

int StudentRecord::getNumEnroll(){
	return _numEnroll;
}

// mutators
void StudentRecord::setFirstName(string name){
	_firstName = name;
}

void StudentRecord::setLastName(string name){
	_lastName = name;
}

void StudentRecord::setID(int intNum){
	_id = intNum;
}

void StudentRecord::setGPA(float floatNum){
	_gpa = floatNum;
}

void StudentRecord::setEnrollment(string openOrClosed){
	_enrollment = openOrClosed;
}

void StudentRecord::setNumEnroll(int intCredits){
	_numEnroll = intCredits;
}

int main(void){
	StudentRecord Z(string("Rick"), string("Sullivan"), 12345, 4.01, "open", 20);
	cout << "Z: " << Z << endl;
	StudentRecord A;
	cout << "Input in the following format:" << endl;
	cout << "FirstName LastName IDNumber GPA EnrollmentStatus NumberOfCredits" << endl;
	cin >> A;
	cout << "A: " << A << endl;
	StudentRecord B(A);
	cout << "B: " << B << endl;
	Z = A;
	cout << "Z: " << Z.getFirstName() << Z.getLastName() << Z.getID() << Z.getGPA() << Z.getEnrollment() << Z.getNumEnroll() << endl;
	Z.setFirstName("P.");
	Z.setLastName("Sherman");
	Z.setID(42);
	Z.setGPA(0);
	Z.setEnrollment("Wallaby Way");
	Z.setNumEnroll(12345);
	cout << "Z: " << Z << endl;
	return 0;
}

/****************************** 
	This main outputs:
	Z: Rick Sullivan ID #: 12345 GPA: 4.01 Enrollment: open Number of Credits: 20
	Input in the following format:
	FirstName LastName IDNumber GPA EnrollmentStatus NumberOfCredits
	John Smith 98765 2.50 OPEN 15
	A: John Smith ID #: 98765 GPA: 2.5 Enrollment: OPEN Number of Credits: 15
	B: John Smith ID #: 98765 GPA: 2.5 Enrollment: OPEN Number of Credits: 15
	Z: JohnSmith987652.5OPEN15
	Z: P. Sherman ID #: 42 GPA: 0 Enrollment: Wallaby Way Number of Credits: 12345
*****************************/


