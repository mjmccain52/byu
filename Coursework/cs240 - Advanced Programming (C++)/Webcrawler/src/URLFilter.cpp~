#include "URLFilter.h"
#include "UnitTest.h"
#include <iostream>

using namespace std;
URLFilter::URLFilter(URL* start, Pages* p, PageQueue* q) : scope(start), pages(p), queue(q){}
URLFilter::~URLFilter(){}
bool URLFilter::IsInScope(URL* url){

	string scopePath = scope->GetPrefix();
	string urlPath = url->GetPrefix();

	for (unsigned int i = 0; i < scopePath.length(); i++){
		if (scopePath[i] != urlPath[i]){
			return false;
		}
	}
	return true;
}
bool URLFilter::IsHTML(URL* url){
	if (url->GetScheme() != "file:" && url->GetScheme() != "http:"){
		return false;
	}
	if (url->GetPathSize() == 0){
		return true;
	}
	string file = (url->GetPath())[url->GetPathSize() - 1];
	int cutoff = file.find_first_of('?');
	if (cutoff != -1){
		file = file.substr(0, cutoff);
	}
	cutoff = file.find_first_of('.');
	if (cutoff == -1){
		return true;
	}else{
		file = file.substr(cutoff);
		if (file != ".html" && file != ".htm" && file != ".shtml" && file != ".cgi" && 
			file != ".jsp" && file != ".asp" && file != ".aspx" && file != ".php"&& 
			file != ".pl" && file != ".cfm"){
			return false;		
		}
	}
	return true;
}
bool URLFilter::IsIndexed(URL* url){
	return pages->Find(url->GetResolvedURL()) || queue->Contains(url->GetResolvedURL());
}

bool URLFilter::Test (ostream& os){
	bool success = true;
	
	os << "Testing URLFilter..." << endl;
	URL* u1 = new URL ("http://www.a.com");
	Pages* pages = new Pages();
	PageQueue* queue = new PageQueue();
	URLFilter f(u1, pages, queue);
	
	//_______________________________________________________________________
	
	os << "\tTesting IsHTML..."<< endl;
	TEST (f.IsHTML(u1));
	URL* u2 = new URL("htTp://www.a.com/b/c/d/andoffile?otherqueryjunk");
	TEST (f.IsHTML(u2));

	URL* u3 = new URL("http://www.a.com/b/c/d/andof.file?otherqueryjunk");
	TEST (!f.IsHTML(u3));

	URL* u4 = new URL("http://www.a.com/b/c/d/andoffile.php?otherqueryjunk");
	TEST (f.IsHTML(u4));
	URL* u8 = new URL("hTp://www.a.com/b/c/d/andoffile?otherqueryjunk");
	TEST (!f.IsHTML(u8));
	
	//_______________________________________________________________________
	
	os << "\tTesting IsInScope..." << endl;
	
	URL* u5 = new URL("file:///a/b/c");
	URL* u6 = new URL("http://www.a.org/a/b/c");
	
	URLFilter f2(u6, new Pages(), new PageQueue());
	URL* u7 = new URL("http://www.a.org/index");
	TEST(f.IsInScope(u2));
	TEST(f.IsInScope(u3));
	TEST(!f.IsInScope(u5));
	TEST(!f.IsInScope(u6));
	TEST(!f2.IsInScope(u7));
	
	//_______________________________________________________________________
	
	os << "\tTesting IsIndexed..." << endl;
	pages->Insert(new Page(u5, "description"));
	queue->Enqueue(u7);
	TEST(!f.IsIndexed(u2));
	TEST(f.IsIndexed(u5));
	TEST(f.IsIndexed(u7));
	
	
	delete u1;
	delete u2;
	delete u3;
	delete u4;
	delete u5;
	delete u6;
	delete u7;
	delete u8;
	
	return success;
}
