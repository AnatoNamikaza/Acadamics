#pragma once
#include <iostream>
class Person {
private:
	char *Name;
	int Age;
	char *Gender;
public:
	Person();
	Person(const char *name, int age, const char *gender);
	char *GetName();
	int GetAge();
	char *GetGender();
	virtual void copy(const Person &p);
	void SetAge(int x);
	void SetName(const char *name);
	void SetGender(const char *gender);
	void SetInfo(const char *name, int age, const char *gender);
	void UpdateAge();
	void UpdateName();
	void UpdateGender();
	virtual void UpdateInfo();
	virtual void printData();
	virtual ~Person();
};