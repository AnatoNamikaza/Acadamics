#include <iostream>
#include <fstream>
#include "Bogie.h"
using namespace std;

bool Bogie::compare(char* P1, char* P2){
	bool res= false;
	int size1=0,size2=0;
	for(int i=0;P1[i]!='\0';i++){
		size1++;
	}
	for(int i=0;P2[i]!='\0';i++){
		size2++;
	}
	if (size1 == size2) {
		for (int i = 0; i < size1; i++) {
			if (P1[i] == P2[i]) {
				res = true;
			} else {
				res = false;
				return res;
			}
		}
	}
	return res;
}

Bogie::Bogie() {
		this->Bogie_ID = 0;
		this->next = nullptr;
		this->Adults = nullptr;
		this->kids = nullptr;
		this->familyName = nullptr;
		this->MaxPassengersNo = 10;
		this->PassengersNo = 0;
		this->MaxAdultsNo = 4;
		this->AdultsNo = 0;
		this->MaxkidsNo = 6;
		this->kidsNo = 0;
	}

Bogie::Bogie(int id) {
		if (id != 0) {
			this->Bogie_ID = id;
		}
		this->next = nullptr;
		this->Adults = nullptr;
		this->kids = nullptr;
		this->familyName = nullptr;
		this->MaxPassengersNo = 10;
		this->PassengersNo = 0;
		this->MaxAdultsNo = 4;
		this->AdultsNo = 0;
		this->MaxkidsNo = 6;
		this->kidsNo = 0;
	}

void Bogie::BogieCopy(Bogie &B) {
		this->Bogie_ID = B.Bogie_ID;
		this->familyName = B.familyName;
		this->next = B.next;
		this->MaxPassengersNo = B.MaxPassengersNo;
		this->PassengersNo = B.PassengersNo;
		this->MaxAdultsNo = B.MaxAdultsNo;
		this->MaxkidsNo = B.MaxkidsNo;
		if (this->Adults == nullptr) {
			this->Adults = new Person *[B.AdultsNo];
		}
		else {
			for (int i = 0; i < AdultsNo; i++) {
				delete Adults[i];
				Adults[i] = nullptr;
			}
			delete Adults;
			Adults = nullptr;
			this->Adults = new Person *[B.AdultsNo];
		}

		for (int i = 0; i < B.AdultsNo; i++) {
			Adults[i] = new Adult();
		}

		for (int i = 0; i < B.AdultsNo; i++) {
			Adult *AdulTs = reinterpret_cast<Adult *>(Adults[i]);
			AdulTs->PAdultcopy(reinterpret_cast<Adult *>(B.Adults[i]));
		}

		if (this->kids == nullptr) {
			this->kids = new Person *[B.kidsNo];
		}
		else {
			for (int i = 0; i < this->kidsNo; i++) {
				delete kids[i];
				kids[i] = nullptr;
			}
			delete kids;
			kids = nullptr;
			this->kids = new Person *[B.kidsNo];
		}

		for (int i = 0; i < B.kidsNo; i++) {
			this->kids[i] = new kid();
		}

		for (int i = 0; i < B.kidsNo; i++) {
			kid *kiDs = reinterpret_cast<kid *>(this->kids[i]);
			kiDs->PKidcopy(reinterpret_cast<kid *>(B.kids[i]));
		}

		this->kidsNo = B.kidsNo;
		this->AdultsNo = B.AdultsNo;

	}

int Bogie::GetID() {
		return this->Bogie_ID;
	}

Bogie* Bogie::GetNext() {
		return this->next;
	}

Person* Bogie::GetkidsP(int i) {
	return this->kids[i];
}

Person* Bogie::GetAdultsP(int i) {
	return this->Adults[i];
}

char* Bogie::GetfamilyName() {
	return this->familyName;
}

int Bogie::GetPassengersNo() {
	return this->PassengersNo;
}

int Bogie::GetAdultsNo() {
	return this->AdultsNo;
}

int Bogie::GetkidsNo() {
	return this->kidsNo;
}

int Bogie::GetMaxPassengersNo() {
		return this->MaxPassengersNo;
	}

