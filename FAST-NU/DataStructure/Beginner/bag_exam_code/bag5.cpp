// FILE: bag5.template
// -------------------------------------------------------------------------
// This is a partial implementation of the bag template class from Section
// 10.5 of "Data Structures and Other Objects Using C++". The parts marked
// with ***STUDENT WORK*** are left as a project for data structures
// students. Some additional discussion of this project is available at
// http://www-cs.engr.ccny.cuny.edu/~wolberg/cs212/hw/hw5.html
// -------------------------------------------------------------------------
// TEMPLATE CLASS IMPLEMENTED: bag<Item> (see bag5.h for documentation)
// INVARIANT of the ADT:
//   root_ptr is the root pointer of a binary search tree that contains the
//   bag's items.

#include <cassert>
#include <cstdlib>
#include "bag5.h"

namespace main_savitch_10
{
	//Updated Function by student
	template <class Item>
	void bst_remove_max(binary_tree_node<Item>*& root_ptr, Item& removed)
		// Precondition: root_ptr is a root pointer of a non-empty binary 
		// search tree.
		// Postcondition: The largest item in the binary search tree has been
		// removed, and root_ptr now points to the root of the new (smaller) 
		// binary search tree. The reference parameter, removed, has been set 
		// to a copy of the removed item.
	{
		bst_removed_max(root_ptr, removed);
	}

	//---------student Defined function---------
	template <class Item>
	void bst_removed_max(binary_tree_node<Item>*& root_ptr, Item& removed)
	{
		if (root_ptr->right() != nullptr)
			bst_removed_max(root_ptr->right(), removed);
		else if (root_ptr->right() == nullptr) {
			removed = root_ptr->data();
			binary_tree_node<Item>* Del_Node = root_ptr;
			root_ptr = root_ptr->left();
			delete Del_Node; Del_Node = nullptr;
		}
	}

	template <class Item>
	bool bst_remove(binary_tree_node<Item>*& root_ptr, const Item& target)
		// Precondition: root_ptr is a root pointer of a binary search tree 
		// or may be NULL for an empty tree).
		// Postcondition: If target was in the tree, then one copy of target
		// has been removed, and root_ptr now points to the root of the new 
		// (smaller) binary search tree. In this case the function returns true.
		// If target was not in the tree, then the tree is unchanged (and the
		// function returns false).
	{
		binary_tree_node<Item>* oldroot_ptr;

		if (root_ptr == NULL)
		{   // Empty tree
			return false;
		}

		if (target < root_ptr->data())
		{   // Continue looking in the left subtree
		// Note: Any change made to root_ptr->left by this recursive
		// call will change the actual left pointer (because the return
		// value from the left() member function is a reference to the
		// actual left pointer.
			return bst_remove(root_ptr->left(), target);
		}

		if (target > root_ptr->data())
		{   // Continue looking in the right subtree
		// Note: Any change made to root_ptr->right by this recursive
		// call will change the actual right pointer (because the return
		// value from the right() member function is a reference to the
		// actual right pointer.
			return bst_remove(root_ptr->right(), target);
		}

		if (root_ptr->left() == NULL)
		{   // Target was found and there is no left subtree, so we can
		// remove this node, making the right child be the new root.
			oldroot_ptr = root_ptr;
			root_ptr = root_ptr->right();
			delete oldroot_ptr;
			return true;
		}

		// If code reaches this point, then we must remove the target from
		// the current node. We'll actually replace this target with the
		// maximum item in our left subtree.
		// Note: Any change made to root_ptr->left by bst_remove_max
		// will change the actual left pointer (because the return
		// value from the left() member function is a reference to the
		// actual left pointer.
		bst_remove_max(root_ptr->left(), root_ptr->data());
		return true;
	}

	//Updated Function by student
	template <class Item>
	typename bag<Item>::size_type bst_remove_all
	(binary_tree_node<Item>*& root_ptr, const Item& target)
		// Precondition: root_ptr is a root pointer of a binary search tree 
		// or may be NULL for an empty tree).
		// Postcondition: All copies of target have been removed from the tree
		// has been removed, and root_ptr now points to the root of the new 
		// (smaller) binary search tree. The return value tells how many copies
		// of the target were removed.
	{
		/** STUDENT WORK
		 ** Note: This implementation is similar to bst_remove, except that
		 ** all occurrences of the target must be removed, and the return
		 ** value is the number of copies that were removed.
		 */

		binary_tree_node<Item>* oldroot_ptr;

		if (root_ptr == NULL)
		{
			return 0;
		}

		if (target < root_ptr->data())
		{
			int occurtime = bst_remove_all(root_ptr->left(), target);
		Label_1:
			if (bst_remove_all(root_ptr->left(), target) == 1) {
				occurtime++;
				goto Label_1;
			}
			else
				return occurtime;
		}

		if (target > root_ptr->data())
		{
			int occurtime = bst_remove_all(root_ptr->right(), target);
		Label_2:
			if (bst_remove_all(root_ptr->right(), target) == 1) {
				occurtime++;
				goto Label_2;
			}
			else
				return occurtime;
		}

		if (root_ptr->left() == NULL)
		{   // Target was found and there is no left subtree, so we can
		// remove this node, making the right child be the new root.
			oldroot_ptr = root_ptr;
			root_ptr = root_ptr->right();
			delete oldroot_ptr;
			int occurtime = bst_remove_all(root_ptr, target);
		Label_3:
			if (bst_remove_all(root_ptr, target) == 1) {
				occurtime++;
				goto Label_3;
			}
			else
				return occurtime;
		}

		// If code reaches this point, then we must remove the target from
		// the current node. We'll actually replace this target with the
		// maximum item in our left subtree. We then continue
		// searching for more copies of the target to remove.
		// This continued search must start at the current root (since
		// the maximum element that we moved up from our left subtree
		// might also be a copy of the target).

		bst_remove_max(root_ptr->left(), root_ptr->data());
		return 1;
	}

