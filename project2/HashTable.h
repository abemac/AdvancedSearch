#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashedObj.h"
#include <iostream>
#include <vector>

/*
We used a hash table to speed up the identification of stop words
This is just a standard hash table with options for different types
of collision resolution.  We did not feel the need to extensively
comment the HashTable, as it is very standard.  However, comments are
given on code that is not obvious at first sight.
*/
class HashTable {
public:
	enum ResolutionType {LINEAR,QUADRATIC,DOUBLE};//the resolution type
	explicit HashTable(int size = 101,ResolutionType resolution = LINEAR);// init to prime
	enum EntryType {ACTIVE, EMPTY, DELETED};//for bookeeping


	// accessors
	int hash (const HashedObj& x) const;
	int linearResolution (int i) const;//helper method for linearResolution
	int quadraticResolution (int i) const;//helper method for quadraticResolution
	int doubleHashResolution (int i, const HashedObj& x) const;//helper method for doubleHashResolution
	int hash2 (const HashedObj& x) const;//used for double hashing
	bool contains (const HashedObj& x) const;//returns true if the hash table contains the item
	int resolution (int i,const HashedObj& x)const;//gets the index of the resolution after a collision
	// mutators
	void makeEmpty();//removes all elements from the has table
	bool insert(const HashedObj& x);//inserts into hash table
	bool insert(HashedObj&& x);//inserts an r-value
	bool remove(const HashedObj& x);//remove from hash table
	void rehash();//used to resize the hash table when needed

	//for testing
	void printHashTable();


private:
	//struct used to store table entires
	struct HashEntry
	{
		HashedObj element;//the HasheObj element
		EntryType info;//for bookeeping

		HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY) :
			element {e},
			info {i} {}
		HashEntry(HashedObj&& e, EntryType i = EMPTY) :
			element {std::move (e)},
			info {i} {}
	};
	const ResolutionType resolutionFunction;//the collision resolution type
	std::vector<HashEntry> v;//all the items
	int size;//current max size of the table
	int numItems;//num items in the hash table

};



#endif
