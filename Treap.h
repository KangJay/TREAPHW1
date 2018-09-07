/* CSS343B 
 * Author: Ji Kang
 * Date: 4/15/2018
 * Class implements a template Dictionary (A.K.A 'Map') by utilizing a TREAP. 
 * Inside the Treap class, there are two dependent classes: an Iterator, and Node class 
 * specifically for this Treap class. Provides the standard functionality of the Dictionary ADT. 
 */
#pragma once
#include <utility>
#include <stack> 
#include <stdlib.h>
#include <iostream>
 
template<typename key, typename val>
class Treap {
public:
	class Iterator;
	class Node;

	Treap() : root_(nullptr), numNodes_(0) {}
	val& operator[](const key& k);
	void displayTree() { privDisplay(root_); }
	Iterator begin();
	Iterator end();
	void insert(const key& k);
	void dump();
	void isValidHeap(); 

	class Node {
	private:
		const key key_;
		val value_;
		int priority_;
	public:
		Node(const key & k) : key_(k), value_(1), left_(nullptr), right_(nullptr) { priority_ =rand() % 100; }
		Node* left_;
		Node* right_;
		const key& getKey() { return key_; }
		val& getVal() { return *&(value_); }
		int getPriority() { return priority_; }
		Node* left() { return left_; }
		Node* right() { return right_; }
	};

	class Iterator {
	public:
		Iterator(Node* root);
		bool operator==(const Iterator& other);
		bool operator!=(const Iterator& other); 
		Iterator& operator++(); 
		std::pair<const key&, val&> operator*(); 
	private:
		Node* current_; 
		std::stack<Node*> stack_; //Used to hold the nodes of the Treap for Iterator-use
		void leftmost(Node*);
	};
	
private: 
	Node* root_; 
	void privDisplay(Node* node);
	Node* privInsert(Node*, const key& k);
	val & lookup(const key& k, Node*);
	void rotateLeft(Node*&);
	void rotateRight(Node*&);
	void dump(Node*);
	bool isValidHeap(Node*, int); 
	int numNodes_;
};

//METHODS PERTAINING TO THE TREAP CLASS FUNCTIONALITY

/* 
	Public method that calls the private helper method to insert nodes into the Treap. 
*/
template<typename key, typename val>
void Treap<key, val>::insert(const key & k)
{
	privInsert(root_, k);
}

/*
	Private helper method to display the contents of the tree. Shares this functionality with the Iterator class. 
	See the section on iterators for a separate implementation. 
*/
template<typename key, typename val>
void Treap<key, val>::privDisplay(Node* node)
{
	if (!node) {
		return;
	}
	else {
		privDisplay(node->left());
		std::cout << node->getVal() << " " << node->getKey() << std::endl; 
		privDisplay(node->right());
	}
}

/*
	Private helper method to the public method 'insert(const key & k)'. 
	Method recursively... 
	1. Increments a node's value by 1 if the given node matches the parameterized key value. 
	2. Creates a new Node and adds it to the Treap if no other node contains the same key value.
	Method also calls helper rotation methods to help balance out the tree based on a random
	priority value assigned during construction. 
*/
template<typename key, typename val>
typename Treap<key,val>::Node* Treap<key, val>::privInsert(Node* node, const key & k)
{
	if (!root_) {
		root_ = new Node(k); 
	}
	else if (!node) {
		return new Node(k); 
	}
	else {
		if (node->getKey() == k) {
			node->getVal()++;
		}
		else if (node->getKey() < k) {
			node->right_ = privInsert(node->right(), k);
			numNodes_++;
			//Rotate if priority property is violated
			if (node->right_->getPriority() < node->getPriority()) {
				rotateLeft(node); 
			}
		}
		else if (node->getKey() > k) {
			node->left_ = privInsert(node->left(), k);
			numNodes_++; 
			//Rotate if priority property is violated
			if (node->left_->getPriority() < node->getPriority()) {
				rotateRight(node);
			}
		}
	}
	return node;
}

