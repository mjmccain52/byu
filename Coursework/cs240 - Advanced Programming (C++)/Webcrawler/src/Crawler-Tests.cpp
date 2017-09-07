#include <iostream>
#include "WordIndex.h"
#include "PageQueue.h"
#include "OutputGenerator.h"
#include "StopWords.h"
#include "Page.h"
#include "Pages.h"
#include "URL.h"
#include "URLFilter.h"
#include "Webcrawler.h"
#include "PageDownloader.h"

#include "HTMLParser.h"
using namespace std;

int main (){
	bool success = true;
	
	if (!PageDownloader::Test(cout)){success = false;}
	if (!URL::Test(cout)){success = false;}
	if (!Occurrences::Test(cout)){success = false;}
	if (!WordIndex::Test(cout)){success = false;}
	if (!PageQueue::Test(cout)){success = false;}
	if (!Page::Test(cout)){success = false;}
	if (!Pages::Test(cout)){success = false;}
	if (!StopWords::Test(cout)){success = false;}
	if (!OutputGenerator::Test(cout)){success = false;}
	if (!URLFilter::Test(cout)){success = false;}
	if (!HTMLParser::Test(cout)){success = false;}
	if (!Webcrawler::Test(cout)){success = false;}
	
	
	if (success){
		cout << "Tests succeeded." << endl;
	} else{
		cout << "Tests failed." << endl;
	}
	
	return 0;
}
