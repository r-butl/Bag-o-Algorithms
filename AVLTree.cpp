// CSCI 311 - Spring 2023
// AVLTree cpp
// Author: Lucas Butler

#include <iostream>
#include <limits.h>
#include "AVLTree.h"
#include "AVLNode.h"
using namespace std;

// Constructor for the AVL tree
AVLTree::AVLTree(){
	root = nullptr;
}

// Returns a pointer to the root node
std::shared_ptr<AVLNode> AVLTree::getRoot(){
  return root;
}

// Returns the number of elements in the tree
int AVLTree::getSize(){
	// In spite of being lazy, create a vector of all the nodes in the tree and return its size
	std::vector<std::shared_ptr<AVLNode>> nodes;
	postOrder(root, nodes);	
	return nodes.size();
}

// Searches for the value in the tree
std::shared_ptr<AVLNode> AVLTree::search(int val){
 	
	return search(root, val);
}

// Helper function for the search function
std::shared_ptr<AVLNode> AVLTree::search(std::shared_ptr<AVLNode> n, int val){
  	// base case
	if(n == nullptr) return nullptr;
	// Matched value, return a pointer to the node
	else if(n->value == val) return n;
	// Val is less than the current node, attempt to traverse left
	else if(val < n->value && n->left != nullptr) return search(n->left, val);
	// Val is greater than the current node, attempt to traverse right
	else if(val > n->value && n->right != nullptr) return search(n->right, val);
	// value is not in the tree
	else return nullptr;
}

// Function to find that smallest node in the tree
std::shared_ptr<AVLNode> AVLTree::minimum(){
  return minimum(root);
}

// Helper function to find the smallest node in the tree
std::shared_ptr<AVLNode> AVLTree::minimum(std::shared_ptr<AVLNode> n){
 	
	// Base case
	if(n == nullptr) return nullptr;
	// if the nodes left node does not exists, we are at the smallest node in the tree
	else if(n->left == nullptr) return n;
	// Traverse to the left
	else return minimum(n->left);

}

// facade function to find the largest node in the tree
std::shared_ptr<AVLNode> AVLTree::maximum(){
	
	return maximum(root);
}

// Helper function for the maximum 
std::shared_ptr<AVLNode> AVLTree::maximum(std::shared_ptr<AVLNode> n){

	// Base case
	if(n == nullptr) return nullptr;
	// if the nodes right node does not exist, we are at the largest node in the tree
	else if(n->right == nullptr) return n;
	// Tracerse to the right
	else return maximum(n->right);
}

// Returns the height of the current node
int getHeight(std::shared_ptr<AVLNode> n){
  	// Base case
  	if(n == nullptr) return -1;
	// Return the max height of the child nodes and add 1
	return std::max(getHeight(n->left), getHeight(n->right)) + 1;

}

// Returns the balance factor of the current node
int getBalanceFactor(std::shared_ptr<AVLNode> n){
	
	if(n == nullptr) return 0;
	
	// Call the get height function on the two children nodes
 	int balance = getHeight(n->right) - getHeight(n->left);
	return balance;	
}

// facade function for inserting a value into the tree
void AVLTree::insertValue(int val){
	root = insertValue(root, val);
}

// Helper function for insertin a value into the tree
std::shared_ptr<AVLNode> AVLTree::insertValue(std::shared_ptr<AVLNode> n, int val){
	
	// Node is empty, set the node to the new value 
	if(n == nullptr){
		std::shared_ptr<AVLNode> temp(new AVLNode(val));
		temp->height = 0;
		temp->balanceFactor = 0;
		n = temp;
		return n;
	// Value already exists
	}else if(n->value == val){
		return n;
	// traverse right
	}else if(n->value < val){
	       	n->right = insertValue(n->right, val);
	// traverse left
	}else if(n->value > val){
		n->left = insertValue(n->left, val);
	}
	// Check if the children nodes exist while updating the heights 
	n->height = getHeight(n);
	n->balanceFactor = getBalanceFactor(n);
	n = rebalance(n);
	return n;
}

// facade function to delete a value in the tree
void AVLTree::deleteValue(int val){
	
	// Begin the function
	root = deleteValue(root, val);
}

// helper function for the delete function
std::shared_ptr<AVLNode> AVLTree::deleteValue(std::shared_ptr<AVLNode> n, int val){
 	
	// covers base case of value not being present
       	if(n == nullptr) return nullptr;
	// current node is less than the value we are looking for, traverse right
	else if(n->value < val){
		// Traverse to the right
		n->right = deleteValue(n->right, val);
	// current node is greater than the value we are looking for, traverse left
	}else if(n->value > val){
		// Traverse to the left
		n->left = deleteValue(n->left, val);
	// The value is present, determine how many children and act accordingly
	}else{
		// no children
		if(n->right == nullptr && n->left == nullptr){
			n = nullptr;	// point the value to null to erase it
			return n;
			// one child
		}else if(n->left == nullptr){
			// the left child exists so set the current node to it
			n = n->right;
		}else if(n->right == nullptr){
			// the right child exists so set the current node to it
			n = n->left;
		// two children exist, find the next largest value
		}else{
			// find next largest element
			std::shared_ptr<AVLNode> temp = minimum(n->right);
			n->value = temp->value;
			n->right = deleteValue(n->right, temp->value);
		}
	}		
	// Check if the children nodes exist while updating the heights 
		n->height = getHeight(n);
		n->balanceFactor = getBalanceFactor(n);
		n = rebalance(n);

	return n;
}

