
#ifndef TRAINPROJECT_KID_H
#define TRAINPROJECT_KID_H

#include "Person.h"

class Kid : public Person {
	std::string B_form_number;
public:
	Kid();

	Kid(const std::string &, int, char, const std::string &);

	Kid(const Kid &);

	void setBFormNumber(const std::string &) override;

	const std::string getBFormNumber() const override;

	void print() override;
};


#endif
