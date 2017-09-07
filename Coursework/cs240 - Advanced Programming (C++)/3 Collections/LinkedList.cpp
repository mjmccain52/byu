#include "LinkedList.h"
#include <string>
#include <iostream>
using namespace std;

//!  No-arg constructor.  Initializes an empty linked list
LinkedList::LinkedList() : size(0), first(NULL), last(NULL){}


//!  Copy constructor.  Makes a complete copy of its argument
LinkedList::LinkedList(const LinkedList & other){
	size = 0;
	//cerr << "size check: " << size << endl;
	Copy(other);
}


//!  Destructor
LinkedList::~LinkedList(){
	Free();
}


//! Assignment operator.  Makes a complete copy of its argument
//! @return A reference to oneself
LinkedList& LinkedList::operator =(const LinkedList & other){
	if (&other == this){
		return *this;
	}
	Copy(other);
	return *this;
}


//!  @return true if the list is empty, or false if the list is not empty
bool LinkedList::IsEmpty() const {
	return size == 0;
}


//!  Removes all values from the list
void LinkedList::Clear(){
	Free();
}


//!  @return the number of values in the list
int LinkedList::GetSize() const {
	return size;
}

//!  @return a pointer to the first node in the list, or NULL if the list is empty
LLNode * LinkedList::GetFirst()const {
	return first;
}



//!  @returns a pointer to the last node in the list, or NULL if the list is empty
LLNode * LinkedList::GetLast()const {
	return last;
}


//!  Inserts value v into the list after node n
//!  
//!  @param v The new value being inserted
//!  @param n A node that is already in the list after which the new node should 
//!      be inserted.
//!      If n is NULL, the new node should be inserted at the beginning of the list.
//!
//!  @return a pointer to the newly inserted node
LLNode * LinkedList::Insert(const std::string & v, LLNode * n){
	LLNode* newGuy;
	if (n != NULL){
		newGuy = new LLNode(v, n, n->next);
		if (n->next == NULL){
			last = newGuy;
		}else{
			n->next->prev = newGuy;
		}
		n->next = newGuy;
	}else{
		newGuy = new LLNode (v, NULL, first);
		if (first != NULL){
			first->prev = newGuy;
		}
		first = newGuy;
		if (last == NULL){
			last = newGuy;
		}
	}
	/*if (newGuy->next == NULL){
		last = newGuy;
	}*/
	size++;
	return newGuy;
}


//! Searches for the first occurrence of value v that appears in the list 
//!   after node n
//!   
//!  @param v The value being searched for
//!  @param n The node in the list after which the search should begin.
//!      If n is NULL, the list should be searched from the beginning.
//!
//!  @return a pointer to the node containing v, or NULL if v is not found
LLNode * LinkedList::Find(const std::string & v, LLNode * n) const{
	LLNode* curr;
	if (n == NULL){
		curr = first;
	}else{
		curr = n->next;
	}
	while (curr != NULL){
		if (curr->value == v){
			return curr;
		}
		curr = curr->next;
	}	
	return NULL;
}


//!  Removes node n from the list
//!  
//!  @param n The node being removed from the list
void LinkedList::Remove(LLNode * n){
	if (size == 0){
		return;
	}
	if (n->next == NULL){
		last = n->prev;
	}else{
		n->next->prev = n->prev;
	}
	if (n->prev == NULL){
		first = n->next;
	}else{
		n->prev->next = n->next;
	}
	size--;
	delete n;
}

void LinkedList::Free(){
	LLNode* curr = first;
	LLNode* temp;
	while (curr != NULL) {
		temp = curr->next;
		//cerr << "deleting " << curr->value << " at " << curr << endl;
		delete curr;
		curr = temp;
	}
	first = NULL;
	last = NULL;
	size = 0;
}
void LinkedList::Copy(const LinkedList & other){
	if (size > 0){
		//cerr << size << endl;
		Free();
	}
	first = NULL;
	last = NULL;
	if (other.size == 0){
		size = 0;	
		return;
	}
	first = new LLNode (other.first->value, NULL, NULL);
	LLNode* currThis = first;
	LLNode* currOther = other.first;
	while (currOther->next != NULL){
		currThis->next = new LLNode(currOther->next->value, currThis, NULL);
		currThis = currThis->next;
		currOther = currOther->next;
	}
	last = currThis;
	size = other.size;
}
