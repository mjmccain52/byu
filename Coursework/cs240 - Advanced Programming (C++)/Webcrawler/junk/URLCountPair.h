#ifndef CS240_URL_COUNT_PAIR_H
#define CS240_URL_COUNT_PAIR_H

#include<string>

//! The base node unit of a map
class URLCountPair{
public:
	//! Constructor takes pointers to key and value
	//! @param k the key v the value
	URLCountPair(std::string k);
	//! hashcode function does some fun math to make unique codes for the stuff
	//! stored in here
	//! @return the hash code for the Pair
	int HashCode();
	//! Determines if two Pair objects are equivalent
	//! @param other The other object to compare
	//! @return true if the two objects are the same
	bool Equals (URLCountPair* const other);
	//! retrieves the key of the Pair
	//! @return a pointer to the key
	std::string GetKey();
	//! @param v Is the new value for the Pair oject
	void SetValue(int v);
	//! @return Pointer to the Pair Object.
	int GetValue();
	
private:
	std::string key; // key of the Map Pair
	int value; // value of the map Pair
};

#endif
