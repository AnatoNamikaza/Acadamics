
#ifndef TRAINPROJECT_ADULT_H
#define TRAINPROJECT_ADULT_H

#include "Person.h"

class Adult : public Person {
	std::string Occupation;
	std::string Qualification;
	std::string NIC;

public:

	Adult();

	Adult(const std::string &, int, char, const std::string &, const std::string &, const std::string &);

	Adult(const Adult &);

	void setOccupation(const std::string &) override;

	const std::string getOccupation() const override ;

	void setQualification(const std::string &) override ;

	const std::string getQualification() const override;

	void setNIC(const std::string &) override;

	const std::string getNIC() const override;

	void print() override;
};


#endif
