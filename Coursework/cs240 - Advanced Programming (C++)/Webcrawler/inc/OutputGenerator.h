#ifndef CS240_OUTPUT_GENERATOR_H
#define CS240_OUTPUT_GENERATOR_H

#include "Pages.h"
#include "WordIndex.h"

class OutputGenerator{
public:
	OutputGenerator();
	~OutputGenerator();
	//! creates and writes the xml file
	void generateXMLFile(const std::string & filename, const std::string & start, 
					Pages& pages, WordIndex& index);
	static bool Test(std::ostream & os);
private:

};
#endif
