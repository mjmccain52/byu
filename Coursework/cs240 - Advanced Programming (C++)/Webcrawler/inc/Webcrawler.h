#ifndef CS240_WEBCRAWLER_H
#define CS240_WEBCRAWLER_H

#include "StopWords.h"
#include "OutputGenerator.h"
#include "HTMLParser.h"
#include "PageDownloader.h"

class Webcrawler{
public:
	Webcrawler(const std::string& start, const std::string& output, const std::string& stops);
	~Webcrawler();
	bool Crawl();
	//! uses the output generator to create an xml file
	void GetXML();
	static bool Test(std::ostream& os);
private:
	//!An array of all the stop words.  Binary search will be used to determine if a word is in here.
	URL* base;
	StopWords* stopWords;
	WordIndex* theGrandIndex;
	Pages* pages;
	PageQueue* queue;
	OutputGenerator* outputGenerator;
	HTMLParser* parser;
	URLFilter* filter;
	PageDownloader downloader;
	std::string outfile;
	
	
};
#endif
