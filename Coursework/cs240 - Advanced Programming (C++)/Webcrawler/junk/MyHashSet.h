#ifndef CS240_MY_HASH_SET_H
#define CS240_MY_HASH_SET_H

//!  Your standard Hash Set with only pointers to objects
class MyHashSet{
public:
	//!Constructor.  Sets up the hashtable to the default initial size
	MyHashSet();
	//! checks the set for the object o
	//! @param o A pointer to the object
	~MyHashSet();
	bool Contains (void* o);
	//! Checks the set for the key
	//! @param p The key in question
	//! @return a pointer to the Pair containing the key, NULL if it hasn't
	Pair* ContainsKey (Pair* p);
	//! @param p the Pair pointer that will do the replacing
	//! @return pointer to the Node that was replaced
	Pair* Replace (Pair* p);
	//! @param p the Pair pointer to be added to the hash set.
	bool Add (Pair* p);
	//! @param o the pointer to the object to be removed
	bool Remove (void* o);
	//! wipes the table and sets it back to the default size
	void Clear();
	//! Is the hash set empty?
	bool IsEmpty();
	
private;
	//! resize the hash table at critical mass
	void Rehash();
	const int INIT_SIZE = 101; //initial size of the hashTable
	MyList* hashTable; // the hashtable with its buckets of lists
	int hashTableSize; // size of the hash table
	int size; // total elements in the hashSet
};
#endif
