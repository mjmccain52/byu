#include "Pages.h"
#include "UnitTest.h"

using namespace std;

Pages::Pages() : root(NULL), size(0){}

Pages::~Pages(){
	if (size > 0){
		Free(root);
		delete root;
	}
}

void Pages::Clear(){
	if (root != NULL){
		Free(root);
		delete root;
		root = NULL;
		size= 0;
	}
}
PageNode * Pages::GetRoot() const{
	return root;
}

bool Pages::IsEmpty() const{
	return size == 0;
}

int Pages::GetSize() const{
	return size;
}

PageNode * Pages::Insert(Page* const p){
	root = Insert(p, root);

	if (toAdd != NULL){
		size++;
	}
	return toAdd;
}

PageNode * Pages::Insert(Page* const p, PageNode* n){
	//cerr<<"...deciding";
	if (n == NULL){
		n = new PageNode(p);
		toAdd = n;
		//cerr << "...added" << endl;
	}else if (p->GetURL()->GetResolvedURL() < n->page->GetURL()->GetResolvedURL()){
		//cerr << "...left ";
		n->left = Insert(p, n->left);
	}else if(p->GetURL()->GetResolvedURL() > n->page->GetURL()->GetResolvedURL()){
		//cerr << "...right";
		n->right = Insert(p, n->right);
	}else{
		cerr <<"SOMEBODY'S POISONED THE WATERHOLE!"<< endl;;
		toAdd = NULL;
	}
	return n;
}


bool Pages::Find(const std::string & url) const{ 
	return Find(url, root);	
}

bool Pages::Find(const std::string & url, PageNode* n) const{
	if (n == NULL){
		return false;
	}else if (url < n->page->GetURL()->GetResolvedURL()){
		return Find(url, n->left);
	}else if (url > n->page->GetURL()->GetResolvedURL()){
		return Find(url, n->right);
	}
	return true;
	
}

void Pages::Free(PageNode* n){
	if (n->left != NULL){
		Free(n->left);
		//cerr << "deleting " << n->left->stopWord << " at " << n->left<< endl;
		delete n->left;
	}
	//cerr << n->stopWord << endl;
	if (n->right != NULL){
		Free(n->right);
		//cerr << "deleting " << n->right->stopWord << " at " << n->right<< endl;
		delete n->right;
	}
}

Pages::TreeIterator* Pages::Iterator(){
	return new TreeIterator(root); 
}
bool Pages::Test(std::ostream & os){

	bool success = true;
	os << "Testing Pages..." << endl;
	
	os<<"\tTesting PageNode..."<<endl;
	PageNode* node = new PageNode(new Page(new URL("http://www.1.com/"), "hi"));
	node->right = new PageNode(new Page(new URL("http://www.2.com/"), "ho"));
	TEST(node->GetPage()!= NULL);
	TEST(node->GetPage()->GetURL()->GetResolvedURL() == "http://www.1.com/");
	TEST(node->GetLeft()== NULL);
	TEST(node->GetRight()->GetPage()->GetURL()->GetResolvedURL() =="http://www.2.com/");
	delete node->right;
	delete node;
	
	os<<"\tTesting Constructor... "<<endl;
	Pages p;
	TEST(p.root == NULL);
	TEST(p.size == 0);
	
	os<<"\tTesting Insert... " << endl;
	p.Insert(new Page (new URL("http://www.e.com/"), "hi"));
	p.Insert(new Page (new URL("http://www.a.com/"), "ha"));
	p.Insert(new Page (new URL("http://www.b.com/"), "ho"));
	p.Insert(new Page (new URL("http://www.g.com/"), "he"));
	p.Insert(new Page (new URL("http://www.f.com/"), "hum"));

	TEST(p.GetSize() == 5);
	TEST(p.root->page->GetURL()->GetResolvedURL() == "http://www.e.com/");
	TEST(p.root->left->page->GetURL()->GetResolvedURL() == "http://www.a.com/");
	TEST(p.root->right->left->page->GetURL()->GetResolvedURL() == "http://www.f.com/");
	TEST(p.root->left->right->page->GetURL()->GetResolvedURL() == "http://www.b.com/");
	
	
	os << "\tTesting Iterator... " << endl;
	TreeIterator* t = p.Iterator();
	TEST (t->Next()->GetURL()->GetResolvedURL() == "http://www.a.com/");
	TEST (t->Next()->GetURL()->GetResolvedURL() == "http://www.b.com/");
	TEST (t->Next()->GetURL()->GetResolvedURL() == "http://www.e.com/");
	TEST (t->Next()->GetURL()->GetResolvedURL() == "http://www.f.com/");
	TEST (t->Next()->GetURL()->GetResolvedURL() == "http://www.g.com/");
	
	TEST(!t->HasNext());
	delete t;
	os << "\tTesting Clear... " << endl;
	p.Clear();
	TEST(p.root == NULL);
	TEST(p.size == 0);
	
	return success;
}
