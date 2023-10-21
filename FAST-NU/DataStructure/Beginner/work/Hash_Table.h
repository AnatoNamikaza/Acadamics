#pragma once
#include "DList.h"

template <class type>
struct HashItem {

	int key; short status; type value; 

	HashItem() { key = 0, status = 0; }

	type* GetValue() { return &value; }
};

template <class type>
struct HashList {
	HashItem<type> Item;
	DList<HashItem<type>>  List;
};

template <class type>
class HashMap {

private:

	//Private Member Variables
	int capacity, currentElements;
	HashList<type>* ListTable;

	//Private Member Function
	void doubleCapacity() {
		this->capacity *= 2;
		int ind = 0;
		HashList<type>* temp = new HashList<type>[capacity];
		for (int i = 0; i < (capacity / 2); i++) {
			if (ListTable[i].Item.status != 0) {
				ind = ListTable[i].Item.key % capacity;
				if (temp[ind].Item.status == 0 || temp[ind].Item.status == 2) {
					temp[ind].Item.key = ListTable[i].Item.key;
					temp[ind].Item.status = 1;
					temp[ind].Item.value = ListTable[i].Item.value;
				}
				else {
					Node<HashItem<type>> NewData;
					NewData.Data.key = ListTable[i].Item.key;
					NewData.Data.status = 1;
					NewData.Data.value = ListTable[i].Item.value;
					temp[ind].List.insertNodeAtEnd(&NewData);
				}
			}
			else if (ListTable[i].List.GetHead()->Getnext() != ListTable[i].List.GetTail()) {
				Node<HashItem<type>>* tempL = ListTable[i].List.GetHead()->Getnext();
				for (; tempL != ListTable[i].List.GetTail(); tempL = tempL->Getnext()) {
					ind = this->ListTable[i].Item.key % capacity;
					if (temp[ind].Item.status == 0 || temp[ind].Item.status == 2) {
						temp[ind].Item.key = tempL->Data.key;
						temp[ind].Item.status = 1;
						temp[ind].Item.value = tempL->Data.value;
					}
					else {
						Node<HashItem<type>> NewData;
						NewData.Data.key = tempL->Data.key;;
						NewData.Data.status = 1;
						NewData.Data.value = tempL->Data.value;
						temp[ind].List.insertNodeAtEnd(&NewData);
					}
				}
				tempL = nullptr;
			}
		}
		delete[] this->ListTable, this->ListTable = temp, temp = nullptr;
	}

public:

	HashMap() {
		this->capacity = 10, this->currentElements = 0;
		ListTable = new HashList<type>[10];
	}

	void insert(int const key, type const value) {
		int index = key % capacity;
		if (ListTable[index].Item.status == 0 || ListTable[index].Item.status == 2) {
			ListTable[index].Item.key = key;
			ListTable[index].Item.status = 1;
			ListTable[index].Item.value = value;
		}
		else {
			Node<HashItem<type>> NewData;
			NewData.Data.key = key;
			NewData.Data.status = 1;
			NewData.Data.value = value;
			ListTable[index].List.insertNodeAtEnd(&NewData);
		}
		currentElements++;
		double d = static_cast<double>(currentElements) / capacity;
		if (d >= 2)
			doubleCapacity();
	}

	bool deleteKey(int const key) {
		int index = key % capacity;
		while (index < capacity)
			if (ListTable[index].Item.status == 1 && ListTable[index].Item.key == key) {
				ListTable[index].Item.status = 2, this->currentElements -= 1;
				return true;
			}
			else if (ListTable[index].List.GetHead()->Getnext() != ListTable[index].List.GetTail()) {
				Node<HashItem<type>>* tempL = ListTable[index].List.GetHead()->Getnext();
				for (; tempL != ListTable[index].List.GetTail(); tempL = tempL->Getnext()) {
					if (tempL->Data.status == 1 && tempL->Data.key == key) {
						tempL->Data.status = 2, this->currentElements -= 1;
						tempL = nullptr;
						return true;
					}
				}
			}
			else
				return false;
	}

	//type* SearchItem(int const key, type *value) {
	//	for (int i = 0; i < capacity; i++) {
	//		if (ListTable[i].Item.key == key &&
	//			ListTable[i].Item.value.Compare(value) &&
	//			ListTable[i].Item.status == 1) {
	//			return ListTable[i].Item.GetValue();
	//		}
	//		if (ListTable[i].List.GetHead()->Getnext() != ListTable[i].List.GetTail()) {
	//			Node<HashItem<type>>* tempL = ListTable[i].List.GetHead()->Getnext();
	//			for (; tempL != ListTable[i].List.GetTail(); tempL = tempL->Getnext()) {
	//				if (tempL->Data.status == 1 && tempL->Data.key == key && tempL->Data.value.Compare(value)) {
	//					return tempL->Data.GetValue();
	//				}
	//			}
	//		}
	//	}
	//	return nullptr;
	//}

	void Print() {
		for (int i = 0; i < capacity; i++) {
			if (ListTable[i].Item.status != 0) {
				std::cout << "HashItem#" << i + 1 << ":- key: " << ListTable[i].Item.key << ",Status: "
					<< ListTable[i].Item.status << "\n";
				ListTable[i].Item.value.print();
			}
			if (ListTable[i].List.GetHead()->Getnext() != ListTable[i].List.GetTail()) {
				std::cout << "HashItem's List:\n";
				Node<HashItem<type>>* tempL = ListTable[i].List.GetHead()->Getnext();
				for (; tempL != ListTable[i].List.GetTail(); tempL = tempL->Getnext()) {
					std::cout << "Status: " << tempL->Data.status << ",key: " << tempL->Data.key << "\n";
					tempL->Data.value.print();
				}
			}
		}
		std::cout << std::endl;
	}

	int GetCE() { return currentElements; }

	~HashMap() {
		this->capacity = 0;
		this->currentElements = 0;
	}
};