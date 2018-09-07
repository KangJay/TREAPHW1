/* DictNode class is a dependent class on the DictBST class. It represents a singular node which contains 
a template key and value type that is defined by the user. From there, it has methods to add to the tree, 
retrieve a certain value from the tree based on the key, and various getter methods. All of these methods
surmount to a recreation of the Dictionary ADT. 
*/
#pragma once
#include <iostream> 
#include <utility> 

template<class key, class val>
class Node {
private:
	const key key_;
	val value_;
	Node<key, val>* left_;
	Node<key, val>* right_;
public:
	Node(const key & k) : key_(k), value_(), left_(nullptr), right_(nullptr) {}
	val& lookup(const key & k);
	
	//Getters
	const key& getKey() { return key_; } 
	val& getVal() { return value_; }
	Node* left() { return left_; }
	Node* right() { return right_; }
};

/*
	Compounded method of retrieving a node's certain value based on the lookup key, as well as, 
	inserting to the tree if the node is not found. The method runs recursively off of the 
	node's children and follows the standard binary search tree rule of every node to the right
	of the parent is greater and vice-versa for the left side. 
*/
template<class key, class val>
val & Node<key, val>::lookup(const key & k)
{
	if (key_ == k) {
		return *&(value_);
	}
	if (k < key_) {
		if (!left_) {
			left_ = new Node<key, val>(k);
			return *&(left_->value_);
		}
		return left_->lookup(k);
	}
	else if (k > key_) {
		if (!right_) {
			right_ = new Node<key, val>(k);
			return *&(right_->value_);
		}
		return right_->lookup(k);
	}
	return value_; //Keep compiler happy
}
