#include "PageQueue.h"
#include "UnitTest.h"
#include<iostream>
using namespace std;

PageQueue::PageQueue() : size(0), front(NULL), back(NULL){}

PageQueue::~PageQueue(){
	Free();
}

bool PageQueue::IsEmpty() const{
	return size == 0;
}

void PageQueue::Clear(){
	Free();
}

int PageQueue::GetSize() const{
	return size;
}

void PageQueue::Enqueue(URL* const u){
	PQNode* newGuy = new PQNode(u, NULL, back);
	if (back != NULL){
		back->prev = newGuy;
	}else{
		front = newGuy;
	}
	back = newGuy;
	size++;
}

bool PageQueue::Contains(const std::string u) const{

	PQNode* curr = front;
	while (curr != NULL) {
		if (curr->url->GetResolvedURL() == u){
			return true;
		}
		curr = curr->prev;
	}
	return false;

}

URL* PageQueue::Peek(){
	return front->url;
}

URL* PageQueue::Serve(){
	PQNode* toDelete = front;
	URL* toReturn = toDelete->url;
	front = toDelete->prev;
	delete toDelete;
	if (front != NULL){
		front->next = NULL;
	}else{
		back = NULL;
	}
	size--;
	return toReturn;
}
void PageQueue::Free(){
	PQNode* curr = front;
	PQNode* temp;
	while (curr != NULL) {
		temp = curr->prev;
		delete curr;
		curr = temp;
	}
	front = NULL;
	size = 0;
}
bool PageQueue::Test(std::ostream & os){
	bool success = true;
	
	os<<"Testing PageQueue..."<<endl;
	
	os<<"\tTesting PQNode..."<<endl;
	URL* u1 = new URL("file:///1");
	URL* u2 = new URL("file:///2");
	PQNode* node = new PQNode(u1);
	node->next = new PQNode(u2);
	TEST(node->GetURL()->GetResolvedURL() == "file:///1");
	TEST(node->GetNext()->GetURL()->GetResolvedURL() == "file:///2");
	TEST(node->GetPrevious() == NULL);
	delete node->next;
	delete node;
	delete u1;
	delete u2;
	
	os << "\tTesting Constructor..." << endl;
	PageQueue pq;
	TEST(pq.size == 0);
	TEST(pq.front == NULL);
	TEST(pq.back == NULL);
	
	os << "\tTesting Enqueue..." << endl;
	pq.Enqueue(new URL("file:///first"));
	TEST(pq.front->url->GetResolvedURL() == "file:///first" && pq.back->url->GetResolvedURL() == "file:///first");
	TEST(pq.size == 1);
	pq.Enqueue(new URL("file:///second"));
	TEST(pq.front->url->GetResolvedURL() == "file:///first" && pq.back->url->GetResolvedURL() == "file:///second");
	TEST(pq.size == 2);
	pq.Enqueue(new URL("file:///third"));
	TEST(pq.front->url->GetResolvedURL() == "file:///first" && pq.back->url->GetResolvedURL() == "file:///third");
	TEST(pq.size == 3);
	
	os << "\tTesting Peek..." << endl;
	TEST(pq.Peek()->GetResolvedURL() == "file:///first");
	
	os << "\tTesting Serve..." << endl;
	TEST(pq.Serve()->GetResolvedURL() == "file:///first");
	TEST(pq.size == 2);
	TEST(pq.front->url->GetResolvedURL() == "file:///second");
	TEST(pq.Serve()->GetResolvedURL() == "file:///second");
	TEST(pq.size == 1);
	TEST(pq.front->url->GetResolvedURL() == "file:///third");
	TEST(pq.Serve()->GetResolvedURL() == "file:///third");
	TEST(pq.size == 0);
	TEST(pq.front == NULL);
	pq.Enqueue(new URL("file:///fourth"));
	TEST(pq.front->url->GetResolvedURL() == "file:///fourth" && pq.back->url->GetResolvedURL() == "file:///fourth");
	return success;
}
