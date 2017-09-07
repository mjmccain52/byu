#ifndef CS240_URL_FILTER_H
#define CS240_URL_FILTER_H

#include "Pages.h"
#include "PageQueue.h"
//! URLFilter contains a couple checks to be sure we want to work with a particular URL
class URLFilter{
public:
	URLFilter(URL* start, Pages* p, PageQueue* q);
	~URLFilter();
	//! Makes sure the url is within the scope of Webcrawler
	//! @param url the url to be checked
	bool IsInScope(URL* url);
	//! Makes sure the url is an html file
	//! @param url the url to be checked
	bool IsHTML(URL* url);
	//! checks the list of AccessedPages to see if the url is already in there.
	//! @param url the url to be checked
	bool IsIndexed(URL* url);
	static bool Test (std::ostream& os);
private:
	URL* scope;
	Pages* pages;
	PageQueue* queue;
};
#endif