// facade functoin to rebalance the tree
std::shared_ptr<AVLNode> AVLTree::rebalance(std::shared_ptr<AVLNode> n){
  
	if(n == nullptr) return nullptr;

	// Left rotation
	if(n->balanceFactor == 2 && n->right->balanceFactor >= 0){
		return rotateLeft(n);
	// Right left rotation
	}else if(n->balanceFactor == 2 && n->right->balanceFactor < 0){
		return rotateRightLeft(n);
	// Address a right rotation
	}else if(n->balanceFactor == -2 && n->left->balanceFactor <= 0){ 
		return rotateRight(n);
	// Left right rotation	
	}else if(n->balanceFactor == -2 && n->left->balanceFactor > 0){ 
		return rotateLeftRight(n);
	}else return n;
}

// helper function to rebalance the tree
std::shared_ptr<AVLNode> AVLTree::rotateLeft(std::shared_ptr<AVLNode> n){
 
       	// Use a temporary pointer to store the right node	
	std::shared_ptr<AVLNode> x = n->right;

	// preform the rotation and update the heights
	n->right = x->left;
	n->height = getHeight(n);
	x->left = n;

	// Update heights and balance factors
	x->height = getHeight(x);
	n->balanceFactor = getBalanceFactor(n);
	x->balanceFactor = getBalanceFactor(x);

	// relink the tree
	return x;
}

// Preform a right rotation on the node passed
std::shared_ptr<AVLNode> AVLTree::rotateRight(std::shared_ptr<AVLNode> n){
 	
       	// Use a temporary pointer to store the left node	
	std::shared_ptr<AVLNode> x = n->left;

	// preform the rotation	
	n->left = x->right;
	n->height = getHeight(n);
	x->right = n;

	// Update the heights and balance factor
	x->height = getHeight(x);
	n->balanceFactor = getBalanceFactor(n);
	x->balanceFactor = getBalanceFactor(x);

	// relink the tree	
	return x;
}

// preform a left right rotation on the current node
std::shared_ptr<AVLNode> AVLTree::rotateLeftRight(std::shared_ptr<AVLNode> n){

       // rotate left	
        std::shared_ptr<AVLNode> x = n->left;
	std::shared_ptr<AVLNode> z = x->right;
	x->right = z->left;
	x->height = getHeight(x);
	z->left = x;
	n->left = z;
	
	// rotate right
	n->left = z->right;
	n->height = getHeight(n);
	z->right = n;
	z->height = getHeight(z);

	// update balance factors
	n->balanceFactor = getBalanceFactor(n);
	x->balanceFactor = getBalanceFactor(x);
	z->balanceFactor = getBalanceFactor(z);

	// relink the tree
	return z;
}

// preform a right left rotation on the current node 
std::shared_ptr<AVLNode> AVLTree::rotateRightLeft(std::shared_ptr<AVLNode> n){
  
	// rotate right
	std::shared_ptr<AVLNode> x = n->right;
	std::shared_ptr<AVLNode> z = x->left;
	x->left = z->right;
	x->height = getHeight(x);
	z->right = x;
	n->right = z;

	// rotate left
	n->right = z->left;
	n->height = getHeight(n);
	z->left = n;
	z->height = getHeight(z);

	// update balance factors
	n->balanceFactor = getBalanceFactor(n);
	x->balanceFactor = getBalanceFactor(x);
	z->balanceFactor = getBalanceFactor(z);

	// Relink the tree
	return z;
}

// Print the tree in pre order form
void AVLTree::preOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
	// base case
	if(n == nullptr) return;
	
	// Add the element to the vector
	order.push_back(n);
	// recursive call left
	preOrder(n->left, order);
	// recursive call right
	preOrder(n->right, order);
}

// Print the tree in order 
void AVLTree::inOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
	// Base case
	if(n == nullptr) return;

	// recursive call left
	inOrder(n->left, order);
	// Add the element to the vector
	order.push_back(n);
	// recursice call right
	inOrder(n->right, order);
}

// Print the tree in post order form
void AVLTree::postOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
	// Base Case
	if(n == nullptr) return;

	// Recursive call left
	postOrder(n->left, order);
	// Recursive call right
	postOrder(n->right, order);
	// Add the element to the vector;
	order.push_back(n);
}



