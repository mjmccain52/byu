#ifndef CS240_OCCURRENCE_HASH_SET_H
#define CS240_OCCURENCE_HASH_SET_H

#include <string>
class OccurrenceNode{
	friend class OccurrenceHashSet;
public:
	OccurrenceNode(string url, int occurred = 0);
	int HashCode();
	bool Equals (const OccurrenceNode & other);
	string GetURLKey();
	void IncreaseOccurrence();
	int GetOccurredValue();
	
private:
	string urlKey;
	int occurredValue;
};

class Occurrences{
public:
	OccurrenceHashSet();
	OccurrenceNode ContainsKey (OccurrenceNode o);
	bool Add (OccurrenceNode o);
	
private;
	void Rehash();
	const int INIT_SIZE = 101;
	LinkedList* hashTable;
	int hashTableSize;
	int size;
};
#endif
