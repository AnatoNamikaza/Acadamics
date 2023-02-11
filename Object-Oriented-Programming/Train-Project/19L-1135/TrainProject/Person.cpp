
#include "Person.h"

Person::Person() : Gender(0), Age(0), Name("") {}

Person::Person(const std::string &name, int a, char g) {
	Gender = g;
	Age = a;
	Name.assign(name);
}

Person::Person(const Person &p) {
	Age = p.Age;
	Gender = p.Gender;
	Name.assign(p.Name);
}

void Person::setGender(char g) {
	Gender = g;
}

char Person::getGender() const {
	return Gender;
}

void Person::setAge(int a) {
	Age = a;
}

int Person::getAge() const {
	return Age;
}

void Person::setName(const char *n) {
	Name.assign(n);
}

void Person::setName(const std::string &n) {
	Name.assign(n);
}

const std::string Person::getName() const {
	return Name;
}

void Person::setOccupation(const std::string &) {}

const std::string Person::getOccupation() const {}

void Person::setQualification(const std::string &) {}

const std::string Person::getQualification() const {}

void Person::setNIC(const std::string &) {}

const std::string Person::getNIC() const {}

void Person::setBFormNumber(const std::string &) {}

const std::string Person::getBFormNumber() const {}

void Person::print(){
	std::cout << "Name: " << getName() << ", Age: " << getAge() << ", Gender: " << getGender() << '\n';
}