#pragma once
#include "Person.h"

class kid :public Person {
private:
	char *B_form_number;
public:
	kid();
	kid(const char *name, int age, const char *gender, const char *BFNUM);
	void Kidcopy(kid &p);
	void PKidcopy(kid *p);
	char *GetB_form_number();
	void SetB_form_number(const char *BFNUM);
	void SetInfo(char *name, int age, char *gender, char *BFNUM);
	void UpdateB_form_number();
	void UpdateInfo()override;
	void printData()override;
	virtual ~kid();
};
