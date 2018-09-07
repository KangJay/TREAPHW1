/* 
	Dictionary class utilizing a Binary search tree for its implementation. 
	Class utilizes two dependent classes: a template node class and a template iterator class
	that runs off of this main class. 
	The user(s) will have the option of choosing which types are meant for the key and val but 
	will be required to stick to those. 
*/
#pragma once
#include "DictNode.h"
#include <utility>
#include <stack> 

template<typename key, typename val>
class BST {
public:
	class Iterator;
	BST() : root_(nullptr) {}
	val& operator[](const key& k);
	void displayTree() { privDisplay(root_); }  //Public method to hide implementation
	Iterator begin();
	Iterator end();

	class Iterator {
	public:
		Iterator(Node<key, val>* root);
		bool operator==(const Iterator& other);
		bool operator!=(const Iterator& other);
		Iterator& operator++();
		std::pair<const key&, val&> operator*();
	private:
		Node<key, val>* current_;
		std::stack<Node<key, val>*> stack_;
		void populateIterator(Node<key, val>* node);
	};

private:
	Node<key, val>* root_;
	void privDisplay(Node<key, val>* node);
};

/*
	Public overloaded method of []. 
	Utilizes a private node helper method to insert and/or return the
	reference to the pointer of the value of the given node. 
*/
template<typename key, typename val>
val & BST<key, val>::operator[](const key & k)
{
	if (!root_) {
		root_ = new Node<key, val>(k);
		return root_->getVal();
	}
	return root_->lookup(k);
}

/*
	Returns a Iterator holding the first value in our Treap (the smallest). 
	Accomplishes this by calling the constructor.
*/
template<typename key, typename val>
typename BST<key, val>::Iterator BST<key, val>::begin()
{
	return Iterator(root_);
}

/*
	Meant as a end-case to any loop involving the iterator.
	Returns an Iterator object which holds a nullptr object.
*/
template<typename key, typename val>
typename BST<key, val>::Iterator BST<key, val>::end()
{
	return Iterator(nullptr);
}

/*
	Private helper method to display the contents of the tree. Shares this functionality with the Iterator class.
	See the section on iterators for a separate implementation.
*/
template<typename key, typename val>
void BST<key, val>::privDisplay(Node<key, val>* node)
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
	Only constructor for this Iterator class.
	Given a valid input (!=nullptr), the Iterator object
	holds the first object (smallest) in the treap with current_ after
	populating the stack halfway (Log(n) elements).
*/
template<typename key, typename val>
BST<key, val>::Iterator::Iterator(Node<key, val>* root)
{
	if (!root) {
		current_ = nullptr;
		return;
	}
	populateIterator(root);
	current_ = stack_.top();
	stack_.pop();
}

/*
	Returns true if the Nodes the two Iterator holds are equal to each other. 
	False otherwise. 
*/
template<typename key, typename val>
bool BST<key, val>::Iterator::operator==(const Iterator & other)
{
	return current_ == other.current_;
}

template<typename key, typename val>
bool BST<key, val>::Iterator::operator!=(const Iterator & other)
{
	return !(*this == other);
}

/*
	Increment overloaded operator. 
	Method populates the stack, changes the value of current_, and removes a node from 
	the stack as run-time goes on. 
*/
template<typename key, typename val>
typename BST<key, val>::Iterator & BST<key, val>::Iterator::operator++()
{
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
std::pair<const key&, val&> BST<key, val>::Iterator::operator*()
{
	return std::pair<const key&, val&>(current_->getKey(), current_->getVal());
}

/*
	Private helper method to get the contents of the tree into the stack
	from the beginning for use later on down the line. Will recursively
	populate the stack by going to the right as far as possible, 
	pushing the node into the stack, then visiting left for all branches. 
*/
template<typename key, typename val>
void BST<key, val>::Iterator::populateIterator(Node<key, val>* node)
{
	if (node == nullptr) {
		return;
	}
	populateIterator(node->right());
	stack_.push(node);
	populateIterator(node->left());
}
