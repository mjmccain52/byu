#include "TreeIterator.h"

TreeIterator::TreeIterator(Pages& tree) : pages(tree){}

bool TreeIterator::HasNext(){
	return stack.IsEmpty() && !tree.IsEmpty();
}
PageNode* TreeIterator::Next(){return NULL;}
