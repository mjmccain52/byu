#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

class URLResolver{
public:
	char* resolveURL(char* base, char* link){
		
		result = new char[strlen(base) + strlen(link)];
		if (link[0] == '#'){
			strcat(base, link);
			strcpy(result, base);
			return result;
		}
		else if (strstr(link, "http://") == link || strstr(link, "file:///") == link ||
				 strstr(link, "HTTP://") == link || strstr(link, "FILE:///") == link){
			strcpy (result, link);
			return result;				 
		}
		webLoc = new char[1024];
		baseCopy = new char[1024];
		strcpy(webLoc, "");
		strcpy(baseCopy, base);
		char* scheme = strtok(baseCopy, "/");
		if (strstr(scheme, "http:") == scheme || strstr(scheme, "HTTP:") == scheme){
			webLoc = strtok(NULL, "/");
		}
		if (link[0] == '/'){
			strcpy(result, scheme);
			strcat(result, "//");
			strcat(result, webLoc);
			strcat(result, link);
			return result;
		}
		char* token = strtok(NULL, "/");
		int i = 0;
		while (token != NULL){
			pathArr[i] = new char[1024];
			strcpy(pathArr[i], token);
			token = strtok(NULL, "/");
			i++;
		}
		climbBack(link);
		strcpy(result, scheme);
		strcat(result, "//");
		strcat(result, webLoc);
		strcat(result, "/");
		
		for (int j = 0; j < i - back - 1; j++){
			strcat(result, pathArr[j]);
			strcat(result, "/");		
		}
		strcat(result, link + resumeIndex);
		return result;	
	}
private:
	char* result;
	char* webLoc;
	char* baseCopy;
	char* pathArr[1024];
	int back;
	int resumeIndex;
	
	void climbBack(char* link){
		back = 0;
		resumeIndex = 0;
		for (int i = 0, dots = 0; link[i] != '\0'; i++){
			if (link[i] == '.'){
				dots++;
			}
			else if (link[i] == '/'){
				if (dots == 2){
					back++;
				}
				dots = 0;
			}
			else{
				resumeIndex = i;
				break;
			}
		}
	}
};

int main (int argc, char* argv[]){	
	if (argc != 3){
		cout << "USAGE: url-resolver <base-url> <relative-url>" << endl;
		exit(2);
	}
	URLResolver r;
	cout << r.resolveURL(argv[1], argv[2]) << endl;
	return 0;
}
