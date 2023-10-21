#pragma once
#include "Adult.h"
#include "kid.h"
#include <TGUI/TGUI.hpp>

class Bogie {
private:
	int Bogie_ID;
	Bogie *next;
	Person **Adults;
	Person **kids;
	char *familyName;
	int MaxPassengersNo;
	int PassengersNo;
	int MaxAdultsNo;
	int AdultsNo;
	int MaxkidsNo;
	int kidsNo;

public:
	Bogie();
	Bogie(int id);
	void BogieCopy(Bogie &B);
	int GetID();
	Bogie *GetNext();
	Person *GetkidsP(int i);
	Person *GetAdultsP(int i);
	char *GetfamilyName();
	int GetPassengersNo();
	int GetAdultsNo();
	int GetkidsNo();
	int GetMaxPassengersNo();
	int GetMaxAdultsNo();
	int GetMaxkidsNo();
	bool compare(char* P1,char* P2);
	void SetNext(Bogie *N);
	void SetAdults(Person** A);
	void Setkids(Person** K);
	void SetID(int x);
	void SetMaxPassengersNo(int x);
	void SetMaxAdultsNo(int x);
	void SetMaxkidsNo(int x);
	void SetPassengersNo(int x);
	void SetAdultsNo(int x);
	void SetkidsNo(int x);
	void SetfamilyName(const char* p);
	void UpdateID();
	void UpdateMaxPassengersNo();
	void UpdateMaxAdultsNo();
	void UpdateMaxkidsNo();
	void UpdateBogieInfo(int Ax, int Ky, char *temp);
	bool AddPassengers();
	void AddNewPassengers();
	void RemovePassengers();
	void Print();
	~Bogie();
};