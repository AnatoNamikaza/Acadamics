#include <iostream>
#include "AVLNode.h"
using namespace std;


template<class type>
class AVL {
private:
	AVLNode<type>* root;
public:
	AVL() {
		root = nullptr;
	}

	AVL(AVL& obj) {
		this->root = new AVLNode<type>;
		DeepCopy(this->root, obj.root);
	}

	void operator=(AVL& obj) {
		this->root = new AVLNode<type>;
		DeepCopy(this->root, obj.root);
	}

	void insert_recursuve(type*& data) {
		if (root == nullptr) {
			root = new AVLNode<type>;
			root->data = data;
		}
		else if (root != nullptr) {
			AVLNode<type>*& temp = this->root;
			insert_R(data, temp);
		}
	}

	void insert_R(type*& data, AVLNode<type>*& temp) {
		if (*temp->data < data) {
			if (temp->right == nullptr) {
				temp->right = new AVLNode<type>;
				temp->right->data = data;
			}
			else if (temp->right != nullptr) {
				insert_R(data, temp->right);
			}
		}
		else if (*temp->data > data) {
			if (temp->left == nullptr) {
				temp->left = new AVLNode<type>;
				temp->left->data = data;
			}
			else if (temp->left != nullptr) {
				insert_R(data, temp->left);
			}
		}
		else if (*temp->data == data) {
			temp->data->Merge(data);
		}

		BalanceAVL(temp);
	}

	AVLNode<type>* SearchAddress(string data, AVLNode<type>*temp) {
		if (*temp->data == data) {
			return temp;
		}
		else if (*temp->data > data && temp->left != nullptr) {
			return SearchAddress(data, temp->left);
		}
		else if (*temp->data < data && temp->right != nullptr) {
			return SearchAddress(data, temp->right);
		}
		return nullptr;
	}

	int heightsetter(AVLNode<type>* x) {
		if (x == nullptr) {
			return -1;
		}
		else if (x->left == nullptr && x->right == nullptr) {
			x->height = 0;
			return 0;
		}
		else {
			if (heightsetter(x->left) >= heightsetter(x->right)) {
				x->height = 1 + heightsetter(x->left);
				return x->height;
			}
			else {
				x->height = 1 + heightsetter(x->right);
				return x->height;
			}
		}
	}

	void BalanceAVL(AVLNode<type>*& temp) {
		if (temp == nullptr)
			return;

		if (heightsetter(temp->right) - heightsetter(temp->left) < -1) {
			if (heightsetter(temp->left->left) >= heightsetter(temp->left->right))
				rightRotate(temp);
			else
				leftRightRotate(temp);
		}
		else if (heightsetter(temp->right) - heightsetter(temp->left) > 1) {
			if (heightsetter(temp->right->right) >= heightsetter(temp->right->left))
				leftRotate(temp);
			else
				rightLeftRotate(temp);
		}

		temp->height = heightsetter(temp);
	}

	void rightRotate(AVLNode<type>*& x) {
		AVLNode<type>* orphan = x->left->right;
		AVLNode<type>* ptr = x->left;
		ptr->right = x;
		x->left = orphan;

		x->height = heightsetter(x);
		ptr->height = heightsetter(ptr);

		x = ptr;
	}

	void leftRotate(AVLNode<type>*& x) {
		AVLNode<type>* orphan = x->right->left;
		AVLNode<type>* ptr = x->right;
		ptr->left = x;
		x->right = orphan;

		x->height = heightsetter(x);
		ptr->height = heightsetter(ptr);

		x = ptr;
	}

	void leftRightRotate(AVLNode<type>*& x) {
		leftRotate(x->left);
		rightRotate(x);
	}

	void rightLeftRotate(AVLNode<type>*& x) {
		rightRotate(x->right);
		leftRotate(x);
	}

	bool search_recursuve(type* data) {
		if (root == nullptr) {
			return 0;
		}
		else if (root != nullptr) {
			AVLNode<type>* temp = new AVLNode<type>;
			temp = this->root;
			return search_R(data, temp);
		}
	}

	bool search_R(type* data, AVLNode<type>* root = nullptr) {
		if (root != nullptr && data == root->data) {
			return true;
		}
		else if (root != nullptr && data > root->data) {
			if (root->right == nullptr) {
				return false;
			}
			else if (root->right != nullptr) {
				return search_R(data, root->right);
			}
		}
		else if (root != nullptr && data < root->data) {
			if (root->left == nullptr) {
				return false;
			}
			else if (root->left != nullptr) {
				return search_R(data, root->left);
			}
		}
	}

	AVLNode<type>* GetRoot() { return this->root; }

	AVLNode<type>& GetRootAddress() { return &this->root; }

	void DeepCopy(AVLNode<type>* temp1, AVLNode<type>* temp2) {
		temp1->data = temp2->data;
		temp1->height = temp2->height;
		if (temp2->left != nullptr) {
			temp1->left = new AVLNode<type>;
			DeepCopy(temp1->left, temp2->left);
		}
		if (temp2->right != nullptr) {
			temp1->right = new AVLNode<type>;
			DeepCopy(temp1->right, temp2->right);
		}
	}

	void treeinsertion(AVLNode<type>* temp, type* data) {
		AVLNode<type>* start = SearchAddress(data, temp);
		this->root = new AVLNode<type>;
		DeepCopy(this->root, start);
	}

	AVL get_AVL(type* data) {
		AVL NewTree;
		NewTree.treeinsertion(root, data);

		return NewTree;
	}

	void Print() {
		PrintAllAVLNodes(this->root);
	}

	void PrintAllAVLNodes(AVLNode<type>* temp) {
		if (temp->left != nullptr) {
			PrintAllAVLNodes(temp->left);
		}
		cout << "AVLNode: ";
		temp->Print();
		cout << "_______________\n";
		if (temp->right != nullptr) {
			PrintAllAVLNodes(temp->right);
		}
	}

	void DeleteAVLNodes(AVLNode<type>* temp) {
		if (temp->left != nullptr) {
			DeleteAVLNodes(temp->left);
		}
		if (temp->right != nullptr) {
			DeleteAVLNodes(temp->right);
		}
		AVLNode<type>* Del = temp;
		temp = nullptr;
		delete Del;
		Del = nullptr;
	}

	~AVL() {
		if (root != nullptr) {
			AVLNode<type>* Del = root;
			root = nullptr;
			DeleteAVLNodes(Del);
		}
	}
};
	