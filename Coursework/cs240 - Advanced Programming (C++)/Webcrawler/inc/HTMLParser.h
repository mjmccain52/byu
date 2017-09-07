#ifndef CS240_HTML_PARSER_H
#define CS240_HTML_PARSER_H

#include "Pages.h"
#include "WordIndex.h"
#include "StopWords.h"
#include "URLFilter.h"

//! Parses the description, links, and words from an HTML file.
class HTMLParser{
public:
	HTMLParser(std::string stopsFilename, URLFilter* f, PageQueue* q, Pages* p, WordIndex* i);
	//! Parses an HTML page looking for the description and links
	//! @param code A string containing all the code from the html file
	//! @return A Page object containing the descriptions and links of the file parsed
	void ParseHTML (std::string& code, URL* url);
	static bool Test(std::ostream& os);
	
private:
	//! Parses text and inserts words into the grand index
	void ParseText(std::string text, URL* url);
	void AddLink(std::string link, URL* base);
	void Index(std::string word);
	void StartTag (std::string value);
	void EndTag (std::string value);
	void Text (const std::string& value);
	bool IsAlphabetic(char c);
	bool IsValidChar(char c);
	bool IsHeader(std::string text);
	bool IsWhiteSpace(char c);
	StopWords boring;
	URLFilter* filter;
	PageQueue* queue;
	Pages* pages;
	WordIndex* index;
	URL* url;
	bool script;
	bool getDesc;
	bool parsing;
	bool haveDesc;
	int charCount;
	std::string desc;
	


};
#endif
