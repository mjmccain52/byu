#ifndef CS240_WORD_INDEX_HASH_SET_H
#define CS240_WORD_INDEX_HASH_SET_H

#include <string>
class IndexNode{
	friend class WordIndexHashSet;
public:
	IndexNode(string url, int occurred = 0);
	int HashCode();
	bool Equals (const IndexNode & other);
	string GetURLKey();
	void Add();
	int GetOccurredValue();
	
private:
	std::string wordKey;
	Occurrences occurrencesValue;
};

class WordIndexHashSet{
public:
	WordIndexHashSet();
	IndexNode ContainsKey (IndexNode i);
	bool Add (IndexNode i);
	
private;
	void Rehash();
	const int INIT_SIZE = 101;
	LinkedList* hashTable;
	int hashTableSize;
	int size;
};
#endif
