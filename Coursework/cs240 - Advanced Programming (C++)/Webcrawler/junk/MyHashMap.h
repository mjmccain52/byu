#ifndef CS240_MY_HASH_MAP_H
#define CS240_MY_HASH_MAP_H

#include "MyHashSet.h"

//! A classic Hash Map that works wonderfully with keys and values.
class MyHashMap{
public:
	//! Constructor
	MyHashMap();
	~MyHashMap();
	//! clears the map
	void Clear();
	//! @param key The key of the Pair we want to access
	//! @return a pointer to the Pair object
	void* Get (void* key);
	//! Is it empty?
	bool IsEmpty();
	//! @param key and value are to form a new Pair Object
	//! @return a pointer to the newly inserted Pair object
	void* Put(void* key, void* value);
	//! @param key The key of the Pair to be removed
	//! @return A pointer to the removed Pair object
	void* Remove(void* key);
	int Size();
private:
	MyHashSet hashTable; //the table that contains all the Pair objects
};
#endif
