// --------------------------- BinTree.cpp ------------------------------------
// Anirudh Prasad, CSS 343 A
// Created: 2/3/2019
// Last Modified: 2/10/2019
// ----------------------------------------------------------------------------
// Purpose: This is the implementation file for a binary search tree that 
// organizes NodeData objects.
// ----------------------------------------------------------------------------
// This binary search tree can insert items, retrieve items from within the 
// tree, and it can convert the entire tree into an array. This tree also
// overloads various operators for special functions.
// ----------------------------------------------------------------------------
#include "BinTree.h"

//default constructor
BinTree::BinTree()
{
	root = NULL;
}

//copy constructor that copies the tree in the parameter
BinTree::BinTree(const BinTree& btr)
{
	root = new Node(*(btr.root->data));
	copyHelper(btr.root->left);
	copyHelper(btr.root->right);
}

//helper method that inserts a node and recursively calls itself to insert the
//Node's children
void BinTree::copyHelper(const Node* bNode)
{
	if (bNode != NULL) {
		insert(bNode->data);
		copyHelper(bNode->left);
		copyHelper(bNode->right);
	}
}

//Destructor for BinTree
BinTree::~BinTree()
{
	recursiveDelete(root);
	root = NULL;
}

//Helper method for destructor that deletes the tree recursively
//Deletes both the Node itself and the data object it carries
void BinTree::recursiveDelete(Node* node)
{
	if (node != NULL) 
	{
		recursiveDelete(node->left);
		recursiveDelete(node->right);
		delete node->data;
		node->data = NULL;
		delete node;
		node = NULL;
	}
}

//Insert method that checks to see if the tree is empty before setting Root
bool BinTree::insert(NodeData* dta)
{
	if (isEmpty()) 
	{
		root = new Node(*dta);
		return true;
	}
	return recInsert(root, dta);
}

//Helper method for insert that follows BST data ordering procedure
//Returns false if data is already in tree
bool BinTree::recInsert(Node* leaf, NodeData* dta)
{
	if (*leaf->data < *dta) 
	{
		if (leaf->right != NULL) 
		{
			return recInsert(leaf->right, dta);
		}
		leaf->right = new Node(*dta);
		return true;
	}
	if (*leaf->data > *dta) 
	{
		if (leaf->left != NULL) 
		{
			return recInsert(leaf->left, dta);
		}
		leaf->left = new Node(*dta);
		return true;
	}
	
	return false; //item already in tree
}

//Iterative function that searches tree for item
//If item is found in tree, sets pointer to address of data item
bool BinTree::retrieve(const NodeData& item, NodeData*& pointer) const
{
	Node* curr = root;

	while (curr != NULL) 
	{

		if (item == *curr->data) 
		{
			pointer = curr->data;
			return true;
		}

		if (item > *curr->data) 
		{
			curr = curr->right;
		}
		else 
		{
			curr = curr->left;
		}
	}

	return false;
}

//Checks to see if the tree is empty
bool BinTree::isEmpty() const
{
	if (root == NULL) return true;
	return false;
}

//Empties the tree by utilizing the destructor helper function
void BinTree::makeEmpty()
{
	recursiveDelete(root);
	root = NULL;
}

//Operator= overload, makes this tree a copy of another
BinTree& BinTree::operator=(const BinTree& btr)
{
	if (this != &btr) 
	{
		makeEmpty();
		root = new Node(*(btr.root->data));
		copyHelper(btr.root->left);
		copyHelper(btr.root->right);
	}

	return *this;
}

//Operator== overload Tests if two trees are equivalent
bool BinTree::operator==(const BinTree& btr) const
{
	return isEqual(root, btr.root);
}

//Helper function for Operator==, tests equality of two trees
bool BinTree::isEqual(Node* bNode1, Node* bNode2) const
{
	if (bNode1 == NULL && bNode2 == NULL) return true;
	if (bNode1 == NULL && bNode2 != NULL) return false;
	if (bNode1 != NULL && bNode2 == NULL) return false;
	if ((*bNode1->data == *bNode2->data)) 
	{
		return isEqual(bNode1->left, bNode2->left) &&
			isEqual(bNode1->right, bNode2->right);
	}
	else return false;
}

//Operator!= overload, tests if two trees are unequal
bool BinTree::operator!=(const BinTree& btr) const
{
	return !(*this == btr);
}

//Operator<< overload, outputs contents of tree in inorder form
ostream& operator<<(ostream& output, const BinTree& btr)
{
	btr.inorderHelper(output, btr.root);
	output << endl;
	return output;
}

//Helper function for Operator<<, adds data items to output in inorder form
ostream& BinTree::inorderHelper(ostream& output, Node* bNode) const
{
	if (bNode == NULL) return output;

	inorderHelper(output, bNode->left);
	output << *bNode->data << " ";
	inorderHelper(output, bNode->right);
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//Converts the tree into an array, and then empties the tree
void BinTree::bstreeToArray(NodeData* arr[])
{
	toArrayHelper(arr, 0, root);
	makeEmpty();
}

//Helper function for bstreeToArray, helps construct the array
void BinTree::toArrayHelper(NodeData* arr[], int pos, Node* leaf)
{
	if (leaf == NULL) return;

	toArrayHelper(arr, pos, leaf->left);
	arr[pos++] = leaf->data;
	toArrayHelper(arr, pos, leaf->right);
}

//Function that returns the height location of the NodeData item
int BinTree::getHeight(const NodeData& item)
{
	if (isEmpty()) return 0;
	return heightHelper(item, root);
}

//Helper function for getHeight that parses tree to find item
//If item is in tree, calls seperate function to calculate height
int BinTree::heightHelper(const NodeData& item, const Node* leaf)
{
	if (leaf == NULL) return 0;
	if (*leaf->data == item) return depthFinder(leaf);
	else 
	{
		int s1 = heightHelper(item, leaf->left);
		int s2 = heightHelper(item, leaf->right);
		int maxVal = max(s1, s2);
		return maxVal;
	}
}

//Helper function for heightHelper that calculates height location of the item
//in the tree
int BinTree::depthFinder(const Node* leaf)
{
	if (leaf == NULL) return 0;
	int s1 = depthFinder(leaf->left);
	int s2 = depthFinder(leaf->right);
	int depthMax = max(s1, s2);
	return 1 + depthMax;
}


//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) 
	{
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) 
		{
			cout << "    ";
		}

		cout << *current->data << endl; // display information of object
		sideways(current->left, level);
	}
}