int Bogie::GetMaxAdultsNo() {
		return this->MaxAdultsNo;
	}

int Bogie::GetMaxkidsNo() {
		return this->MaxkidsNo;
	}

void Bogie::SetNext(Bogie *N) {
	this->next=N;
}

void Bogie::SetAdults(Person **A) {
	this->Adults=A;
}

void Bogie::Setkids(Person **K) {
	this->kids = K;
}

void Bogie::SetID(int x) {
		this->Bogie_ID = x;
	}

void Bogie::SetMaxPassengersNo(int x) {
		this->MaxPassengersNo = x;
	}

void Bogie::SetMaxAdultsNo(int x) {
		this->MaxAdultsNo = x;
	}

void Bogie::SetMaxkidsNo(int x) {
		this->MaxkidsNo = x;
	}

void Bogie::SetPassengersNo(int x) {
	this->PassengersNo = x;
}

void Bogie::SetAdultsNo(int x) {
	this->AdultsNo = x;
}

void Bogie::SetkidsNo(int x) {
	this->kidsNo = x;
}

void Bogie::SetfamilyName(const char *p) {
	int i=0;
	for(;p[i]!='\0';i++);
	i++;
	this->familyName=new char[i];
	for(int j=0;j<i;j++){
		familyName[j]=p[j];
	}
}

void Bogie::UpdateID() {
		cout << "Enter the New ID of the Bogie: ";
		int x;
		cin >> x;
		SetID(x);
	}

void Bogie::UpdateMaxPassengersNo() {
		cout << "Enter the New Capacity of the Bogie: ";
		int x;
		cin >> x;
		SetMaxPassengersNo(x);
	}

void Bogie::UpdateMaxAdultsNo() {
		cout << "Enter the New Adult Capacity of the Bogie: ";
		int x;
		cin >> x;
		SetMaxAdultsNo(x);
	}

void Bogie::UpdateMaxkidsNo() {
		cout << "Enter the New kids Capacity of the Bogie: ";
		int x;
		cin >> x;
		SetMaxkidsNo(x);
	}

void Bogie::UpdateBogieInfo(int Ax, int Ky, char *temp) {
		this->familyName = temp;

		this->Adults = new Person *[Ax];
		for (int i = 0; i < Ax; i++) {
			Adults[i] = new Adult();
		}

		for (int i = 0; i < Ax; i++) {
			cout << "Info of Adult #" << i + 1 << ": \n";
			Adult *AdulTs = reinterpret_cast<Adult *>(Adults[i]);
			AdulTs->UpdateInfo();
		}

		this->kids = new Person *[Ky];
		for (int i = 0; i < Ky; i++) {
			kids[i] = new kid();
		}

		for (int i = 0; i < Ky; i++) {
			cout << "Info of Kid #" << i + 1 << ": \n";
			kid *kiDs = reinterpret_cast<kid *>(kids[i]);
			kiDs->UpdateInfo();
		}

	}

