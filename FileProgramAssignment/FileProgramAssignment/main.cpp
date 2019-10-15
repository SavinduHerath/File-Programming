#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <map>
#include "Person.h"

using namespace std;

vector<Person>* addToVector()
{
	vector<Person>* personData = new vector<Person>();

	ifstream infile("personal_data.csv");
	string line;
	getline(infile, line);

	while (getline(infile, line))
	{
		istringstream token(line);

		string first_name;
		string middle_name;
		string last_name;
		string address;
		string telephone_number;
		string email;
		string yob;
		string nic;

		getline(token, first_name, ',');
		getline(token, middle_name, ',');
		getline(token, last_name, ',');
		getline(token, address, ',');
		getline(token, telephone_number, ',');
		getline(token, email, ',');
		getline(token, yob, ',');
		getline(token, nic, ',');
		personData->push_back(Person(first_name, middle_name, last_name, address, telephone_number, email, stoi(yob), nic));
	}
	cout << personData->size() << endl;
	return personData;
}

void binaryWrite(vector<Person>* personData)
{
	ofstream file;
	file.open("person.txt", ios::out | ios::binary);
	if (!file) {
		cout << "Error in creating file...\n" << endl;
	}
	for (vector<Person>::iterator it = personData->begin(); it != personData->end(); ++it) {
		//Person tem = it*;
		Person tem = (Person)*it;
		file.write((char*)&tem, sizeof(tem));
	}
	file.close();
}

vector<Person>* binaryRead()
{
	Person temp = Person();
	vector<Person>* readPersons = new vector<Person>();
	ifstream infile;
	infile.open("person.txt", ios::binary | ios::in);
	while (infile.read((char*)&temp, sizeof(temp)))
	{
		//infile.read((char*)&temp, sizeof(temp));
		readPersons->push_back(temp);
	}
	infile.close();
	return readPersons;
}

void createIndexFile()
{
	Person temp = Person();
	multimap <string, int> indexMap;
	//vector<Person>* readPersons = new vector<Person>();
	ifstream infile;
	infile.open("person.txt", ios::binary | ios::in);
	int position = infile.tellg();
	while (infile.read((char*)&temp, sizeof(temp)))
	{
		indexMap.insert({ temp.getFirstName(), position });
		position = infile.tellg();
	}

	ofstream indexFile;
	indexFile.open("indexfile.csv", ios::out);
	for (multimap<string, int>:: iterator it = indexMap.begin(); it != indexMap.end(); it++)
	{
		indexFile << it->first << "," << it->second << "\n";
	}
}

vector<Person>* findIndex(string first_name)
{
	vector<Person>* foundPersons = new vector<Person>();
	ifstream indexFile;
	indexFile.open("indexfile.csv");
	string line;

	while (getline(indexFile,line))
	{
		stringstream strstream(line);
		string name_in_file;
		string posStr;
		int position;
		getline(strstream, name_in_file, ',');

		if (name_in_file == first_name)
		{
			getline(strstream, posStr, ',');
			position = stoi(posStr);

			Person P;
			ifstream binaryFile;
			binaryFile.open("person.txt", ios::in | ios::binary);
			binaryFile.seekg(position);
			binaryFile.read((char*)&P, sizeof(P));
			foundPersons->push_back(P);
		}
	}
	if (foundPersons->size() == 0)
	{
		cout << first_name << " is not in the list" << endl;
	}
	return foundPersons;
}

vector<Person>* findWithoutIndex(string first_name)
{
	Person temp = Person();
	//multimap <string, int> indexMap;
	vector<Person>* foundPersons = new vector<Person>();
	ifstream infile;
	infile.open("person.txt", ios::binary | ios::in);
	//int position = infile.tellg();
	while (infile.read((char*)&temp, sizeof(temp)))
	{
		if (temp.getFirstName() == first_name)
		{
			foundPersons->push_back(temp);
		}
		//indexMap.insert({ temp.getFirstName(), position });
		//position = infile.tellg();
	}
	if (foundPersons->size() == 0)
	{
		cout << first_name << " is not in the list" << endl;
	}
	return foundPersons;
}

int main()
{
	vector<Person>* personData = addToVector();

	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	binaryWrite(personData);
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	auto duration1 = chrono::duration<double>(t2 - t1).count();
	cout << "Binary write time: " << duration1 << endl;

	chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();
	vector<Person>* readList = binaryRead();
	chrono::high_resolution_clock::time_point t4 = chrono::high_resolution_clock::now();
	auto duration2 = chrono::duration<double>(t4 - t3).count();
	cout << "Binary read time: " << duration2 << endl;


	createIndexFile();

	chrono::high_resolution_clock::time_point t5 = chrono::high_resolution_clock::now();
	vector<Person>* readListWithIndex = findIndex("Judd");
	chrono::high_resolution_clock::time_point t6 = chrono::high_resolution_clock::now();
	auto duration3 = chrono::duration<double>(t6 - t5).count();
	cout << "Find time with index: " << duration3 << endl;

	if (readListWithIndex->size() != 0)
	{
		for (vector<Person>::iterator it = readListWithIndex->begin(); it != readListWithIndex->end(); it++)
		{
			cout << it->getMiddleName() << endl;
		}
	}

	chrono::high_resolution_clock::time_point t7 = chrono::high_resolution_clock::now();
	vector<Person>* readListWithoutIndex = findWithoutIndex("Judd");
	chrono::high_resolution_clock::time_point t8 = chrono::high_resolution_clock::now();
	auto duration4 = chrono::duration<double>(t8 - t7).count();
	cout << "Find time without index: " << duration4 << endl;

	if (readListWithoutIndex->size() != 0)
	{
		for (vector<Person>::iterator it = readListWithoutIndex->begin(); it != readListWithoutIndex->end(); it++)
		{
			cout << it->getMiddleName() << endl;
		}
	}

	return 0;
}

