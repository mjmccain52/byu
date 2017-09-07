/*
 * BST.cpp
 *
 *  Created on: Jul 2, 2010
 *      Author: mccain
 */

#include "BST.h"
BST::BST() : size(0), root(NULL){}

//!  Copy constructor.  Makes a complete copy of its argument
BST::BST(const BST & other){
	//BST newBST;
	if (other.root != NULL){
	 	root = Copy(other.root);
	}else{
		root = NULL;
	}
	 size = other.size;
}
BST::~BST() {
	//cerr << "deleting tree..." << endl;
	if (root != NULL){
		Free(root);
		//cerr << "deleting " << root->value << " at " << root << endl;
		delete root;
	}
}

//!  Assignment operator.  Makes a complete copy of its argument
//!  @return Reference to oneself
BST& BST::operator =(const BST & other){
	if (&other == this){
		return *this;
	}

	Clear();
	if (other.root != NULL){
		root = Copy(other.root);
	}else{
		root = NULL;
	}
	size = other.size;
	return *this;

}

//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
//!  @note This is useful for BST clients that need to traverse the tree.)
BSTNode * BST::GetRoot() const {
	return root;
}

//!  @return true if the BST is empty, or false if the BST is not empty
bool BST::IsEmpty() const{
	return size == 0;
}

//!  Removes all values from the BST
void BST::Clear(){
	if (root != NULL){
		Free(root);
		delete root;
		root = NULL;
		size= 0;
	}
}

//!  @return the number of values in the BST
int BST::GetSize() const{
	return size;
}

//!  Inserts value v into the BST
//!
//!  @param v The new value being inserted
//!
//!  @return a pointer to the newly inserted node, or NULL if v was already
//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
BSTNode * BST::Insert(const std::string & v){

	root = Insert(v, root);

	if (toAdd != NULL){
		size++;
	}
	return toAdd;
}

BSTNode * BST::Insert(const std::string & v, BSTNode* n){
	//cerr<<"...deciding";
	if (n == NULL){
		n = new BSTNode(v);
		toAdd = n;
		//cerr << "...added" << endl;
	}else if (v < n->value){
		//cerr << "...left ";
		n->left = Insert(v, n->left);
	}else if(v > n->value){
		//cerr << "...right";
		n->right = Insert(v, n->right);
	}else{
		//cerr <<"...already there."<< endl;;
		toAdd = NULL;
	}
	return n;
}

//!  Searches the tree for value v
//!
//!  @param v The new value being searched for
//!
//!  @return a pointer to the node containing v, or NULL if v is not in the tree
BSTNode * BST::Find(const std::string & v) const{

	return Find(v, root);
}

BSTNode* BST::Find(const std::string & v, BSTNode* n) const {

	if (n == NULL){
		return NULL;
	}else if (v < n->value){
		return Find(v, n->left);
	}else if (v > n->value){
		return Find(v, n->right);
	}
	return n;
}

//! @NOTE: YOU ARE NOT REQUIRED TO IMPLEMENT THE Remove METHOD BELOW
//!        (BUT YOU CAN IF YOU WANT TO)
//!
//!  Removes value v from the tree
//!
//!  @param v The value being removed from the tree
//!
//!  @return true if v was removed from the tree, or false if v was not in the tree
//bool Remove(const std::string & v);

void BST::Free(BSTNode* n){
	if (n->left != NULL){
		Free(n->left);
		//cerr << "deleting " << n->left->value << " at " << n->left<< endl;
		delete n->left;
	}
	//cerr << n->value << endl;
	if (n->right != NULL){
		Free(n->right);
		//cerr << "deleting " << n->right->value << " at " << n->right<< endl;
		delete n->right;
	}
}

BSTNode* BST::Copy (const BSTNode * n){
	BSTNode* copy = new BSTNode(*n);
	if (n->left != NULL){
		copy->left = Copy(n->left);
	}
	if (n->right != NULL){
		copy->right = Copy(n->right);
	}
	return copy;
}


