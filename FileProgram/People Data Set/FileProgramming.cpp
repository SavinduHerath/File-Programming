// FileProgramming.cpp : Defines the entry point for the console application.
//
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;


class Person {
public:
	string first_name;
	string middle_name;
	string last_name;
	string address;
	string telephone_number;
	string email;
	int yob;
	string nic;

	Person(string first_name, string middle_name, string last_name, string address, string telephone_number, string email, int yob, string nic) {
		this->first_name = first_name;
		this->middle_name = middle_name;
		this->last_name = last_name;
		this->address = address;
		this->telephone_number = telephone_number;
		this->email = email;
		this->yob = yob;
		this->nic = nic;
	}
};


vector<Person>* populate() {

	vector<Person>* person_data = new vector<Person>();

	ifstream infile("personal_data.csv");
	string line;

	getline(infile, line);//The first line - do nothing

	while (getline(infile, line))
	{
		istringstream tokenStream(line);
		
		string first_name;
		string middle_name;
		string last_name;
		string address;
		string telephone_number;
		string email;
		string yob;
		string nic;

		getline(tokenStream, first_name, ',');
		getline(tokenStream, middle_name, ',');
		getline(tokenStream, last_name, ',');
		getline(tokenStream, address, ',');
		getline(tokenStream, telephone_number, ',');
		getline(tokenStream, email, ',');
		getline(tokenStream, yob, ',');
		getline(tokenStream, nic, ',');
		person_data->push_back(Person(first_name, middle_name, last_name, address, telephone_number, email, stoi(yob), nic));
	}
	return person_data;
}

int main()
{
	vector<Person>* person_data = populate();
	cout << "You have created a vector with " << person_data->size() << " objects." << endl;
	cout << "\nThanks and Best Regards," << endl << "-Chanaka Maduranga Karunarathne-" << endl << endl;
	return 0;
}

