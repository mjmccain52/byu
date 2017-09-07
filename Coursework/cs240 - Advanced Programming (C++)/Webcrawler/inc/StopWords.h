#ifndef CS240_STOP_WORDS_H
#define CS240_STOP_WORDS_H

#include <string>

class StopWords{
public:
StopWords();
~StopWords();
bool IsStopWord(const std::string& word) const;
void LoadSWFile(std::string filename);

static bool Test(std::ostream& os);
private:
std::string* words;
int size;
int max;
void Grow();
//int CompareWords (const void * a, const void * b);
void Insert (const std::string& word);

};

#endif
