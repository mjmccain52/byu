#include <iostream>
#include "LinkedList.h"
using namespace std;

int main(){

	LinkedList tree;
	tree.Insert("hi", NULL);
	cerr << tree.GetFirst()->GetValue()<< endl;
	//tree.Insert("ho", NULL);
	//tree.Insert("ha", NULL);
	
	LinkedList t(tree);

	return 0;
}
