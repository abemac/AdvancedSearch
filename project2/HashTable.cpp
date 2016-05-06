#include "HashTable.h"
/**
This class provides the implementation of HashTable.h.  See the documention
in the header file for more details.
*/

HashTable::HashTable(int _size,ResolutionType _resolutionFuction):
	resolutionFunction {_resolutionFuction},
	size{_size},
	numItems{0}{
		v= std::vector<HashEntry>{size_t(_size)};
	}


// accessors


int HashTable::hash (const HashedObj& x) const {

	int hashVal{0};
	std::string key = x.key.substr(0,3);
	for(char ch : key){
		hashVal = hashVal*37 + ch;
	}
	return hashVal % size;
}


int HashTable::linearResolution (int i) const {
	return i;
}

int HashTable::quadraticResolution (int i) const {

	return i * i;
}

// needs an extra parameter to call the second hash function, hash2
int HashTable::doubleHashResolution (int i, const HashedObj& x) const {
	return i * hash2(x);
}
int HashTable::hash2 (const HashedObj& x) const {
	int secondLowestPrime = size;
	//std::cout<<size<<std::endl;
	int numDivis = -1;
	while ( numDivis!=0){
		numDivis = 0;
		secondLowestPrime--;
		int thisNum = secondLowestPrime-1;
		while(thisNum>1 && numDivis==0){
			if((secondLowestPrime % thisNum) == 0)
				numDivis++;
			thisNum--;
		}

	}
	//std::cout<<secondLowestPrime<<std::endl;

	return secondLowestPrime - (hash(x) % secondLowestPrime);
}

int HashTable::resolution(int i,const HashedObj& x)const{
	if(resolutionFunction == LINEAR){
		return linearResolution(i);
	}
	else if (resolutionFunction == QUADRATIC){
		return quadraticResolution(i);
	}
	else
		return doubleHashResolution(i,x);
}
bool HashTable::contains (const HashedObj& x) const{
	// CODE HERE
	int hashVal = hash(x);
	int i = 0;
	while((v[(hashVal + resolution(i,x))%size].info != EMPTY && !(v[(hashVal + resolution(i,x))%size].element == x))
			&& (i<=size)){//(limit in case all are marked as DELETED )
		i++;
	}
	hashVal = (hashVal + resolution(i,x))%size;
	if(v[hashVal].info == ACTIVE && v[hashVal].element == x){
		return true;
	}else
		return false;
}

// mutators
void HashTable::makeEmpty(){
	// CODE HERE
	for(int i =0; i < size;i++){
		v[i].info=EMPTY;  //not actually deleting, just marking as deleted
		v[i].element.key = "";
	}
	numItems = 0;
}
bool HashTable::insert(const HashedObj& x){
	// CODE HERE			//NOT COMPLETE!!!!
	int hashVal = hash(x);
	int i =0;
	while(v[(hashVal + resolution(i,x))%size].info==ACTIVE){
		i++;
	}
	hashVal = (hashVal + resolution(i,x))%size;
	v[hashVal].element = x;
	v[hashVal].info = ACTIVE;
	numItems++;

	double lf = (double)numItems / (double)size;
	if (lf > 0.5){//if load facter >0.5, need to resize and rehash
		//std::cout<<"rehash"<<std::endl;
		rehash();
	}
	return true; // b/c will always be able to insert??
}
bool HashTable::insert(HashedObj&& x){
	// CODE HERE
	HashedObj& x2 = x;
	return insert(x2);

}
bool HashTable::remove(const HashedObj& x){
	// CODE HERE
	int hashVal = hash(x);
	int i =0;
	while(!(v[(hashVal + resolution(i,x))%size].element== x) && v[(hashVal + resolution(i,x))%size].info!=EMPTY && i<=size){
		i++;
	}
	hashVal = (hashVal + resolution(i,x))%size;
	if(v[hashVal].info == EMPTY || i>size)
		return false;
	else{
		v[hashVal].info = DELETED;
		v[hashVal].element.key ="";
		numItems--;
		return true;
	}
}

// performs a rehashing by finding the next prime after doubling the tableSize
void HashTable::rehash(){
	// CODE HERE
	int nextPrime = size*2;
	//std::cout<<size<<std::endl;
	int numDivis = -1;
	while ( numDivis!=0){
		numDivis = 0;
		nextPrime++;
		int thisNum = nextPrime-1;
		while(thisNum>1 && numDivis==0){
			if((nextPrime % thisNum) == 0)
				numDivis++;
			thisNum--;
		}

	}
	size = nextPrime;
	numItems = 0;
	std::vector<HashEntry> oldTable =v;
	v = std::vector<HashEntry>{size_t(nextPrime)};
	for(HashEntry he : oldTable){
		if(he.info == ACTIVE){
			insert(he.element);
			he.info=ACTIVE;
			numItems++;
		}


	}



}

void HashTable::printHashTable(){
	std::cout<<"|";
	for (int i =0;i<size;i++){
		std::cout<<v[i].element.key<<"|";
	}
	std::cout<<""<<std::endl;
}