bool Bogie::AddPassengers() {
	system("CLS");
	int FC;
	int Result = 0;

	cout << "Is there a Family in the Bogie? \n";
	cout << "1.Yes, there is a Family. \n";
	cout << "2.No, there is no Family. \n";
	cout << "Enter Choice: ";

	while (true) {
		cin >> FC;
		system("CLS");

		if (FC == 1) {
			int RC;
			cout << "Does the Family want to reserve the Bogie? \n";
			cout << "1.Yes, they want to reserve. \n";
			cout << "2.No, they don't want to reserve. \n";
			cout << "Enter Choice: ";

			while (true) {
				cin >> RC;
				system("CLS");

				if (RC == 1) {
					cout << "Enter the Total no. of Members in Family: ";

					while (true) {
						cin >> this->PassengersNo;
						system("CLS");

						if (this->PassengersNo == 0) {
							return Result;
						}
						else if (this->PassengersNo < this->MaxPassengersNo) {
							cout << "Enter the Total no. of Adults in Family: ";

							while (true) {
								cin >> this->AdultsNo;
								system("CLS");

								if (this->AdultsNo > this->PassengersNo) {
									cout << "Exceeding the Available Space. \n";
									cout << "Enter Correct number: ";
								}
								else if (this->AdultsNo < this->MaxAdultsNo) {
									cout << "Enter the Total no. of kids in Family: ";

									while (true) {
										cin >> this->kidsNo;
										system("CLS");

										if (this->kidsNo + this->AdultsNo > this->PassengersNo) {
											cout << "Exceeding the Available Space. \n";
											cout << "Enter Correct number: ";
										}
										else if (this->kidsNo < this->MaxkidsNo) {
											char *famName;
											famName = new char[30];
											cout << "Enter the name of Family: ";
											cin.ignore(1, '\n');
											cin.clear();
											cin.getline(famName, 15, '\n');

											UpdateBogieInfo(this->AdultsNo, this->kidsNo, famName);
											Result = 1;
											cout << "Passengers have been added." << endl;
											break;
										}
										else {
											cout << "Exceeding the Available Space. \n";
											cout << "Enter Correct number: ";
										}
									}
									break;
								}
								else {
									cout << "Exceeding the Available Space. \n";
									cout << "Enter Correct number: ";
								}
							}
							break;
						}
						else {
							cout << "Exceeding the Available Space. \n";
							cout << "Enter Correct number: ";
						}
					}
					break;
				}
				else if (RC == 2) {
					cout << "Enter the Total no. of Passengers in Bogie: ";

					while (true) {
						cin >> this->PassengersNo;
						system("CLS");

						if (this->PassengersNo == 0) {
							return Result;
						}
						else if (this->PassengersNo < this->MaxPassengersNo) {
							cout << "Enter the Total no. of Adults in Bogie: ";

							while (true) {
								cin >> this->AdultsNo;
								system("CLS");

								if (this->AdultsNo > this->PassengersNo) {
									cout << "Exceeding the Available Space. \n";
									cout << "Enter Correct number: ";
								}
								else if (this->AdultsNo < this->MaxAdultsNo) {
									cout << "Enter the Total no. of kids in Bogie: ";

									while (true) {
										cin >> this->kidsNo;
										system("CLS");

										if (this->kidsNo + this->AdultsNo > this->PassengersNo) {
											cout << "Exceeding the Available Space. \n";
											cout << "Enter Correct number: ";
										}
										else if (this->kidsNo < this->MaxkidsNo) {
											char *famName;
											cin.ignore(1, '\n');
											cin.clear();
											famName = nullptr;
											UpdateBogieInfo(this->AdultsNo, this->kidsNo, famName);
											Result = 1;
											cout << "Passengers have been added." << endl;
											break;
										}
										else {
											cout << "Exceeding the Available Space. \n";
											cout << "Enter Correct number: ";
										}
									}
									break;
								}
								else {
									cout << "Exceeding the Available Space. \n";
									cout << "Enter Correct number: ";
								}
							}
							break;
						}
						else {
							cout << "Exceeding the Available Space. \n";
							cout << "Enter Correct number: ";
						}
					}
					break;
				}
				else {
					cout << "Option unavailable \n";
					cout << "Enter Correct Choice: \n";
				}
			}
			break;
		}
		else if (FC == 2) {
			cout << "Enter the Total no. of Passengers in Bogie: ";

			while (true) {
				cin >> this->PassengersNo;
				system("CLS");

				if (this->PassengersNo == 0) {
					return Result;
				}
				else if (this->PassengersNo < this->MaxPassengersNo) {
					cout << "Enter the Total no. of Adults in Bogie: ";

					while (true) {
						cin >> this->AdultsNo;
						system("CLS");

						if (this->AdultsNo > this->PassengersNo) {
							cout << "Exceeding the Available Space. \n";
							cout << "Enter Correct number: ";
						}
						else if (this->AdultsNo < this->MaxAdultsNo) {
							cout << "Enter the Total no. of kids in Bogie: ";

							while (true) {
								cin >> this->kidsNo;
								system("CLS");

								if (this->kidsNo + this->AdultsNo > this->PassengersNo) {
									cout << "Exceeding the Available Space. \n";
									cout << "Enter Correct number: ";
								}
								else if (this->kidsNo < this->MaxkidsNo) {
									char *famName;
									cin.ignore(1, '\n');
									cin.clear();
									famName = nullptr;
									UpdateBogieInfo(this->AdultsNo, this->kidsNo, famName);
									Result = 1;
									cout << "Passengers have been added." << endl;
									break;
								}
								else {
									cout << "Exceeding the Available Space. \n";
									cout << "Enter Correct number: ";
								}
							}
							break;
						}
						else {
							cout << "Exceeding the Available Space. \n";
							cout << "Enter Correct number: ";
						}
					}
					break;
				}
				else {
					cout << "Exceeding the Available Space. \n";
					cout << "Enter Correct number: ";
				}
			}
			break;
		}
		else {
			cout << "Option unavailable \n";
			cout << "Enter Correct Choice: \n";
		}
	}

	return 0;
}