/*
	Private helper method to rotate certain nodes. This method is explicitly called
	when a node's right child has a lower priority value (violates the rule). 
	Method saves copies of the nodes to be moved, does the rotation, and sets the 
	grandparent, parent, and child node accordingly afterwards. 
*/
template<typename key, typename val>
void Treap<key, val>::rotateLeft(Node*& gParent)
{
	if (gParent == root_) { //Special case: Root is being replaced
		Node* parent = root_->right(); 
		root_->right_ = parent->left(); 
		parent->left_ = root_; 
		root_ = parent; 
	}
	else {
		Node* parent = gParent->right();
		gParent->right_ = parent->left_;
		parent->left_ = gParent;
		gParent = parent;
	}
}

/*
	Private helper method to rotate certain nodes. This method is explicitly called
	when a node's left child has a lower priority value (violates the rule).
	Method saves copies of the nodes to be moved, does the rotation, and sets the
	grandparent, parent, and child node accordingly afterwards.
*/
template<typename key, typename val>
void Treap<key, val>::rotateRight(Node*& gParent)
{
	if (gParent == root_){ //Special case: Root is being replaced
		Node* parent = root_->left();
		root_->left_ = parent->right(); 
		parent->right_ = root_;
		root_ = parent; 
	}
	else {
		Node* parent = gParent->left();
		gParent->left_ = parent->right_;
		parent->right_ = gParent;
		gParent = parent;
	}
}

/*
	Public method to return the value associated with a given key. 
	Calls the private helper method for the implementation. 
*/
template<typename key, typename val>
val & Treap<key, val>::operator[](const key & k)
{
	return (lookup(k, root_)); 
}

/*
	Private helper method to the public method 'operator[]'
	Recursively finds the given node by checking if the given node's key matches with the 
	parameterized key value and returns the reference to a pointer of the value if found. 
	Else, it obeys the Binary search tree invariant of everything greater than the node is on the
	right, and vice-versa and does this recursively. If nothing is found, it will eventually return a
	nullptr object. 
*/
template<typename key, typename val>
val & Treap<key, val>::lookup(const key & k, Node* node)
{
	if (node->getKey() == k) {
		return *&(node->getVal());
	}
	else if (node->getKey() < k) {
		return *&(lookup(k, node->right_));
	}
	else {
		return *&(lookup(k, node->left_));
	}
}

/*
	Public method to output stderr to console. 
	Utilized to check for the structure of the tree. 
*/
template<typename key, typename val>
void Treap<key, val>::dump()
{
	dump(root_);
}

/*
	Private helper method of 'dump()'. 
	Method recursively prints out the tree's structure by printing out its 
	key, value, left child, and right child. It will then recursively call itself
	until all nodes have been visited. 
*/
template<typename key, typename val>
void Treap<key, val>::dump(Node * node)
{
	if (!node) return;
	std::cerr << "Key: " << node->getKey() << ", Value: " << node->getVal() << std::endl;
	if (node->left()) {
		std::cerr << "Left Child Key: " << node->left_->getKey() << ", Left Child Value: " << node->left_->getVal() << std::endl;
	}
	else {
		std::cerr << "Left Child Key: nullptr, Left Child Value: nullptr" << std::endl;
	}
	if (node->right()) {
		std::cerr << "Right Child Key: " << node->right_->getKey() << ", Right Child Value: " << node->right_->getVal() << std::endl;
	}
	else {
		std::cerr << "Right Child Key: nullptr, Right Child Value: nullptr" << std::endl;
	}
	std::cerr << std::endl;
	dump(node->left());
	dump(node->right());
}

