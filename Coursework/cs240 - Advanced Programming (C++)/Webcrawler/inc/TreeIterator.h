#ifndef CS240_TREE_ITERATOR_H
#define CS240_TREE_ITERATOR_H

#include "Pages.h"

class StackNode{
	friend class TreeStack;
	StackNode(PageNode* n, StackNode* s) : v(n), next(s){}
	PageNode* v;
	StackNode* next;
};

class TreeStack{
	friend class TreeIterator;
public:
	TreeStack (){
		count = 0;
		top = NULL;
	}
	~TreeStack(){
		Empty();
	}
	int Size(){
		return count;
	}
	bool IsEmpty(){
		return count == 0;
	}
	bool Push(PageNode* n){
		StackNode* temp = new StackNode(n, top);
		top = temp;
		count++;
		return true;
	}
	PageNode* Pop(){
		if (top == NULL){
			return NULL;
		}
		PageNode* temp = top->v;
		StackNode* garbage = top;
		top = top->next;
		delete garbage;
		count--;
		return temp;
	}
	bool Empty(){
		while (top != NULL){
			StackNode* garbage = top;
			top = top->next;
			delete garbage;
		}
		count = 0;
		return true;
	}
private:
	StackNode* top;
	int count;
	
	
};

class TreeIterator{
public:
	TreeIterator(Pages& tree);
	bool HasNext();
	PageNode* Next();
private:
	TreeStack stack;
	Pages pages;
};

#endif