void Bogie::AddNewPassengers() {
	system("CLS");
	int FC;

	if(this->familyName!= nullptr) {
		FC=1;
	}else {
		FC=2;
	}

	while (true) {
		system("CLS");

		if (FC == 1) {
			int RC;
			cout << "Will the Family allow New Passengers in the Bogie? \n";
			cout << "1.Yes, they will allow. \n";
			cout << "2.No, they will not allow. \n";
			cout << "Enter Choice: ";

			while (true) {
				cin >> RC;
				system("CLS");

				if (RC == 1) {
					int k = 0;
					cout << "Is the New Passanger an Adult or a Kid:- \n";
					cout << "1. Adult || 2. Kid:- \n";
					cin >> k;
					if (k == 1) {
						Adult *TempAdult;
						TempAdult = new Adult[this->AdultsNo + 1];
						for (int i = 0; i < this->AdultsNo; i++) {
							TempAdult[i].PAdultcopy(dynamic_cast<Adult *>(Adults[i]));
						}
						TempAdult[this->AdultsNo].UpdateInfo();
						for (int i = 0; i < AdultsNo; i++) {
							delete Adults[i];
							Adults[i] = nullptr;
						}
						delete Adults;
						this->Adults = new Person *[this->AdultsNo + 1];
						for (int i = 0; i < this->AdultsNo + 1; i++) {
							Adults[i] = new Adult();
						}

						for (int i = 0; i < this->AdultsNo + 1; i++) {
							Adult *AdulTs = reinterpret_cast<Adult *>(Adults[i]);
							AdulTs->Adultcopy(TempAdult[i]);
						}
						AdultsNo++;

						delete[] TempAdult;
						break;
					} else if (k == 2) {
						kid *TempKID;
						TempKID = new kid[this->kidsNo + 1];
						for (int i = 0; i < this->kidsNo; i++) {
							TempKID[i].PKidcopy(dynamic_cast<kid *>(kids[i]));
						}
						TempKID[this->kidsNo].UpdateInfo();
						for (int i = 0; i < kidsNo; i++) {
							delete kids[i];
							kids[i] = nullptr;
						}
						delete kids;
						this->kids = new Person *[this->kidsNo + 1];
						for (int i = 0; i < this->kidsNo + 1; i++) {
							kids[i] = new kid();
						}

						for (int i = 0; i < this->kidsNo + 1; i++) {
							kid *kiDs = reinterpret_cast<kid *>(kids[i]);
							kiDs->Kidcopy(TempKID[i]);
						}
						kidsNo++;

						delete[] TempKID;
						break;
					} else {
						cout << "Option Unavailable. \n";
					}
				}
				if (RC == 2) {
					cout << "Permission not granted by Family.\n";
					cout << "Passangers can not be added.\n";
					break;
				} else {
					cout << "Option unavailable \n";
					cout << "Enter Correct Choice: \n";
				}
			}
			break;
		} else if (FC == 2) {
			int k = 0;
			cout << "Is the New Passanger an Adult or a Kid:- \n";
			cout << "1. Adult || 2. Kid:- \n";
			cin >> k;
			if (k == 1) {
				Adult *TempAdult;
				TempAdult = new Adult[this->AdultsNo + 1];
				for (int i = 0; i < this->AdultsNo; i++) {
					TempAdult[i].PAdultcopy(dynamic_cast<Adult *>(Adults[i]));
				}
				TempAdult[this->AdultsNo].UpdateInfo();
				for (int i = 0; i < AdultsNo; i++) {
					delete Adults[i];
					Adults[i] = nullptr;
				}
				delete Adults;
				this->Adults = new Person *[this->AdultsNo + 1];
				for (int i = 0; i < this->AdultsNo + 1; i++) {
					Adults[i] = new Adult();
				}

				for (int i = 0; i < this->AdultsNo + 1; i++) {
					Adult *AdulTs = reinterpret_cast<Adult *>(Adults[i]);
					AdulTs->Adultcopy(TempAdult[i]);
				}
				AdultsNo++;

				delete[] TempAdult;
				break;
			} else if (k == 2) {
				kid *TempKID;
				TempKID = new kid[this->kidsNo + 1];
				for (int i = 0; i < this->kidsNo; i++) {
					TempKID[i].PKidcopy(dynamic_cast<kid *>(kids[i]));
				}
				TempKID[this->kidsNo].UpdateInfo();
				for (int i = 0; i < kidsNo; i++) {
					delete kids[i];
					kids[i] = nullptr;
				}
				delete kids;
				this->kids = new Person *[this->kidsNo + 1];
				for (int i = 0; i < this->kidsNo + 1; i++) {
					kids[i] = new kid();
				}

				for (int i = 0; i < this->kidsNo + 1; i++) {
					kid *kiDs = reinterpret_cast<kid *>(kids[i]);
					kiDs->Kidcopy(TempKID[i]);
				}
				kidsNo++;

				delete[] TempKID;
				break;
			} else {
				cout << "Option Unavailable. \n";
			}
			break;
		}else {
			cout << "Option unavailable \n";
			cout << "Enter Correct Choice: \n";
		}
	}
}

