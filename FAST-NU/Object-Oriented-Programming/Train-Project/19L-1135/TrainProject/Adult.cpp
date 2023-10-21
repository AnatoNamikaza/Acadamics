
#include "Adult.h"

Adult::Adult() : Occupation(""), Qualification(""), NIC(""), Person() {}

Adult::Adult(const std::string &name, int a, char g, const std::string &o, const std::string &q, const std::string &nic)
			: Person(name, a, g){

	Occupation.assign(o), Qualification.assign(q), NIC.assign(nic);
}

Adult::Adult(const Adult &a) {
	Occupation.assign(a.Occupation);
	Qualification.assign(a.Qualification);
	NIC.assign(a.NIC);
	setGender(a.getGender());
	setAge(a.getAge());
	setName(a.getName());
}

void Adult::setOccupation(const std::string &o) {
	Occupation.assign(o);
}

const std::string Adult::getOccupation() const {
	return Occupation;
}

void Adult::setQualification(const std::string &q) {
	Qualification.assign(q);
}

const std::string Adult::getQualification() const {
	return Qualification;
}

void Adult::setNIC(const std::string &n) {
	NIC.assign(n);
}

const std::string Adult::getNIC() const {
	return NIC;
}

void Adult::print(){

	std::cout << "Adult Name: " << getName() << ", Age: " << getAge() << ", Gender: " << getGender()
	<< 	", Occupation: " << getOccupation() << ", Qualification: " << getQualification() << ", NIC: "
	<< getQualification() << '\n';

}