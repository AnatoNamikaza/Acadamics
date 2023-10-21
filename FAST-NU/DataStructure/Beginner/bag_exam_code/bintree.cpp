#include <cassert>    // Provides assert
#include <cstdlib>   // Provides NULL, std::size_t
#include <iomanip>    // Provides std::setw
#include <iostream>   // Provides std::cout
#include "bintree.h"

namespace main_savitch_10
{
    template <class Process, class BTNode>
    void inorder(Process f, BTNode* node_ptr)
        // Library facilities used: cstdlib
    {
        if (node_ptr != NULL)
        {
            inorder(f, node_ptr->left());
            f(node_ptr->data());
            inorder(f, node_ptr->right());
        }
    }

    template <class Process, class BTNode>
    void postorder(Process f, BTNode* node_ptr)
        // Library facilities used: cstdlib
    {
        if (node_ptr != NULL)
        {
            postorder(f, node_ptr->left());
            postorder(f, node_ptr->right());
            f(node_ptr->data());
        }
    }

    template <class Process, class BTNode>
    void preorder(Process f, BTNode* node_ptr)
        // Library facilities used: cstdlib
    {
        if (node_ptr != NULL)
        {
            f(node_ptr->data());
            preorder(f, node_ptr->left());
            preorder(f, node_ptr->right());
        }
    }

    template <class Item, class SizeType>
    void print(const binary_tree_node<Item>* node_ptr, SizeType depth)
        // Library facilities used: iomanip, iostream, stdlib
    {
        if (node_ptr != NULL)
        {
            print(node_ptr->right(), depth + 1);
            std::cout << std::setw(4 * depth) << ""; // Indent 4*depth spaces.
            std::cout << node_ptr->data()<<"--------------------------" << std::endl;               ///undodododosafis
            print(node_ptr->left(), depth + 1);
        }
    }

    template <class Item>
    void tree_clear(binary_tree_node<Item>*& root_ptr)
        // Library facilities used: cstdlib
    {
        if (root_ptr != NULL)
        {
            tree_clear(root_ptr->left());
            tree_clear(root_ptr->right());
            delete root_ptr;
            root_ptr = NULL;
        }
    }

    template <class Item>
    binary_tree_node<Item>* tree_copy(const binary_tree_node<Item>* root_ptr)
        // Library facilities used: cstdlib
    {
        binary_tree_node<Item>* l_ptr;
        binary_tree_node<Item>* r_ptr;

        if (root_ptr == NULL)
            return NULL;
        else
        {
            l_ptr = tree_copy(root_ptr->left());
            r_ptr = tree_copy(root_ptr->right());
            return
                new binary_tree_node<Item>(root_ptr->data(), l_ptr, r_ptr);
        }
    }

    template <class Item>
    std::size_t tree_size(const binary_tree_node<Item>* node_ptr)
        // Library facilities used: cstdlib
    {
        if (node_ptr == NULL)
            return 0;
        else
            return
            1 + tree_size(node_ptr->left()) + tree_size(node_ptr->right());
    }
};