#include <iostream>
#include <fstream>
#include "kid.h"
using namespace std;

kid::kid() : Person() {
		this->B_form_number = nullptr;
	}

kid::kid(const char *name, int age, const char *gender, const char *BFNUM) : Person(name, age, gender) {
		if (BFNUM != nullptr) {
			int size = 0;
			for (int i = 0; BFNUM[i] != '\0'; i++) {
				size++;
			}
			size++;
			B_form_number = new char[size];
			for (int i = 0; i < size; i++) {
				this->B_form_number[i] = BFNUM[i];
			}
		}
		else {
			B_form_number = nullptr;
		}
	}

void kid::Kidcopy(kid &p) {
		Person::SetName(p.GetName());
		Person::SetAge(p.GetAge());
		Person::SetGender(p.GetGender());
		SetB_form_number(p.B_form_number);
	}

void kid::PKidcopy(kid *p) {
		Person::SetName(p->GetName());
		Person::SetAge(p->GetAge());
		Person::SetGender(p->GetGender());
		SetB_form_number(p->B_form_number);
	}

char* kid::GetB_form_number() {
		return this->B_form_number;
	}

void kid::SetB_form_number(const char *BFNUM) {
		int size = 0;
		for (int i = 0; BFNUM[i] != '\0'; i++) {
			size++;
		}
		size++;
		this->B_form_number = new char[size];
		for (int i = 0; i < size; i++) {
			this->B_form_number[i] = BFNUM[i];
		}
	}

void kid::SetInfo(char *name, int age, char *gender, char *BFNUM) {
		if (BFNUM != nullptr) {
			Person::SetInfo(name, age, gender);
			int size = 0;
			for (int i = 0; BFNUM[i] != '\0'; i++) {
				size++;
			}
			size++;
			if (this->B_form_number != nullptr) {
				delete[] this->B_form_number;
				this->B_form_number = nullptr;
				this->B_form_number = new char[size];
			}
			else {
				this->B_form_number = new char[size];
			}
			for (int i = 0; i < size; i++) {
				this->B_form_number[i] = BFNUM[i];
			}
		}
		else {
			Person::SetInfo(name, age, gender);
		}
	}

void kid::UpdateB_form_number() {
		cout << "Enter Birth form no: \n";
		char *BFNUM;
		BFNUM = new char[30];
		cin.getline(BFNUM, 20, '\n');
		int size = 0;
		for (int i = 0; BFNUM[i] != '\0'; i++) {
			size++;
		}
		size++;
		if (this->B_form_number != nullptr) {
			delete[] this->B_form_number;
			this->B_form_number = nullptr;
			this->B_form_number = new char[size];
		}
		else {
			this->B_form_number = new char[size];
		}
		for (int i = 0; i < size; i++) {
			this->B_form_number[i] = BFNUM[i];
		}
	}

void kid::UpdateInfo()  {
		Person::UpdateInfo();

		//--------------------------------------------
		cout << "Enter B_form_number: \n";
		char *Bform;
		Bform = new char[15];
		cin.ignore(1, '\n');
		cin.clear();
		cin.getline(Bform, 15, '\n');
		SetB_form_number(Bform);

		//--------------------------------------------
		delete[] Bform;
		Bform = nullptr;
	}

void kid::printData() {
		if (B_form_number != nullptr) {
			Person::printData();
			cout << "( B_form_number: " << this->B_form_number << " )" << endl;
		}
		else {
			Person::printData();
			cout << "B_form data not present." << endl;
		}
	}

kid::~kid() {
//		cout << "K destor called" << endl;
	delete[] B_form_number;
	B_form_number = nullptr;
}