void Bogie::RemovePassengers() {
	system("CLS");
	char Name[30]{0};
	char NIC[30]{0};
	int c1 = 0, c2 = 0;

	cout << "Enter Passanger's Name:- \n";
	cin.getline(Name, 30, '\n');
	cout << "Enter Passanger's NIC:- \n";
	cin.getline(NIC, 20, '\n');
	int k = 0;
	cout << "Is the New Passanger an Adult or a Kid:- \n";
	cout << "1. Adult || 2. Kid:- \n";
	cin >> k;
	if (k == 1) {
		Adult *TempAdult;
		TempAdult = new Adult[this->AdultsNo];
		for (int i = 0; i < this->AdultsNo; i++) {
			TempAdult[i].PAdultcopy(dynamic_cast<Adult *>(Adults[i]));
		}

		for (int i = 0; i < this->AdultsNo; i++) {
			if (compare(TempAdult[i].GetName(), Name) && compare(TempAdult[i].GetNIC(), NIC)) {
				if (i != AdultsNo - 1) {
					for (int j = i; j < AdultsNo - 1; j++) {
						TempAdult[j].Adultcopy(TempAdult[j + 1]);
					}
					c1++;
					break;
				} else if (i == AdultsNo - 1) {
					c2++;
				}
			}
		}

		for (int i = 0; i < AdultsNo; i++) {
			delete Adults[i];
			Adults[i] = nullptr;
		}
		delete Adults;

		if (c1 == 1) {
			AdultsNo--;
			this->Adults = new Person *[this->AdultsNo];
			for (int i = 0; i < this->AdultsNo; i++) {
				Adults[i] = new Adult();
			}

			for (int i = 0; i < this->AdultsNo; i++) {
				Adult *AdulTs = reinterpret_cast<Adult *>(Adults[i]);
				AdulTs->Adultcopy(TempAdult[i]);
			}
		}

		if (c2 == 1) {
			AdultsNo--;
			this->Adults = new Person *[this->AdultsNo];
			for (int i = 0; i < this->AdultsNo; i++) {
				Adults[i] = new Adult();
			}

			for (int i = 0; i < this->AdultsNo; i++) {
				Adult *AdulTs = reinterpret_cast<Adult *>(Adults[i]);
				AdulTs->Adultcopy(TempAdult[i]);
			}
		}
		delete[] TempAdult;
	} else if (k == 2) {
		kid *TempKID;
		TempKID = new kid[this->kidsNo];
		for (int i = 0; i < this->kidsNo; i++) {
			TempKID[i].PKidcopy(dynamic_cast<kid *>(kids[i]));
		}

		for (int i = 0; i < this->kidsNo; i++) {
			if (compare(TempKID[i].GetName(), Name) && compare(TempKID[i].GetB_form_number(), NIC)) {
				if (i != kidsNo - 1) {
					for (int j = i; j < AdultsNo - 1; j++) {
						TempKID[j].Kidcopy(TempKID[j + 1]);
					}
					c1++;
					break;
				} else if (i == AdultsNo - 1) {
					c2++;
				}
			}
		}

		for (int i = 0; i < kidsNo; i++) {
			delete kids[i];
			kids[i] = nullptr;
		}
		delete kids;

		if (c1 == 1) {
			kidsNo--;
			this->kids = new Person *[this->kidsNo];
			for (int i = 0; i < this->kidsNo; i++) {
				kids[i] = new kid();
			}

			for (int i = 0; i < this->kidsNo; i++) {
				kid *kiDs = reinterpret_cast<kid *>(kids[i]);
				kiDs->Kidcopy(TempKID[i]);
			}
		}

		if (c2 == 1) {
			kidsNo--;
			this->kids = new Person *[this->kidsNo];
			for (int i = 0; i < this->kidsNo; i++) {
				kids[i] = new kid();
			}

			for (int i = 0; i < this->kidsNo; i++) {
				kid *kiDs = reinterpret_cast<kid *>(kids[i]);
				kiDs->Kidcopy(TempKID[i]);
			}
			delete[] TempKID;
		} else {
			cout << "Option Unavailable. \n";
		}

	}
}

