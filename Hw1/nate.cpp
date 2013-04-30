//Nathan Matsunaga COEN 70
#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<cmath>
using namespace std;

class Analyzer{

        private:
                float ave;
                string _longest;
                string _shortest;
        public:
                Analyzer();
                ~Analyzer();
                void input(char*);
                void average();
                void longest();
                void shortest();
};

Analyzer::Analyzer(){}

Analyzer::~Analyzer(){}

//Reads through the text file and records the first longest word, the last shortest word, and the total characters and total words used to calculate the average.
void Analyzer::input(char* fname){

        ifstream in_file;
        in_file.open(fname);

        int d = 0;
        int totalchar  = 0;
        int totalword = 0;
        int l = 0;
        string word;

        _shortest = "aaaaaaaaaaaaaa";

        //Reads until the end of the file is reached.
        while(in_file && in_file.peek() != EOF){

                in_file >> word;

                d = 0;

                //Scans through word and removes any punctutation.
                while(word[d] != '\0'){

                        if(ispunct(word[d])){

                                l = d;

                                while(word[l] != '\0'){

                                        word[l] = word[l+1];
                                        l++;
                                }

                                d--;
                        }

                        d++;
                }

                if(word[0] != '\0'){

                        totalchar += d;
                        totalword++;

                        if(d > _longest.length()){

                                _longest = word;
                        }

                        if(word.length() <= _shortest.length()){

                                _shortest = word;
                        }

                        cout << word << word.length() << d << endl;
                }
        }

  //      totalchar -= d;
    //    totalword--;

        cout << totalchar << endl;
        cout << totalword << endl;

        ave = float(totalchar) / float(totalword);

        return;
}

//Prints out the average word length for the file.
void Analyzer::average(){

        cout << "The average word length is:";
        cout << setprecision(3) << ave;
        cout << endl;

        return;
}

//Prints out the first longest word encountered in the file.
void Analyzer::longest(){

        cout << "The longest word is:" ;
        cout << _longest;
        cout << endl;

        return;
}

//Prints out the last shortest word encoutered in the file.
void Analyzer::shortest(){

        cout << "The shortest word is:";
        cout << _shortest;
        cout << endl;

        return;
}

int main(){

        Analyzer A;
        A.input("GettysburgAddress.txt");
        A.average();
        A.longest();
        A.shortest();
/*
        Analyzer B;
        B.input("test.txt");
        B.average();
        B.longest();
        B.shortest();
*/
        return 0;
}
