#include "URLCountPair.h"
#include <cstdlib>

URLCountPair::URLCountPair(std::string k){
	key = k;
	value = 0;
}

int URLCountPair::HashCode(){ 
	return atoi(key.c_str());
}

bool URLCountPair::Equals (URLCountPair* const other){ 
	return other->key == key;
}

std::string URLCountPair::GetKey(){ 
	return key;
}

void URLCountPair::SetValue(int v){ 
	value = v;
}

int URLCountPair::GetValue(){
	return value;
}
