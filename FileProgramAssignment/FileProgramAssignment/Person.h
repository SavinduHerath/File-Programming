#pragma once
#include <string>

using namespace std;

class Person
{
	char firstName[12];
	char middleName[12];
	char lastName[12];
	char address[128];
	char telephoneNumber[10];
	char email[21];
	int yob;
	char nic[8];

public:
	Person(string first_name, string middle_name, string last_name, string address_, string telephone_number, string email_, int yob_, string nic_);
	Person();
	~Person();
	string getFirstName();
	string getMiddleName();
};