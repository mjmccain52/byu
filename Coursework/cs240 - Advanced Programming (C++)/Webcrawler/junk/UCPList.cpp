
#include "UCPList.h"
#include <cstdlib>
#include <iostream>

//! LinkedList implements a doubly-linked list

//!  No-arg constructor.  Initializes an empty linked list
UCPList::UCPList() : size(0), first(NULL), last(NULL){}

//!  Destructor
UCPList::~UCPList(){}

//!  @return true if the list is empty, or false if the list is not empty
bool UCPList::IsEmpty() const{
	return size == 0;
}


//!  Removes all values from the list
void UCPList::Clear(){
	Free();
}


//!  @return the number of values in the list
int UCPList::GetSize() const{
	return size;
}

//!  @return a pointer to the first node in the list, or NULL if the list is empty
LLNode * UCPList::GetFirst()const{ 
	return first;
}

//!  @returns a pointer to the last node in the list, or NULL if the list is empty
LLNode * UCPList::GetLast()const{
	return last;}


//!  Inserts value v into the list after node n
//!  
//!  @param v The new value being inserted
//!  @param n A node that is already in the list after which the new node should 
//!      be inserted.
//!      If n is NULL, the new node should be inserted at the beginning of the list.
//!
//!  @return a pointer to the newly inserted node
LLNode * UCPList::Insert(URLCountPair* const v, LLNode * n){
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
LLNode * UCPList::Find(URLCountPair* const v, LLNode * n) const{return NULL;}


//!  Removes node n from the list
//!  
//!  @param n The node being removed from the list
void UCPList::Remove(LLNode * n){}


void UCPList::Free(){}