void Bogie::Print() {
		cout << "(Bogie ID: " << this->Bogie_ID << ") \n";
		cout << "(Next: " << this->GetNext() << ") \n";
		cout << "(Total Passangers: " << this->PassengersNo << ") \n";
		if (this->familyName != nullptr) {
			cout << "(FamilyName: " << this->familyName << ") \n";
		}
		cout << "List of All Kids present in the Bogie: " << endl;
		cout << "_____________________________________" << endl;
		if (this->kidsNo == 0) {
			cout << endl;
			cout << ".........................................................................................."
				<< endl;
			cout << "No kids found in the Bogie." << endl;
			cout << ".........................................................................................."
				<< endl;
			cout << endl;

		}

		for (int i = 0; i < this->kidsNo; i++) {
			kid *kiDs = reinterpret_cast<kid *>(kids[i]);	cout << endl;
			cout << ".........................................................................................."
				<< endl;
			kiDs->printData();
			cout << ".........................................................................................."
				<< endl;
			cout << endl;
		}

		cout << "List of All Adults present in the Bogie: " << endl;
		cout << "_______________________________________" << endl;
		if (this->AdultsNo == 0) {
			cout << endl;
			cout << ".........................................................................................."
				<< endl;
			cout << "No Adults found in the Bogie." << endl;
			cout << ".........................................................................................."
				<< endl;
			cout << endl;

		}

		for (int i = 0; i < this->AdultsNo; i++) {
			Adult *AdulTs = reinterpret_cast<Adult *>(Adults[i]);cout << endl;
			cout << ".........................................................................................."
				<< endl;
			AdulTs->printData();
			cout << ".........................................................................................."
				<< endl;
			cout << endl;
		}
	}

Bogie::~Bogie() {
		Bogie_ID = 0;
		if (this->Adults != nullptr) {
			for (int i = 0; i < AdultsNo; i++) {
				delete Adults[i];
				Adults[i] = nullptr;
			}
			delete Adults;
			Adults = nullptr;
		}

		if (this->kids != nullptr) {
			for (int i = 0; i < kidsNo; i++) {
				delete kids[i];
				kids[i] = nullptr;
			}
			delete kids;
			kids = nullptr;
		}

		familyName = nullptr;

		MaxPassengersNo = 0;
		PassengersNo = 0;
		MaxAdultsNo = 0;
		AdultsNo = 0;
		MaxkidsNo = 0;
		kidsNo = 0;
		next = nullptr;

	}