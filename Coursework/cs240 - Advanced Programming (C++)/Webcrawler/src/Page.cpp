#include "Page.h"
#include "UnitTest.h"

using namespace std;

Page::Page(URL* u, std::string d) : desc(d), url(u){}
Page::~Page(){
	delete url;
}
std::string Page::GetDesc() const{
	return desc;
}

URL* Page::GetURL() const{
	return url;
}

bool Page::Test (ostream & os){
	bool success = true;
	os << "Testing Page..." << endl;
	
	os << "\tTesting Constructor..." << endl;
	Page p(new URL("http://www.a.com/"), "studying 'A'");;
	TEST(p.desc == "studying 'A'");
	TEST(p.url->GetResolvedURL() == "http://www.a.com/");
	
	os <<"\tTesting Accessors..." << endl;
	TEST(p.GetURL()->GetResolvedURL() == "http://www.a.com/");
	TEST(p.GetDesc() == "studying 'A'");
	
	return success;
}
