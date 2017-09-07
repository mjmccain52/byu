#include "HTMLParser.h"
#include "HTMLTokenizer.h"
#include "HTMLToken.h"
#include "StringUtil.h"
#include <iostream>
#include <sstream>
#include "OutputGenerator.h"
#include "UnitTest.h"
#include <ctype.h>
#include "CS240Exception.h"
using namespace std;
HTMLParser::HTMLParser( string stopsFilename, URLFilter* f, PageQueue* q, Pages* p, WordIndex* i){
	boring.LoadSWFile(stopsFilename);
	filter = f;
	queue = q;
	pages = p;
	index = i;
}

void HTMLParser::ParseHTML(string& code, URL* url){
	this->url = url;
	desc = "";
	haveDesc = false;
	script = false;
	getDesc = false;
	parsing = false;
	charCount = 0;
	string value = "";
	
	HTMLTokenizer tokener(code);
	
	while (tokener.HasNextToken()){
		try{
			HTMLToken current(tokener.GetNextToken());
			value = current.GetValue();
			if (current.GetType() == TAG_END){
				EndTag(value);
			}else if (current.GetType() == COMMENT || script){
				continue;
			}else if (current.GetType() == TAG_START){
				StartTag(value);
			}else if (current.GetType() == TEXT && parsing){
				Text(value);
			}
			if (current.GetType() == TAG_START && (value == "a" || value == "A")){
				string link;
				link = current.GetAttribute("href");
				if (link.length() > 0){
					AddLink(link, url);
				}
			}
		}
		catch (CS240Exception& e){
			cout << e.GetMessage() << endl;
		}
		
	}
	pages->Insert(new Page(url, desc));
}
void HTMLParser::StartTag (std::string value){
	StringUtil::ToLower(value);
	if (value == "script"){
		script = true;
		return;
	}
	if ((value == "title" || IsHeader(value)) && !haveDesc){
		getDesc = true;
	}
	if (value == "title" || value == "body"){
		parsing = true;
	}	
}

void HTMLParser::EndTag (std::string value){
	StringUtil::ToLower(value);
	if (value == "script"){
		script = false;
		return;
	}

	if (value == "title" || value == "body"){
		parsing = false;
	}
	
}

void HTMLParser::Text(const std::string& value){
	bool wording = false;
	bool badWord = false;
	bool singleSpace = false;
	string word = "";
	if (getDesc){
		desc = value;
		haveDesc = true;
		getDesc = false;
	}
	for (unsigned int i = 0; i < value.length(); i++){
		//cout << value[i] << ":";
		if (!isspace(value[i]) && charCount < 100 && !haveDesc){
			desc += value[i];
			charCount++;
			singleSpace = false;
		}
		if (isspace(value[i]) && charCount < 100 && !haveDesc && !singleSpace){
			desc += " ";
			singleSpace = true;
		}
		if (!IsAlphabetic(value[i]) && IsValidChar(value[i]) && !wording){
			badWord = true;
		}
		if (IsAlphabetic(value[i]) && !wording && !badWord){
			wording = true;
		}
		if (IsValidChar(value[i]) && wording){
			word += value[i];
		}
		if ((isspace(value[i]) || !IsValidChar(value[i])) && !wording){
			badWord = false;
		}
		if ((isspace(value[i]) || !IsValidChar(value[i]) || i == value.length() - 1)  && wording){
			wording = false;
			//cout << word << endl;
			Index(word);		
			word = "";
		}
	}
}

