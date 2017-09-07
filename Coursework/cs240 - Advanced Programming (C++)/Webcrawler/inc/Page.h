#ifndef CS240_PAGE_H
#define CS240_PAGE_H

#include <iostream>
#include "URL.h"
//! A value object which holds some basic information about a webpage
class Page{
public:
	//! Constructor
	//! @param u, d The url and description to be stored
	Page(URL* u, std::string d);
	~Page();
	
	//!Accessors
	std::string GetDesc() const;
	URL* GetURL() const;
	
	static bool Test(std::ostream & os);
private:
	std::string desc; // description of the page
	URL* url; //URL of the page.
};
#endif
