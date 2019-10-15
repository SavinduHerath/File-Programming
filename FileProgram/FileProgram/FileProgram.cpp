#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "FileProgram.h"
using namespace std;

int main()
{
	string tmp;
	int i = 0;
	vector<Person*> personVector;
	vector<string> personData;
	ifstream infile("test.txt");
	while (getline(infile,tmp))
	{
		string tmp2;
		stringstream   linestream(tmp);
		while (getline(linestream, tmp2, ','))
		{
			personData.push_back(tmp2);
			cout << tmp << endl;
		}
		string firstName = personData[i];
		string lastName = personData[i + 1];
		string age = personData[i + 2];
		Person* P = new Person{ firstName, lastName, age };
		personVector.push_back(P);
		i += 3;
	}
	return 0;
}