#include <iostream>
#include <fstream>
#include "Adult.h"
using namespace std;

Adult::Adult() : Person() {
		this->Occupation = nullptr;
		this->Qualification = nullptr;
		this->NIC = nullptr;
	}

Adult::Adult(const char *name, int age, const char *gender, char *Occup, const char *Qualif, const char *nic) : Person(
		name, age, gender) {
		if (Occup != nullptr) {
			int size = 0;
			for (int i = 0; Occup[i] != '\0'; i++) {
				size++;
			}
			size++;
			Occupation = new char[size];
			for (int i = 0; i < size; i++) {
				this->Occupation[i] = Occup[i];
			}
		}
		else {
			this->Occupation = nullptr;
		}

		if (Qualif != nullptr) {
			int size = 0;
			for (int i = 0; Qualif[i] != '\0'; i++) {
				size++;
			}
			size++;
			Qualification = new char[size];
			for (int i = 0; i < size; i++) {
				this->Qualification[i] = Qualif[i];
			}
		}
		else {
			this->Qualification = nullptr;
		}

		if (nic != nullptr) {
			int size = 0;
			for (int i = 0; nic[i] != '\0'; i++) {
				size++;
			}
			size++;
			NIC = new char[size];
			for (int i = 0; i < size; i++) {
				this->NIC[i] = nic[i];
			}
		}
		else {
			this->NIC = nullptr;
		}
	}

void Adult::Adultcopy(Adult &p) {
		SetName(p.GetName());
		SetAge(p.GetAge());
		SetGender(p.GetGender());
		SetOccupation(p.Occupation);
		SetQualification(p.Qualification);
		SetNIC(p.NIC);
	}

void Adult::PAdultcopy(Adult *p) {
		SetName(p->GetName());
		SetAge(p->GetAge());
		SetGender(p->GetGender());
		SetOccupation(p->Occupation);
		SetQualification(p->Qualification);
		SetNIC(p->NIC);
	}

char* Adult::GetOccupation() {
		return this->Occupation;
	}

char* Adult::GetQualification() {
		return this->Qualification;
	}

char* Adult::GetNIC() {
		return this->NIC;
	}

void Adult::SetOccupation(const char *Occup) {
		int size = 0;
		for (int i = 0; Occup[i] != '\0'; i++) {
			size++;
		}
		size++;
		this->Occupation = new char[size];
		for (int i = 0; i < size; i++) {
			this->Occupation[i] = Occup[i];
		}
	}

void Adult::SetQualification(const char *Qualif) {
		int size = 0;
		for (int i = 0; Qualif[i] != '\0'; i++) {
			size++;
		}
		size++;
		this->Qualification = new char[size];
		for (int i = 0; i < size; i++) {
			this->Qualification[i] = Qualif[i];
		}
	}

void Adult::SetNIC(const char *nic) {
		int size = 0;
		for (int i = 0; nic[i] != '\0'; i++) {
			size++;
		}
		size++;
		if (this->NIC != nullptr) {
			delete[] this->NIC;
			this->NIC = nullptr;
			this->NIC = new char[size];
		}
		else {
			this->NIC = new char[size];
		}
		for (int i = 0; i < size; i++) {
			this->NIC[i] = nic[i];
		}
	}

void Adult::SetInfo(char *name, int age, char *gender, char *Occup, char *Qualif, char *nic) {
		Person::SetInfo(name, age, gender);
		if (Occup != nullptr) {
			SetOccupation(Occup);
		}
		if (Qualif != nullptr) {
			SetQualification(Qualif);
		}
		if (nic != nullptr) {
			SetNIC(nic);
		}
	}

void Adult::UpdateOccupation() {
		cout << "Enter Occupation: \n";
		char *Occup;
		Occup = new char[38];
		cin.getline(Occup, 38, '\n');
		SetOccupation(Occup);

		delete[] Occup;
		Occup = nullptr;
	}

void Adult::UpdateQualification() {
		cout << "Enter Qualification: \n";
		char *Qualif;
		Qualif = new char[40];
		cin.getline(Qualif, 40, '\n');
		SetQualification(Qualif);

		delete[] Qualif;
		Qualif = nullptr;
	}

void Adult::UpdateNIC() {
		cout << "Enter NIC: \n";
		char *nic;
		nic = new char[15];
		cin.getline(nic, 15, '\n');
		SetQualification(nic);

		delete[] nic;
		nic = nullptr;
	}

void Adult::UpdateInfo() {
		Person::UpdateInfo();

		//--------------------------------------------
		cout << "Enter Occupation: \n";
		char *Occup;
		Occup = new char[38];
		cin.ignore(1, '\n');
		cin.clear();
		cin.getline(Occup, 38, '\n');
		SetOccupation(Occup);

		//--------------------------------------------
		cout << "Enter Qualification: \n";
		char *Qualif;
		Qualif = new char[40];
		cin.getline(Qualif, 40, '\n');
		SetQualification(Qualif);

		//--------------------------------------------
		cout << "Enter NIC: \n";
		char *nic;
		nic = new char[15];
		cin.getline(nic, 15, '\n');
		SetNIC(nic);

		//--------------------------------------------
		delete[] Occup;
		Occup = nullptr;
		delete[] Qualif;
		Qualif = nullptr;
		delete[] nic;
		nic = nullptr;
	}

void Adult::printData() {
		Person::printData();
		cout << "( NIC: " << this->NIC << ", Qualification: " << this->Qualification << ", Occupation: "
			<< this->Occupation << " )" << endl;
	}

Adult::~Adult() {
//		cout << "A destor called" << endl;
		delete[] Occupation;
		Occupation = nullptr;
		delete[] Qualification;
		Qualification = nullptr;
		delete[] NIC;
		NIC = nullptr;
	}


