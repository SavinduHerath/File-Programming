#include "Person.h"

Person::Person(string first_name, string middle_name, string last_name, string address_, string telephone_number, string email_, int yob_, string nic_)
{
	strcpy(firstName, first_name.c_str());
	strcpy(middleName, middle_name.c_str());
	strcpy(lastName, last_name.c_str());
	strcpy(address, address_.c_str());
	strcpy(telephoneNumber,telephone_number.c_str());
	strcpy(email, email_.c_str());
	yob = yob_;
	strcpy(nic, nic_.c_str());
}

Person::Person()
{}


Person::~Person()
{}

string Person::getFirstName()
{
	return firstName;
}

string Person::getMiddleName()
{
	return middleName;
}
