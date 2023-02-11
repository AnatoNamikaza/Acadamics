
#ifndef TRAINPROJECT_PERSON_H
#define TRAINPROJECT_PERSON_H

#include <iostream>

class Person {
	char Gender;
	int Age;
	std::string Name;
public:
	Person();

	Person(const std::string &, int, char);

	Person(const Person &);

	void setGender(char);

	char getGender() const;

	void setAge(int);

	int getAge() const;

	void setName(const char *);

	void setName(const std::string &);

	const std::string getName() const;

	virtual void setOccupation(const std::string &);

	virtual const std::string getOccupation() const;

	virtual void setQualification(const std::string &);

	virtual const std::string getQualification() const;

	virtual void setNIC(const std::string &);

	virtual const std::string getNIC() const;

	virtual void setBFormNumber(const std::string &);

	virtual const std::string getBFormNumber() const;

	virtual void print();


};


#endif
