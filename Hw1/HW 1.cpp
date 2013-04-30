//Rick Sullivan
//Homework 1
//16 January 2013
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Analyzer{
	private:
		string longWord;
		string shortWord;
		float avg;
	public:
		void input(char* fileName);
		void average();
		void longest();
		void shortest();
};

void Analyzer::input(char* fileName){
	ifstream fileReader;
	fileReader.open(fileName);
	if(fileReader.is_open()){
		string buffer;
		unsigned int wordCount = 0;
		unsigned int totalChars = 0;
		while(fileReader.good()){
			fileReader >> buffer;
			unsigned int i = 0;
			//Remove any non-letter characters from the buffer string.
			while(i < buffer.length()){
				if(!isalpha(buffer[i])){
					buffer.erase(i, 1);
				}
				else
					i++;
			}
			if(buffer.length() > 0){
				totalChars += buffer.length();
				wordCount ++;
				if(buffer.length() > longWord.length() || wordCount <= 1)
					longWord = buffer;
				if(buffer.length() <= shortWord.length() || wordCount <= 1)
					shortWord = buffer;
			}
		}
		avg = float(totalChars)/float(wordCount);
	}
	fileReader.close();
}

void Analyzer::average(){
	cout << "The average word's length is " << setprecision(3) << avg << endl;
}

void Analyzer::longest(){
	cout << "The longest word is '" << longWord << "'" << endl;
}

void Analyzer::shortest(){
	cout << "The shortest word is '" << shortWord << "'" << endl;
}

int main() {
	Analyzer A;
	A.input("GettysburgAddress.txt"); 	
	A.average();						
	A.longest();						
	A.shortest();
	return 0;
}

/******  Tests:  ****************
shortTest.txt: "one two" 
	tests:	Choosing the first longest and last shortest words.
			Calculating average correctly.
	prints:	The average word's length is 3
			The longest word is 'one'
			The shortest word is 'two'

hw1test.txt: "short longword medium"
	tests:	Finding the longest and shortest words.
	prints:	The average word's length is 6.33
			The longest word is 'longword'
			The shortest word is 'short'

********************************/		