/*
	Public method that prints whether or not the given Treap follows
	the properties of a Treap. 
*/
template<typename key, typename val>
void Treap<key, val>::isValidHeap()
{
	if (isValidHeap(root_, 0)) {
		std::cout << "The Tree is a valid Heap and follows Heap properties" << std::endl; 
	}
	else {
		std::cout << "The Tree is not a valid Heap" << std::endl; 
	}
}
/*
	Heaps follow the property of being a complete tree. 
	Since we can check the upper level of the node by taking the index
	or node place and multiplying it by 2 and adding 1, we can see if any nodes
	go past this level. The method then recursively checks if every node obeys this rule. 
	If so, it will return true and the public method will print something accordingly. 
*/
template<typename key, typename val>
bool Treap<key, val>::isValidHeap(Node * node, int index)
{
	if (node == nullptr) {
		return true; 
	}
	if ((2 * index + 1) <= numNodes_ && node->left() == nullptr
		&& node->right() == nullptr) {
		return true; 
	}
	else if (2 * index + 1 > numNodes_) {
		return false; 
	} 
	return (isValidHeap(node->left(), index + 1) && isValidHeap(node->right(), index + 1));
}


//METHODS PERTAINING TO THE ITERATOR CLASS FUNCTIONALITY

/*
	Returns a Iterator holding the first value in our Treap (the smallest). 
	Accomplishes this by calling the constructor. 
*/
template<typename key, typename val>
typename Treap<key, val>::Iterator Treap<key, val>::begin()
{
	return Iterator(root_);
}

/*
	Meant as a end-case to any loop involving the iterator. 
	Returns an Iterator object which holds a nullptr object. 
*/
template<typename key, typename val>
typename Treap<key, val>::Iterator Treap<key, val>::end()
{
	return Iterator(nullptr);
}

/*
	Only constructor for this Iterator class. 
	Given a valid input (!=nullptr), the Iterator object
	holds the first object (smallest) in the treap with current_ after
	populating the stack halfway (Log(n) elements). 
*/
template<typename key, typename val>
Treap<key, val>::Iterator::Iterator(Node* root)
{
	if (!root) {
		current_ = nullptr; 
		return; 
	}
	leftmost(root); 
	current_ = stack_.top(); 
	stack_.pop();
}

/*
	Returns true if the Nodes the two Iterator holds are equal to each other. 
	False otherwise. 
*/
template<typename key, typename val>
bool Treap<key, val>::Iterator::operator==(const Iterator & other)
{
	return current_ == other.current_;
}

/*
	Utilizes an existing boolean method declaration within the Iterator class. 
	(See "operator==(const Iterator & other)" for more details). 
	Returns the reverse boolean logic of the mentioned method. 
*/
template<typename key, typename val>
bool Treap<key, val>::Iterator::operator!=(const Iterator & other)
{
	return !(*this == other);
}

/*
	Increment overloaded operator. 
	Method populates the stack, changes the value of current_, and removes a node from 
	the stack as run-time goes on. This is intended to have the stack only manage
	half of the tree at any given time, giving a better memory management overall. 
*/
template<typename key, typename val>
typename Treap<key, val>::Iterator & Treap<key, val>::Iterator::operator++()
{
	leftmost(current_->right());
	if (stack_.empty()) {
		current_ = nullptr;
		return *this;
	}
	current_ = stack_.top();
	stack_.pop();
	return *this;
}

/*
	Dereference overloaded operator. 
	Instead of returning the node itself which would end in a memory-leak, 
	it returns a pair representing the data found within the given node. 
	It returns a const key & object and a value & object. 
*/
template<typename key, typename val>
std::pair<const key&, val&> Treap<key, val>::Iterator::operator*()
{
	return std::pair<const key&, val&>(current_->getKey(), current_->getVal());
}

/*
	Private helper method to populate the stack_ as run-time goes on. 
	It will move left-ward down the tree and push each node it visits on the way down. 
*/
template<typename key, typename val>
void Treap<key, val>::Iterator::leftmost(Node* node)
{
	while (node) {
		stack_.push(node);
		node = node->left();
	}
}