	template <class Item>
	bag<Item>::bag(const bag<Item>& source)
		// Library facilities used: bintree.h
	{
		root_ptr = tree_copy(source.root_ptr);
	}

	template <class Item>
	bag<Item>::~bag()
		// Header file used: bintree.h
	{
		tree_clear(root_ptr);
	}

	template <class Item>
	typename bag<Item>::size_type bag<Item>::size() const
		// Header file used: bintree.h
	{
		return tree_size(root_ptr);
	}

	//Updated Function by student
	template <class Item>
	void bag<Item>::insert(const Item& entry)
		// Header file used: bintree.h
	{
		binary_tree_node<Item>* cursor;

		if (root_ptr == NULL)
		{   // Add the first node of the binary search tree:
			root_ptr = new binary_tree_node<Item>(entry);
			return;
		}

		else
		{   // Move down the tree and add a new leaf:
			cursor = root_ptr;
			inserted(cursor, entry);
		}
	}

	//---------student Defined function---------
	template <class Item>
	void bag<Item>::inserted(binary_tree_node<Item>* Node_ptr, const Item& entry) {
		if (Node_ptr->data() > entry)
			if (Node_ptr->left() == nullptr)
				Node_ptr->left() = new binary_tree_node<Item>(entry);
			else
				inserted(Node_ptr->left(), entry);
		else if (Node_ptr->data() <= entry)
			if (Node_ptr->right() == nullptr)
				Node_ptr->right() = new binary_tree_node<Item>(entry);
			else
				inserted(Node_ptr->right(), entry);
	}

	//Updated Function by student
	template <class Item>
	typename bag<Item>::size_type bag<Item>::count(const Item& target) const
	{
		size_type answer = 0;
		binary_tree_node<Item>* cursor;

		cursor = root_ptr;
		answer = counter(cursor, target);
		return answer;
	}

	//---------student Defined function---------
	template <class Item>
	typename bag<Item>::size_type bag<Item>::counter(binary_tree_node<Item>* Node_ptr, const Item& target) const {
		if (Node_ptr == nullptr)
			return 0;
		else if (Node_ptr->data() == target)
			return 1 + counter(Node_ptr->left(), target) + counter(Node_ptr->right(), target);
		else
			return counter(Node_ptr->left(), target) + counter(Node_ptr->right(), target);
	}

	template <class Item>
	typename bag<Item>::size_type bag<Item>::erase(const Item& target)
	{
		return bst_remove_all(root_ptr, target);
	}

	template <class Item>
	bool bag<Item>::erase_one(const Item& target)
	{
		return bst_remove(root_ptr, target);
	}

	template <class Item>
	void bag<Item>::operator =(const bag<Item>& source)
		// Header file used: bintree.h
	{
		if (root_ptr == source.root_ptr)
			return;
		tree_clear(root_ptr);
		root_ptr = tree_copy(source.root_ptr);
	}

	template <class Item>
	void bag<Item>::operator +=(const bag<Item>& addend)
	{
		if (root_ptr == addend.root_ptr)
		{
			bag<Item> copy = addend;
			insert_all(copy.root_ptr);
		}
		else
			insert_all(addend.root_ptr);
	}

	template <class Item>
	bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2)
	{
		bag<Item> answer = b1;
		answer += b2;
		return answer;
	}

	template <class Item>
	void bag<Item>::insert_all(binary_tree_node<Item>* addroot_ptr)
		// Precondition: addroot_ptr is the root pointer of a binary search tree that
		// is separate for the binary search tree of the bag that activated this
		// method.
		// Postcondition: All the items from the addroot_ptr's binary search tree
		// have been added to the binary search tree of the bag that activated this
		// method.
	{
		if (addroot_ptr != NULL)
		{
			insert(addroot_ptr->data());
			insert_all(addroot_ptr->left());
			insert_all(addroot_ptr->right());
		}
	}
}