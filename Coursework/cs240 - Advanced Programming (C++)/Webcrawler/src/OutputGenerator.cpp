#include "OutputGenerator.h"
#include "UnitTest.h"
#include "StringUtil.h"
#include <fstream>
using namespace std;

OutputGenerator::OutputGenerator(){}

OutputGenerator::~OutputGenerator(){}

void OutputGenerator::generateXMLFile(const std::string & filename, const std::string & start, 
							Pages& pages, WordIndex& index){
	ofstream xmlFile;
	xmlFile.open(filename.c_str());
	
	xmlFile << "<website>" ;
	xmlFile << "<start-url>" ;
	xmlFile << StringUtil::EncodeToXmlCopy(start) ;
	xmlFile << "</start-url>" ;
	xmlFile << "<pages>" ;
	Pages::TreeIterator* t = pages.Iterator();
	while (t->HasNext()){
		xmlFile << "<page>" ;
		Page* current = t->Next();
		xmlFile << "<url>";
		xmlFile << StringUtil::EncodeToXmlCopy(current->GetURL()->GetResolvedURL());
		xmlFile << "</url>";
		xmlFile << "<description>";
		xmlFile << StringUtil::EncodeToXmlCopy(current->GetDesc());
		xmlFile << "</description>";
		xmlFile << "</page>" ;
	}
	delete t;
	xmlFile << "</pages>" ;
	xmlFile << "<index>" ;
	WordIndex::IndexIterator* i = index.Iterator();
	while (i->HasNext()){
		WIMapNode* current = i->Next();
		xmlFile << "<word>" ;
		xmlFile << "<value>" ;
		xmlFile << current->GetWordKey() ;
		xmlFile << "</value>" ;
		Occurrences::OccIterator* oi = current->GetOccurrences()->Iterator();
		while (oi->HasNext()){
			xmlFile << "<occurrence>" ;
			OccMapNode* currOcc = oi->Next();
			xmlFile << "<url>" ;
			xmlFile << currOcc->GetUrlKey()->GetResolvedURL() ;
			xmlFile << "</url>" ;
			xmlFile << "<count>" ;
			xmlFile << currOcc->GetCountValue() ;
			xmlFile << "</count>" ;
			xmlFile << "</occurrence>" ;
		}
		delete oi;
		xmlFile << "</word>" ;
	}
	delete i;
	xmlFile << "</index>" ;
	xmlFile << "</website>" ;
	
	xmlFile.close();
}
bool OutputGenerator::Test(std::ostream & os){
	bool success = true;
	os << "Testing OutputGenerator..." << endl;
	Pages pages;
	pages.Insert(new Page (new URL("http://www.cnn.com/moose"), "A moose destroys New York"));
	pages.Insert(new Page (new URL("http://www.cnn.com/mike"), "Mike wins everything"));
	pages.Insert(new Page (new URL("http://www.cnn.com/rain"), "It's raining"));
	pages.Insert(new Page (new URL("http://www.cnn.com/tofu"), "Still gross"));
	
	WordIndex index;
	
	index.Insert("moose", new URL("http://www.cnn.com/moose"));
	index.Insert("moose", new URL("http://www.cnn.com/moose"));
	index.Insert("mike", new URL("http://www.cnn.com/mike"));
	index.Insert("mike", new URL("http://www.cnn.com/mike"));
	index.Insert("rain", new URL("http://www.cnn.com/rain"));
	index.Insert("tofu", new URL("http://www.cnn.com/tofu"));
	index.Insert("tofu", new URL("http://www.cnn.com/tofu"));
	index.Insert("tofu", new URL("http://www.cnn.com/tofu"));
	OutputGenerator og;
	og.generateXMLFile("test/OGTest.xml", "http://www.cnn.com", pages, index);
	
	ifstream file;
	string xml;
	file.open("test/OGTest.xml");
	getline(file, xml);
	file.close();
	
	TEST(xml == "<website><start-url>http://www.cnn.com</start-url><pages><page><url>http://www.cnn.com/mike</url><description>Mike wins everything</description></page><page><url>http://www.cnn.com/moose</url><description>A moose destroys New York</description></page><page><url>http://www.cnn.com/rain</url><description>It&apos;s raining</description></page><page><url>http://www.cnn.com/tofu</url><description>Still gross</description></page></pages><index><word><value>mike</value><occurrence><url>http://www.cnn.com/mike</url><count>2</count></occurrence></word><word><value>moose</value><occurrence><url>http://www.cnn.com/moose</url><count>2</count></occurrence></word><word><value>rain</value><occurrence><url>http://www.cnn.com/rain</url><count>1</count></occurrence></word><word><value>tofu</value><occurrence><url>http://www.cnn.com/tofu</url><count>3</count></occurrence></word></index></website>");

	return success;
}
