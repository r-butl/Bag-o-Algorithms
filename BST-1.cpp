// CSCI 311 - Spring 2023
// Binary Search Tree Implementaton
// Author: Lucas Butler

#include<iostream>
#include <vector>
#include <limits>
#include "BST.h"
using namespace std;

// if the constructor is called 
BST::BST(){

	// initialize the root to point to null	
	root = nullptr; 

}

// if the destructor is called
BST::~BST(){
	
	// point the root to null to start a chain reaction of smart pointer destruction
	root = nullptr;
}

// Function facade to search for a value in a BST
std::shared_ptr<Node> BST::search(int target){

	// Call the helper search function on the root
	return search(root, target);
}

// Search helper function that will be used to conduct the search
std::shared_ptr<Node> BST::search(std::shared_ptr<Node> n, int target){
 
    if(n == nullptr) return nullptr;	
	else if(n->value == target) return n;
	else if(target < n->value) return search(n->left, target);
	else return search(n->right, target);
}

// Facade function to find the smallest value in a BST
std::shared_ptr<Node> BST::minimum(){

       	// call the minimum function on the root node	
	return minimum(root);
}

// helper function to find the minimum left in the BST
std::shared_ptr<Node> BST::minimum(std::shared_ptr<Node> n){
 
       	// Naturally, the smallest value in a BST is the value to the furthest left point	
	if(n == nullptr) return nullptr;
	else if(n->left != nullptr) return minimum(n->left);
	return n;	
}

// Facade function for the maximum function 
std::shared_ptr<Node> BST::maximum(){
 	return maximum(root);
}

// Helper function for the maximum function
std::shared_ptr<Node> BST::maximum(std::shared_ptr<Node> n){
	// The largest value in a BST is the value to the furthest right point
	// protection against passing a nullptr, EI an enpty tree
	if(n == nullptr) return nullptr;
	else if(n->right != nullptr) return maximum(n->right);
	return n;
}

// Facade function for the insert value function
void BST::insertValue(int val){

	// Call the helper function and pass the root
	insertValue(root, val);
}

// Helper function for the insertValue function
std::shared_ptr<Node> BST::insertValue(std::shared_ptr<Node> n, int val){

	if(n == nullptr){	// Empty root node, create it
		std::shared_ptr<Node> nodePtr(new Node(val));
		root = nodePtr;
		return nodePtr;

	}else if(n->value == val){
		return nullptr;			// protect against duplicate values

	}else if(n->value > val){		// If the insert is less than the current node, look at the left node
		
		if(n->left == nullptr) {	// if the node doesnt exist, create new one and insert it
			std::shared_ptr<Node> nodePtr(new Node(val));
			n->left = nodePtr;
			return nodePtr;

		}else{	// Traverse to the node because it exists
			return insertValue(n->left, val);
		}

	}else if(n->value < val){		// The val is greater than the current node, look right
		
		if(n->right == nullptr){	// If the right node doesnt exist, create a new one and insert it
			std::shared_ptr<Node> nodePtr(new Node(val));
			n->right = nodePtr;
			return nodePtr;
		
		}else{	// The node exists already to traverse to it
			return insertValue(n->right, val);
		}
	}

}

// facade for the delete value function
void BST::deleteValue(int val){

	// Call the delete function starting on the root node
	root = deleteValue(root, val);
}

// Delete value helper function 
std::shared_ptr<Node> BST::deleteValue(std::shared_ptr<Node> n, int val){

	// The current node points to null
	if(n == NULL){
		return nullptr;
	}

	//printf("value: %d\n", n->value);
	if(val < n->value){
		// traverse left
		n->left = deleteValue(n->left, val);
	}else if(val > n->value){
		// traverse right
		n->right = deleteValue(n->right, val);
	}else{
		
		if(n->left == NULL && n->right == NULL){
			// the node has no children
			n = nullptr;
			return n;
		}else if(n->left == nullptr){
			// set the current node the right child
			n = n->right;
			return n;
		}else if(n->right == nullptr){
			// set the current node the left child
			n = n->left;
			return n;
		}
		// Find the smallest value in the right subtree and set the nodes value to it
		std::shared_ptr<Node> m = minimum(n->right);
		n->value = m->value;
		n->right = deleteValue(n->right, m->value);
	}

	return n;
}

//Facade function for the isBST function
bool BST::isBST(std::shared_ptr<Node> n){

	// Call the BST helper function passing the lowest and highest possible values as parameters
      	return isBST(n, numeric_limits<int>::min(), numeric_limits<int>::max());	
}

// Detemines if a BST is valid or not
bool BST::isBST(std::shared_ptr<Node> n, int low, int high){
 
        // if the current node points to null, we have reached the end of the tree	
	if(n == nullptr) return true;
	// if the node is below the upper limit of the range, call on the left node and continue
	else if(n->value < high && n->value > low){
	       	return isBST(n->left, low, n->value) && isBST(n->right, n->value, high);
	}else return false;

}

// Fill the vector with elements in pre order format
void BST::preOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){

	if(n == nullptr) return;
	order.push_back(n);
	preOrder(n->left, order);
	preOrder(n->right, order);
}

// Fill the vector with elements in order
void BST::inOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){
	
	if(n==nullptr) return;
	inOrder(n->left, order);
	order.push_back(n);
	inOrder(n->right, order);
}

// Fill a vector with elements in post order order format
void BST::postOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){

	if(n==nullptr) return;
	postOrder(n->left, order);
	postOrder(n->right, order);
	order.push_back(n);
}
