#include "WordIndex.h"
#include "UnitTest.h"
#include "StringUtil.h"
using namespace std;

WordIndex::WordIndex() : root(NULL), size(0){}

WordIndex::~WordIndex(){
	if (root != NULL){
		
		Free(root);
		delete root;
	}
}

WIMapNode * WordIndex::GetRoot() const{
	return root;
}

bool WordIndex::IsEmpty() const{
	return size == 0;
}

void WordIndex::Clear(){
	if (root != NULL){
		Free(root);
		delete root;
		root = NULL;
		size= 0;
	}
}

int WordIndex::GetSize() const{
	return size;
}

WIMapNode * WordIndex::Insert(const std::string & v, URL* const url){
	root = Insert(v, url, root);

	return toAdd;
}

WIMapNode * WordIndex::Insert(const std::string & v, URL* const url, WIMapNode* n){
	if (n == NULL){
		n = new WIMapNode(v);
		n->GetOccurrences()->Insert(url);
		toAdd = n;
		size++;
	}else if (v < n->wordKey){
		n->left = Insert(v, url, n->left);
	}else if(v > n->wordKey){
		n->right = Insert(v, url, n->right);
	}else{
		n->GetOccurrences()->Insert(url);
		toAdd = n;
	}
	return n;
}

/*void WordIndex::AddIndex(const std::string & word, const std::string & url){
	WIMapNode* temp = Find(word);
	if (temp == NULL){
		temp = Insert(word);
		temp->GetOccurrences()->Insert(url);
	} else{
		OccMapNode* temp2 = temp->Find(url);
		if (temp2 == NULL){
			temp->Insert(url);
		} else {
			temp2->Increment();
		}
	}
}*/

WIMapNode * WordIndex::Find(const std::string & v) const{
	return Find(v, root);
}

WIMapNode* WordIndex::Find(const std::string & v, WIMapNode* n) const{
	if (n == NULL){
		return NULL;
	}else if (v < n->wordKey){
		return Find(v, n->left);
	}else if (v > n->wordKey){
		return Find(v, n->right);
	}
	return n;
}

void WordIndex::Free(WIMapNode* n){
	if (n->left != NULL){
		Free(n->left);
		delete n->left;
	}
	if (n->right != NULL){
		Free(n->right);
		delete n->right;
	}
}

WordIndex::IndexIterator* WordIndex::Iterator(){
	return new IndexIterator(root); 
}

bool WordIndex::Test(std::ostream & os){
	bool success = true;
	
	os<<"Testing WordIndex..."<<endl;
	
	os<<"\tTesting WIMapNode..."<<endl;
	WIMapNode* node1 = new WIMapNode("1");
	node1->right = new WIMapNode("2");
	TEST(node1->GetWordKey()=="1");
	TEST(node1->GetOccurrences()!=NULL);
	TEST(node1->GetLeft()== NULL);
	TEST(node1->GetRight()->GetWordKey()=="2");
	delete node1->right;
	delete node1;
	
	//________________________________________________________________
	
	os<<"\tTesting Constructor... " << endl;
	WordIndex wi;
	TEST(wi.root == NULL);
	TEST(wi.size == 0);
	
	//________________________________________________________________
	
	os<<"\tTesting Insert (Occurrences Integration)... "<<endl;
	string str = "even";
	URL* u = new URL ("www.a.com");
	wi.Insert(str, u);
	wi.Insert("baby", u);
	wi.Insert("great", new URL("www.a.com"));
	wi.Insert("fall", new URL("www.a.com"));
	wi.Insert(str, u);
	wi.Insert("fall", new URL("www.b.com"));
	wi.Insert("fall", new URL("www.a.com"));
	TEST(wi.size == 4);
	TEST(wi.root->wordKey == "even");
	TEST(wi.root->occMap != NULL);
	TEST(wi.root->occMap->GetSize() == 1);
	TEST(wi.root->occMap->GetRoot()->GetCountValue() == 2);
	TEST(wi.root->right->left->occMap->GetSize() == 2);
	TEST(wi.root->right->left->occMap->GetRoot()->GetCountValue() == 2);
	
	//________________________________________________________________
	
	os <<"\tTesting Iterator... " << endl;
	IndexIterator* i = wi.Iterator();
	TEST (i->Next()->wordKey == "baby");
	TEST (i->Next()->wordKey == "even");
	TEST (i->Next()->wordKey == "fall");
	TEST (i->Next()->wordKey == "great");
	TEST (!i->HasNext());
	
	delete i;
	return success;
}
