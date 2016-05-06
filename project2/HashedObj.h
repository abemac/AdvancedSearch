#ifndef HASHEDOBJ_H
#define HASHEDOBJ_H

#include <string>
/*
	This class is used for data bookeeping in the hash table. It simply stores
	a string key, and provides = and == overloads
*/
class HashedObj {
public:
	std::string key;  // the key for a hash object

	HashedObj ();
	//constructors
	explicit HashedObj (const std::string _key);
	explicit HashedObj (const HashedObj& other);
	explicit HashedObj (HashedObj&& other);

	//overloaded operators
	HashedObj& operator=(const HashedObj& other) = default;
	bool operator==(const HashedObj& other)const; // overloading equality check

};



#endif
