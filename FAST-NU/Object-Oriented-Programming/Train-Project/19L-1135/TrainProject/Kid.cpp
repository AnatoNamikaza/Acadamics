
#include "Kid.h"

Kid::Kid() : B_form_number(""), Person() {}

Kid::Kid(const std::string &name, int a, char g, const std::string &bfn) : Person(name, a, g) {
	B_form_number.assign(bfn);
}

Kid::Kid(const Kid &k) {
	setGender(k.getAge());
	setAge(k.getAge());
	setName(k.getName());
	B_form_number.assign(k.getBFormNumber());
}

void Kid::setBFormNumber(const std::string &bfn) {
	B_form_number.assign(bfn);
}

const std::string Kid::getBFormNumber() const {
	return B_form_number;
}

void Kid::print(){

	std::cout << "Kid Name: " << getName() << ", Age: " << getAge() << ", Gender: " << getGender()
	<< ", BForm Number: " << getBFormNumber() << '\n';

}
