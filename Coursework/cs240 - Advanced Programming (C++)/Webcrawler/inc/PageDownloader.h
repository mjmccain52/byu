#ifndef CS240_PAGE_DOWNLOADER_H
#define CS240_PAGE_DOWNLOADER_H

#include "URL.h"
class PageDownloader{
public:
	//! Gets all the code of the specified url
	//! @param url The URL object containing the absolute url to download
	//! @return a string containing all the html code
	std::string DownloadPage(const std::string& url);
	static bool Test(std::ostream& os);
private:

};
#endif