void HTMLParser::Index(string word){
	StringUtil::ToLower(word);
	if (!boring.IsStopWord(word) && word != ""){
		index->Insert(word, url);
	}
}
bool HTMLParser::IsAlphabetic(char c){
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool HTMLParser::IsValidChar(char c){
	return IsAlphabetic(c) || (c >= '0' && c <= '9') || c == '-' || c == '_';
}

bool HTMLParser::IsHeader(string text){
	return text[0] == 'h' && text[1] >= '1' && text[1] <= '9' && text.length() == 2;
}

void HTMLParser::AddLink(string link, URL* base){
	URL* temp = new URL(link, base->GetResolvedURL());
	try{
		temp->Redirect();
		if (filter->IsInScope(temp) && filter->IsHTML(temp) && !filter->IsIndexed(temp) 
			&& temp->GetResolvedURL() != base->GetResolvedURL()){
			queue->Enqueue(temp);
		}else{
			delete temp;
		}
	}
	catch (CS240Exception& e){
		delete temp;
	}
	
}
bool HTMLParser::Test(ostream& os){
	bool success = true;
	os << "Testing HTMLParser..." << endl;
	PageQueue* queue = new PageQueue();
	URL* u1 = new URL ("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawlindex.html");
	URL* u3 = new URL("file:///users/ta/cs240ta/webcrawler/file/student/linktests/absolute.html");
	
	URL* u5 = new URL("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/testFive.html");

	Pages* pages = new Pages();
	WordIndex* index = new WordIndex;
	URLFilter* filter = new URLFilter(u1, pages, queue);

	HTMLParser parser("test/stopword.txt", filter, queue, pages, index);
	
	
	os << "\tTesting Constructor..." << endl;
	TEST(filter != NULL && pages != NULL && queue != NULL && index != NULL);
	parser.url = u1;
	
	//---------------------------------------------
	
	os << "\tTesting IsAlphabetic..." << endl;
	TEST(parser.IsAlphabetic('a'));
	TEST(parser.IsAlphabetic('z'));
	TEST(parser.IsAlphabetic('A'));
	TEST(parser.IsAlphabetic('z'));
	TEST(parser.IsAlphabetic('m'));
	TEST(parser.IsAlphabetic('M'));
	TEST(!parser.IsAlphabetic('1'));
	TEST(!parser.IsAlphabetic('_'));
	TEST(!parser.IsAlphabetic(' '));
	TEST(!parser.IsAlphabetic('%'));
	TEST(!parser.IsAlphabetic('~'));
	TEST(!parser.IsAlphabetic('0'));
	
	//---------------------------------------------
	
	os << "\tTesting IsValidChar..." << endl;
	TEST(parser.IsValidChar('1'));
	TEST(parser.IsValidChar('a'));
	TEST(parser.IsValidChar('Z'));
	TEST(parser.IsValidChar('-'));
	TEST(parser.IsValidChar('_'));
	TEST(parser.IsValidChar('0'));
	TEST(!parser.IsValidChar('&'));
	TEST(!parser.IsValidChar('!'));
	TEST(!parser.IsValidChar('.'));
	TEST(!parser.IsValidChar('?'));
	TEST(!parser.IsValidChar('('));
	
	//---------------------------------------------
	
	os << "\tTesting IsHeader..." << endl;
	TEST(parser.IsHeader("h1"));
	TEST(parser.IsHeader("h9"));
	TEST(!parser.IsHeader("h0"));
	TEST(!parser.IsHeader("h10"));
	TEST(!parser.IsHeader("h"));
	TEST(!parser.IsHeader("h20"));
	TEST(!parser.IsHeader("p1"));
	
	//---------------------------------------------
	
	os << "\tTesting StartTag..." << endl;
	parser.StartTag("script");
	TEST(parser.script);
	parser.StartTag("title");
	TEST(parser.getDesc && parser.parsing);
	parser.getDesc = false;
	parser.parsing = false;
	parser.haveDesc = true;
	parser.StartTag("TITLE");
	TEST(!parser.getDesc);
	parser.haveDesc = false;
	parser.StartTag("h3");
	TEST(parser.getDesc);
	parser.getDesc = false;
	
	//---------------------------------------------
	
	os << "\tTesting EndTag..." << endl;
	parser.EndTag("body");
	TEST(!parser.parsing);
	parser.EndTag("SCRIPT");
	TEST(!parser.script);
	
	//---------------------------------------------
	
	os << "\tTesting AddLink..." << endl;
	URL* u4 = new URL("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/makefile.php");
	
	parser.AddLink("http://STUDENTS.CS.BYU.edu/~cs240ta/crawler_tests/crawler/valid.asp", u5);
	parser.AddLink("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/makefile.php#comments", u4);
	parser.AddLink("crawler/TestOne.html", u1);
	TEST(queue->GetSize() == 2);
	parser.AddLink("crawler/TestOne.html", u1);
	TEST(queue->GetSize() == 2);
	parser.AddLink("crawler/testTwo.html", u1);
	TEST(queue->GetSize() == 3);
	parser.AddLink("file:///users/ta/cs240ta/webcrawler/file/student/linktests/absolute1.html", u3);
	TEST(queue->GetSize() == 3);
	queue->Clear();
	
	//---------------------------------------------
	
	os <<"\tTesting Index..." << endl;
	parser.Index("Michael");
	TEST (index->GetSize() == 1);
	TEST (index->GetRoot()->GetWordKey() == "michael");
	parser.Index("the");
	TEST(index->GetSize() == 1);
	
	//---------------------------------------------
	
	os << "\tTesting Text..." << endl;
	parser.getDesc = true;
	parser.Text("A fairly mild string");
	TEST(parser.desc == "A fairly mild string");
	TEST(!parser.getDesc && parser.haveDesc);
	TEST(index->GetSize() == 4);
	parser.Text("  A  More-Robust  \tString");
	TEST(index->GetSize() == 5);
	parser.Text("\"quotes\"  Mike's 'fun'-time");
	TEST(index->GetSize() == 8);
	
	parser.Text("!Really complex&naughty  1a3\nString");
	TEST(index->GetSize() == 11);
	index->Clear();
	
	parser.Text("Special&cedil;Characters&#60;entities&gt;Should&#174;also&#178;seperate&#172;words&amp;sentences&iexcl;");
	TEST(index->GetSize() == 10);
	parser.haveDesc = false;
	parser.desc = "";
	parser.charCount = 0;
	parser.Text("!longandcomplicated   \n!stringtodeterminewhetherthe !descriptionisworking !longandcomplicated !stringtodeterminewhetherthe !descriptionisworking");
	TEST(parser.desc.length() == 104);	
	
	index->Clear();
	
	//---------------------------------------------
	
	os << "\tTesting ParseHTML..." << endl;
	string html = "<html><head><script>alert('hi there!');</script></head><body>\nMy name is <h1>Frank</h1> and i'm a kangaroo&This is the story of a guy named al and he lived in the sewer with his hamster pal.</body></html>";
	
	parser.ParseHTML(html, u1);

	TEST(pages->GetRoot()->GetPage()->GetDesc() == "Frank");
	TEST(index->GetSize() == 12);

	
	html = "<html><head><title>Frank's Story</title></head><body>My name<a target ='main' href='fine.html'> is</a> <h1><A href='../crawler/question.html'>Frank</A></h1> and i'm a kangaroo&This is the story of a guy named al and he lived in the sewer with his hamster pal.</body></html>";
	URL* u2 = new URL("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/TestOne.html");
	u2->Redirect();
	parser.ParseHTML(html, u2);
	
	TEST(pages->GetRoot()->GetLeft()->GetPage()->GetDesc() == "Frank's Story");
	TEST(index->GetSize() == 12);
	TEST(queue->GetSize() == 2);
	delete queue;
	delete pages;
	delete filter;
	delete index;
	
	return success;
}

