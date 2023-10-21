#include <fstream>
#include "Person.h"
using namespace std;

Person::Person() {
	this->Name = nullptr;
	this->Age = 0;
	this->Gender = nullptr;
}

Person::Person(const char* name, int age, const char* gender) {
	if (name != nullptr) {
		int size = 0;
		for (int i = 0; name[i] != '\0'; i++) {
			size++;
		}
		size++;
		Name = new char[size];
		for (int i = 0; i < size; i++) {
			this->Name[i] = name[i];
		}
		this->Age = age;
		size = 0;
		for (int i = 0; gender[i] != '\0'; i++) {
			size++;
		}
		size++;
		Gender = new char[size];
		for (int i = 0; i < size; i++) {
			this->Gender[i] = gender[i];
		}
	}
}

char* Person::GetName() {
	return this->Name;
}

int Person::GetAge() {
	return this->Age;
}

char* Person::GetGender() {
	return this->Gender;
}

void Person::copy(const Person &p) {
	int x = p.Age;
	SetAge(x);
	SetName(p.Name);
	SetGender(p.Gender);
}

void Person::SetAge(int x) {
	this->Age = x;
}

void Person::SetName(const char* name) {
	int size = 0;
	for (int i = 0; name[i] != '\0'; i++) {
		size++;
	}
	size++;
	if (this->Name != nullptr) {
		delete[] this->Name;
		this->Name = nullptr;
		this->Name = new char[size];
	}
	else {
		this->Name = new char[size];
	}
	for (int i = 0; i < size; i++) {
		this->Name[i] = name[i];
	}
}

void Person::SetGender(const char* gender) {
	int size = 0;
	for (int i = 0; gender[i] != '\0'; i++) {
		size++;
	}
	size++;
	if (this->Gender != nullptr) {
		delete[] this->Gender;
		this->Gender = nullptr;
		this->Gender = new char[size];
	}
	else {
		this->Gender = new char[size];
	}
	for (int i = 0; i < size; i++) {
		this->Gender[i] = gender[i];
	}
}

void Person::SetInfo(const char* name, int age, const char* gender) {
	int size = 0;
	for (int i = 0; name[i] != '\0'; i++) {
		size++;
	}
	size++;
	if (this->Name != nullptr) {
		delete[] this->Name;
		this->Name = nullptr;
		this->Name = new char[size];
	}
	else {
		this->Name = new char[size];
	}
	for (int i = 0; i < size; i++) {
		this->Name[i] = name[i];
	}
	this->Age = age;
	size = 0;
	for (int i = 0; gender[i] != '\0'; i++) {
		size++;
	}
	size++;
	if (this->Gender != nullptr) {
		delete[] this->Gender;
		this->Gender = nullptr;
		this->Gender = new char[size];
	}
	else {
		this->Gender = new char[size];
	}
	for (int i = 0; i < size; i++) {
		this->Gender[i] = gender[i];
	}

}

void Person::UpdateAge() {
	cout << "Enter New Age: ";
	int x;
	cin >> x;
	this->Age = x;
}

void Person::UpdateName() {
	cout << "Enter Name: \n";
	char *name;
	name = new char[30];
	cin.getline(name, 30, '\n');
	int size = 0;
	for (int i = 0; name[i] != '\0'; i++) {
		size++;
	}
	size++;
	if (this->Name != nullptr) {
		delete[] this->Name;
		this->Name = nullptr;
		this->Name = new char[size];
	}
	else {
		this->Name = new char[size];
	}
	for (int i = 0; i < size; i++) {
		this->Name[i] = name[i];
	}
}

void Person::UpdateGender() {
	cout << "Enter Gender: \n";
	char *gender;
	gender = new char[20];
	cin.getline(gender, 20, '\n');
	int size = 0;
	for (int i = 0; gender[i] != '\0'; i++) {
		size++;
	}
	size++;
	if (this->Gender != nullptr) {
		delete[] this->Gender;
		this->Gender = nullptr;
		this->Gender = new char[size];
	}
	else {
		this->Gender = new char[size];
	}
	for (int i = 0; i < size; i++) {
		this->Gender[i] = gender[i];
	}
}

void Person::UpdateInfo() {
	cout << "Enter Name: \n";
	char *name;
	name = new char[20];
	cin.getline(name, 20, '\n');
	int size = 0;
	for (int i = 0; name[i] != '\0'; i++) {
		size++;
	}
	size++;
	if (this->Name != nullptr) {
		delete[] this->Name;
		this->Name = nullptr;
		this->Name = new char[size];
	}
	else {
		this->Name = new char[size];
	}
	for (int i = 0; i < size; i++) {
		this->Name[i] = name[i];
	}
	cout << "Enter Gender: \n";
	char *gene;
	gene = new char[8];
	cin.getline(gene, 8, '\n');
	size = 0;
	for (int i = 0; gene[i] != '\0'; i++) {
		size++;
	}
	size++;
	if (this->Gender != nullptr) {
		delete[] this->Gender;
		this->Gender = nullptr;
		this->Gender = new char[size];
	}
	else {
		this->Gender = new char[size];
	}
	for (int i = 0; i < size; i++) {
		this->Gender[i] = gene[i];
	}
	cout << "Enter Age: \n";
	int age;
	cin >> age;
	this->Age = age;
	delete[] name;
	name = nullptr;
	delete[] gene;
	gene = nullptr;
	age = 0;
}

void Person::printData() {
	if (this->Name != nullptr) {
		cout << "( Name: " << this->Name << ", Age: " << this->Age << ", Gender: " << this->Gender << " )" << endl;
	}
	else {
		cout << "No data found." << endl;
	}
}

Person::~Person() {
//	cout << "P destor called" << endl;
	delete[] Name;
	Name = nullptr;
	delete[] Gender;
	Gender = nullptr;
	Age = 0;
}
