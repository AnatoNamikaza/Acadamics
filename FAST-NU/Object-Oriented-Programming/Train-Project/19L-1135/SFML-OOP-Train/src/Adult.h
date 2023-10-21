#pragma once
#include "Person.h"

class Adult :public Person {
private:
	char *Occupation;
	char *Qualification;
	char *NIC;
public:
	Adult();
	Adult(const char *name, int age, const char *gender, char *Occup, const char *Qualif, const char *nic);
	void Adultcopy(Adult &p);
	void PAdultcopy(Adult *p);
	char *GetOccupation();
	char *GetQualification();
	char *GetNIC();
	void SetOccupation(const char *Occup);
	void SetQualification(const char *Qualif);
	void SetNIC(const char *nic);
	void SetInfo(char *name, int age, char *gender, char *Occup, char *Qualif, char *nic);
	void UpdateOccupation();
	void UpdateQualification();
	void UpdateNIC();
	void UpdateInfo() override;
	void printData() override;
	virtual ~Adult();
};
