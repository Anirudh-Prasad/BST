// ---------------------------- BinTree.h -------------------------------------
// Anirudh Prasad, CSS 343 A
// Created: 2/3/2019
// Last Modified: 2/10/2019
// ----------------------------------------------------------------------------
// Purpose: This is the header file for a binary search tree that 
// organizes NodeData objects.
// ----------------------------------------------------------------------------
// This header file describes the functions of the BinTree, both the main
// functions and structures as well as helper methods.
// ----------------------------------------------------------------------------

#ifndef BINTREE_H
#define BINTREE_H

#include "nodedata.h"
#include <iostream>
#include <algorithm>

using namespace std;

class BinTree {	// you add class/method comments and assumptions
	
public:
	// constructor
	BinTree(); 
	// copy constructor
	BinTree(const BinTree&); 
	// destructor, calls makeEmpty
	~BinTree();
	// true if tree is empty, otherwise false
	bool isEmpty() const;
	// make the tree empty
	void makeEmpty();
	// Operator << overload, outputs tree
	friend ostream& operator<<(ostream& output, const BinTree& btr);
	// Operator = overload, sets tree equal to another
	BinTree& operator=(const BinTree&);
	// Operator == overload, tests if two trees are equal
	bool operator==(const BinTree& bst) const;
	// operator != overload, tests if two trees are unequal
	bool operator!=(const BinTree& bst) const;
	// insert function that inserts a NodeData item into the tree
	bool insert(NodeData*);
	// retrieval function that checks if item is in tree and retrieves it
	bool retrieve(const NodeData& item, NodeData*& pointer) const;
	// provided below, displays the tree sideways
	void displaySideways() const;
	// Converts tree into an array, wipes tree
	void bstreeToArray(NodeData* arr[]);
	// returns height location of NodeData item
	int getHeight(const NodeData& item);
	
private:
	// Node class that stores data
	struct Node {
		NodeData* data;	// pointer to data object
		Node* left;	// left subtree pointer
		Node* right; // right subtree pointer

		// Node default constructor
		Node() : data(NULL), left(NULL), right(NULL) {}
		// Node constructor that takes in NodeData object
		Node(NodeData dta) : left(NULL), right(NULL) {
			data = new NodeData(dta);
		}
	};
	Node* root;	// root of the tree

// utility functions

	// outputs items in inorderwalk form
	ostream& inorderHelper(ostream& output, Node* bNode) const;
	// provided below, helps displaySideways()
	void sideways(Node*, int) const;
	// deletes the tree from Node to Node
	void recursiveDelete(Node* Node); 
	// assists the copy constructor by adding Nodes
	void copyHelper(const Node* Node); 
	// recursively traverses tree and inserts item
	bool recInsert(Node* leaf, NodeData* dta);
	// tests to see if two nodes are equal
	bool isEqual(Node* bNode1, Node* bNode2) const;
	// helps convert the tree into an array
	void toArrayHelper(NodeData* arr[], int pos, Node* leaf);
	// finds an item in the tree
	int heightHelper(const NodeData& item, const Node* leaf);
	// finds the height of a previously found item
	int depthFinder(const Node* leaf);
};

#endif
