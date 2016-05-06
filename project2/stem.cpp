#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "HashTable.h"
using namespace std;



//////////variables
vector<string> currentFile = vector<string>(); //used to store the file currently being processed
int fileNum=1;
string workingDirectory; //directory of text files
vector<string> stopWords;//only used to read in the stop words before creating the hash table
HashTable stopWordsHash {10,stopWordsHash.QUADRATIC};//hash table of the stop words for fast processing

string os;//the os the program is running on

//methods
string getOsName();//gets OS name
void readFile(string path);//reads file in
void rmStopWords();//removes stop words
void init();//initilizes processing
bool checkIfInStopWords(string s);//checks if a string is a stop words
void writeFile();//writes the processed file back out
void processDirectory();//handles all processing for the text file directory
string getFileName();//gets file name to be processed
int getM(string b,unsigned int endSize);//gets the value of m for the porter algorithm
bool isVowel(string check, int index);//returns if a character is a Vowel
bool endsIn(string word, string end);//boolean functions for seeing if a string ends in another string

void stemPorterAlg();//main function for porter alg
void porter1a(string& check);//porter step 1a
void porter1b(string& check);//porter step 1b
void porter1c(string& check);//porter step 1c
void porter2(string& check);//porter step 2
void porter3(string& check);//porter step 3
void porter4(string& check);//porter step 4
void porter5a(string& check);//porter step 5a
void porter5b(string& check);//porter step 5b

void runCmdLineProgram();//runds command line program
void printInstructions();//prints instructions fro command line program
void stem();
/*
	main function
*/
void stem(){
	init();
  processDirectory();
}

/*
	checks if a string is a stop word.  Uses the hash table for fast
	processing.
*/
bool checkIfInStopWords(string s){
	return stopWordsHash.contains(HashedObj(s));
}

/*
	removes all stop words from the currentFile vector
*/
void rmStopWords(){
	for(unsigned int i=0; i<currentFile.size();i++){
		if(checkIfInStopWords(currentFile[i])){
			currentFile.erase(currentFile.begin()+i);//removes if is a stop word
			i-=1;
		}
	}

}

/**
	main function for running all the steps of the porter alorithm for stemming
*/
void stemPorterAlg(){
	//calls each function on each word in currentFile
	for(unsigned int i=0;i<currentFile.size();i++){
		porter1a(currentFile[i]);
		porter1b(currentFile[i]);
		porter1c(currentFile[i]);
		porter2(currentFile[i]);
		porter3(currentFile[i]);
		porter4(currentFile[i]);
		porter5a(currentFile[i]);
		porter5b(currentFile[i]);

	}
}

/*
	step 1a of the porter algorithm.
	SSES 		-> 		SS 		    		caresses 		-> 		caress
	IES 		-> 		I 		    		ponies 		-> 		poni
						    							ties 		-> 		ti
	SS 		-> 		SS 		    		caress 		-> 		caress
  S 		-> 				    		 cats 		-> 		cat
*/
void porter1a(string& check){
	if(endsIn(check,"sses")){
		check.pop_back();
		check.pop_back();
	}
	else if(endsIn(check,"ies")){
		check.pop_back();
		check.pop_back();
	}
	else if(endsIn(check,"s") && !endsIn(check,"ss")){
		check.pop_back();
	}
}

/*
	step 1b of the porter algorithm
	(m>0) EED 		-> 		EE 		    		feed 		-> 		feed
						    									agreed 		-> 		agree
  (*v*) ED 		-> 				    	  	plastered 		-> 		plaster
						    									bled 		-> 		bled
  (*v*) ING 		-> 				    		motoring 		-> 		motor
							 										sing 		-> 		sing

	if step 2 or 3 are successful (goOn is true):

		AT 		-> 		ATE 		    		conflat(ed) 		-> 		conflate
		BL 		-> 		BLE 		    		troubl(ed) 		-> 		trouble
		IZ 		-> 		IZE 		    		siz(ed) 		-> 		size

		(*d and not (*L or *S or *Z)) 		-> 		single letter
															hopp(ing) 		-> 		hop
															tann(ed) 		-> 		tan
															fall(ing) 		-> 		fall
															hiss(ing) 		-> 		hiss
															fizz(ed) 		-> 		fizz
	(m=1 and *o) 		-> 		E 		fail(ing) 		-> 		fail
														fil(ing) 		-> 		file
*/
void porter1b(string& check){
	bool goOn=false;
	if(endsIn(check,"eed")){
			if(getM(check,3)>0)
				check.pop_back();
	}
	else if(endsIn(check,"ed")){

		bool containsVowel=false;
		for(unsigned int i=0;i<check.size()-2 && !containsVowel;i++){

			containsVowel=isVowel(check,i);
		}
		if(containsVowel){
			goOn=true;
			check.pop_back();
			check.pop_back();
		}

	}
	else if(endsIn(check,"ing")){
		bool containsVowel=false;
		for(unsigned int i=0;i<check.size()-3 && !containsVowel;i++){
			containsVowel=isVowel(check,i);
		}
		if(containsVowel){
			goOn=true;
			check.pop_back();
			check.pop_back();
			check.pop_back();
		}

	}

	if(goOn){
		if(endsIn(check,"at")){
			check+='e';
		}
		else if (endsIn(check,"bl")){
			check+='e';
		}else if(endsIn(check,"iz")){
			check+='e';
		}
		else if(check.size()>=2 && check[check.size()-2]==check[check.size()-1]){
			if(!endsIn(check,"l") && ! endsIn(check,"s") && !endsIn(check,"z")){
				check.pop_back();
			}
		}else if(getM(check,0)==1 && check.size()>=3){
			if(!isVowel(check,check.size()-3) &&
					isVowel(check,check.size()-2) &&
					!isVowel(check,check.size()-1) &&
					check[check.size()-1]!='w' &&
					check[check.size()-1]!='x' &&
					check[check.size()-1]!='y'){
						check+='e';
					}

		}


	}

}
/*
	step 1c of porter algorithm
	(*v*) Y 		-> 		I 		    		happy 		-> 		happi
						    									sky 		-> 		sky

*/
void porter1c(string& check){
	bool containsVowel=false;
	for(int unsigned i=0;i<check.size()-1 && !containsVowel;i++){
		containsVowel=isVowel(check,i);
	}
	if(containsVowel && endsIn(check,"y")){
		check.pop_back();
		check.push_back('i');
	}

}
/**
	step 2 of the porter alogrithm:

	(m>0) ATIONAL 		-> 		ATE 		    		relational 		-> 		relate
	(m>0) TIONAL 		-> 		TION 		    		conditional 		-> 		condition
																			rational 		-> 		rational
	(m>0) ENCI 		-> 		ENCE 		    		valenci 		-> 		valence
	(m>0) ANCI 		-> 		ANCE 		    		hesitanci 		-> 		hesitance
	(m>0) IZER 		-> 		IZE 		    		digitizer 		-> 		digitize
	(m>0) ABLI 		-> 		ABLE 		    	 	conformabli 		-> 		conformable
	(m>0) ALLI 		-> 		AL 		    	   	radicalli 		-> 		radical
	(m>0) ENTLI 		-> 		ENT 		    		differentli 		-> 		different
	(m>0) ELI 		-> 		E 		    		    vileli 		-> 		vile
	(m>0) OUSLI 		-> 		OUS 		    		analogousli 		-> 		analogous
	(m>0) IZATION 		-> 		IZE 		    		vietnamization 		-> 		vietnamize
	(m>0) ATION 		-> 		ATE 		    		predication 		-> 		predicate
	(m>0) ATOR 		-> 		ATE 		    		operator 		-> 		operate
	(m>0) ALISM 		-> 		AL 		    		feudalism 		-> 		feudal
	(m>0) IVENESS 		-> 		IVE 		    		decisiveness 		-> 		decisive
	(m>0) FULNESS 		-> 		FUL 		    		hopefulness 		-> 		hopeful
	(m>0) OUSNESS 		-> 		OUS 		    		callousness 		-> 		callous
	(m>0) ALITI 		-> 		AL 		    		  formaliti 		-> 		formal
	(m>0) IVITI 		-> 		IVE 		    		sensitiviti 		-> 		sensitive
	(m>0) BILITI 		-> 		BLE 		    		sensibiliti 		-> 		sensible

*/
void porter2(string& check){
	//note, each m is calculated only on the step of the word. That is the reason
	//for the second parameter in getM.  it is the length of the suffix
		if(endsIn(check,"ational") && getM(check,7)> 0){
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.push_back('e');
		}

		else if(endsIn(check, "tional")&& getM(check,6) > 0){
			check.pop_back();
			check.pop_back();

		}
		else if(endsIn(check, "enci")&& getM(check,4) >0){
			check.pop_back();
			check.push_back('e');
		}
		else if(endsIn(check, "anci")&& getM(check,4) > 0){
			check.pop_back();
			check.push_back('e');
		}
		else if(endsIn(check, "izer") && getM(check,4) > 0){
			check.pop_back();
		}

		else if(endsIn(check, "abli") && getM(check,4) > 0){
			check.pop_back();
			check.push_back('e');
		}

		else if(endsIn(check, "alli") && getM(check,4) > 0){
			check.pop_back();
			check.pop_back();
		}

		else if(endsIn(check, "entli") && getM(check,4) > 0){
			check.pop_back();
			check.pop_back();
		}

		else if(endsIn(check, "eli")&& getM(check,3) > 0){
			check.pop_back();
			check.pop_back();
		}

		else if(endsIn(check, "ousli")&& getM(check,5) > 0){
			check.pop_back();
			check.pop_back();
		}

		else if(endsIn(check, "ization")&& getM(check,7) > 0){
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.push_back('e');
		}

		else if(endsIn(check, "ation")&& getM(check,5) > 0){
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.push_back('e');
		}

		else if(endsIn(check, "ator")&& getM(check,4) > 0){
			check.pop_back();
			check.pop_back();
			check.push_back('e');
		}

		else if(endsIn(check, "alism")&& getM(check,5) > 0){
			check.pop_back();
			check.pop_back();
			check.pop_back();
		}

		else if(endsIn(check, "iveness")&& getM(check,7) > 0){
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.pop_back();
		}

		else if(endsIn(check, "fulness")&& getM(check,7) > 0){
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.pop_back();
		}

		else if(endsIn(check, "ousness")&& getM(check,7) > 0){
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.pop_back();
		}

		else if(endsIn(check, "aliti")&& getM(check,5) > 0){
			check.pop_back();
			check.pop_back();
			check.pop_back();
		}
		else if(endsIn(check, "iviti")&& getM(check,5) > 0){
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.push_back('e');
		}

		else if(endsIn(check, "biliti")&& getM(check,6) > 0){
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.pop_back();
			check.push_back('l');
			check.push_back('e');

		}

}
vector<string> ends3={"icate", "ative", "alize", "iciti","ical", "ful","ness"};

//3 checks for the word ending in certain strings stored in the above vector
//3 has the goal of removing some suffixes or changing them down to others

void porter3(string& check){
	int m=0;

	int x;

		for (unsigned int i=0; i<ends3.size(); i++){//iterates through the vector
			if(endsIn(check, ends3[i])){//checks the word and the vector index
				m=getM(check, ends3[i].size());// gets an m to check
				x=i+1;
				break;
			}
		}
		if(m>0){//sees if m is greater than 0
			switch(x){
				case 1:	check.pop_back();//for ending in icate
								check.pop_back();
								check.pop_back();
								break;

				case 2: check.pop_back();//for ending in ative
								check.pop_back();
								check.pop_back();
								check.pop_back();
								check.pop_back();
								break;

				case 3: check.pop_back();//for ending in alize
								check.pop_back();
								check.pop_back();
								break;

				case 4: check.pop_back();//for ending in iciti
								check.pop_back();
								check.pop_back();
								break;

				case 5: check.pop_back();//for ending in ical
								check.pop_back();
								break;

				case 6: check.pop_back();//for ending in ful
								check.pop_back();
								check.pop_back();
								break;

				case 7: check.pop_back();//for ending in ness
								check.pop_back();
								check.pop_back();
								check.pop_back();
								break;
			}
		}
}


vector<string> ends4={"al", "ance", "ence", "er", "ic", "able", "ible",
										 "ant", "ement", "ment", "ent","sion","tion", "ou", "ism",
										 "ate", "iti", "ous", "ive", "ize"};

//4 is about removing the last suffixes to words, it is about popping them
//off, it uses the above declared vector of string

void porter4(string& check){
	int m=0;

	int x;

		for (unsigned int i=0; i<ends4.size(); i++){//checks all the possble suffixes
			if(endsIn(check, ends4[i])){//using endsIn  for a match
				m=getM(check, ends4[i].size());//stores m to check if its large enough
				x=i+1;//the switch value
				break;
			}
		}
		if(m>1){//has to be larget than 1 , therefore size and shall aren't reduced
			switch(x){
				case 1:	check.pop_back();// for ending al
								check.pop_back();
								break;

				case 2: check.pop_back();// for ending in ance
								check.pop_back();
								check.pop_back();
								check.pop_back();
								break;

				case 3: check.pop_back();//for ending in ence
								check.pop_back();
								check.pop_back();
								check.pop_back();
								break;

				case 4: check.pop_back();//for ending in er
								check.pop_back();
								break;

				case 5: check.pop_back();//for ending in ic
								check.pop_back();
								break;

				case 6: check.pop_back();//for ending in able
								check.pop_back();
								check.pop_back();
								check.pop_back();
								break;

				case 7: check.pop_back();//for ending in ible
								check.pop_back();
								check.pop_back();
								check.pop_back();
								break;
				case 8: check.pop_back();//for ending in ant
								check.pop_back();
								check.pop_back();
								break;

				case 9: check.pop_back();//for ending in ement
								check.pop_back();
								check.pop_back();
								check.pop_back();
								check.pop_back();
								break;

				case 10:check.pop_back();//for ending in ment
								check.pop_back();
								check.pop_back();
								check.pop_back();
								break;

				case 11:check.pop_back();//for ending in ent
								check.pop_back();
								check.pop_back();
								break;

				case 12:check.pop_back();//for ending in sion
								check.pop_back();
								check.pop_back();
								break;

				case 13:check.pop_back();//for ending in tion
								check.pop_back();
								check.pop_back();
								break;
				case 14:check.pop_back();//for ending in ou
								check.pop_back();
								break;
				case 15:check.pop_back();//for ending in ism
								check.pop_back();
								check.pop_back();
								break;
				case 16:check.pop_back();//for ending in ate
								check.pop_back();
								check.pop_back();
								break;
				case 17:check.pop_back();//for ending iti
								check.pop_back();
								check.pop_back();
								break;
				case 18:check.pop_back();//for ending ous
								check.pop_back();
								check.pop_back();
								break;
				case 19:check.pop_back();//for ending ive
								check.pop_back();
								check.pop_back();
								break;
				case 20:check.pop_back();//for ending in ize
								check.pop_back();
								check.pop_back();
								break;

			}
		}

}
//5a removes the last e in words as its main thing
//The First case is for the word to end in an e, and the m to be
//greater than one and the second case is for m to be equal to 1 , end in e,
// and not end  the from of a consonant, vowel, and a consonant with the second
// consonant not ending in x,y, or z
// This part is one statement

void porter5a(string& check){
	if(endsIn(check,"e") && (getM(check,1) > 1) ){
		check.pop_back();
	}
	if(check.size()>=4 && endsIn(check,"e")&&
	!(!isVowel(check,check.size()-4) && //the entire cvc and its conditions
			isVowel(check,check.size()-3) && // are kept in a massive negate statement
			!isVowel(check,check.size()-2) &&
			check[check.size()-1]!='w' &&
			check[check.size()-1]!='x' &&
			check[check.size()-1]!='y' ) &&
			getM(check,1) == 1){

				check.pop_back();
	}
}

//5b is reducing the number of ls at the end of a word
//It checks that the word ends in an l, has the m > 1, and has two
// last two indexes ending in l.
void porter5b(string& check){
	if( endsIn(check, "l") &&
			check.size()>=2 && //simple check to ensure not index issues
			check[check.size()-2]=='l' && //checks for l in second to last index
			 getM(check,1) > 1){
				 check.pop_back();
	}
}



/*
	reads a file with a path into the currentFile vector for
	processing.  It removes all non ASCII values and converts
	all letters to lower case.
*/
void readFile(string path){
	int x=0;
	char c;
	fstream textfile;
	textfile.open(path);
	while (!textfile.eof()){
			c=textfile.get();//assign a char to c
			while(c==' '){
				c=textfile.get();
			}
			currentFile.push_back("");//create a new space for new word
			while((c!=',' && c!=' ' && c!='\n') && !textfile.eof()){//split words by ',' ' ' '\n'
				if(c<91 && c>64)//convert string to all lower case
					c+=32;
				if(c>=97&& c<=122)//only include letters
					currentFile[x]=currentFile[x]+c;//build words char by char
				c=textfile.get();
			}
			if(currentFile[x].length()==0)
				currentFile.pop_back();
			else{
				x++;
			}
		}

		textfile.close();
}

/**
	writes the currentFile vector to a file with the name of the original file
	appended by _cleaned, in the corpus directory.
*/
void writeFile(){
	string path;
	//paths are different in Windows/ MAC/ Linux
	if(os.compare("Windows")==0){
		if(fileNum<10){
			path="..\\corpus\\txt0"+to_string(fileNum)+"_cleaned.txt";
		}else{
			path="..\\corpus\\txt"+to_string(fileNum)+"_cleaned.txt";
		}
	}else{
		if(fileNum<10){
			path="../corpus/txt0"+to_string(fileNum)+"_cleaned.txt";
		}else{
			path="../corpus/txt"+to_string(fileNum)+"_cleaned.txt";
		}
	}
	ofstream file;
	file.open(path);
	int length=0;
	for(unsigned int i=0; i<currentFile.size();i++){
		file << currentFile[i];//writes each poreccessed word out individually
		length+=currentFile[i].size();
		file<< " ";//space between words
		if(length>=80){
			file<<"\n";//new lines every 80 characters
			length=0;
		}
	}
	file.close();

}

/*
	calls all necessary functions to proecess the directory of text files.
	note that for each iteration,  the vector currentFile is reused for all functions.
*/
void processDirectory(){
	while(fileNum<=40){
		currentFile.clear();
		string path =getFileName();
		cout<<path<<endl;
		readFile(path);//reads text file into currentFile vector
		rmStopWords();//removes stop words
		stemPorterAlg();//applies Porter algorithm for stemmming
		writeFile();//writes the file back out to the corpus directory
		fileNum++;

	}
	fileNum=1;
}

/*
	gets the path of the file to be currently processed, according to
	fileNum and OS
*/
string getFileName(){
	string path;
	//paths are different for Windows and MAC/Linux
	if(os.compare("Windows")==0){
		if(fileNum<10){
			path=workingDirectory+"\\txt0"+to_string(fileNum)+".txt";
		}else{
			path=workingDirectory+"\\txt"+to_string(fileNum)+".txt";
		}
	}else{
		if(fileNum<10){
			path=workingDirectory+"/txt0"+to_string(fileNum)+".txt";
		}else{
			path=workingDirectory+"/txt"+to_string(fileNum)+".txt";
		}
	}

	return path;
}

/*
 used to get the operating system
*/
string getOsName()
{
    #ifdef _WIN32
    return "Windows";
    #elif _WIN64
    return "Windows";
    #elif __unix || __unix__
    return "Linux";
    #elif __APPLE__ || __MACH__
    return "Mac";
    #elif __linux__
    return "Linux";
    #else
    return "Other";
    #endif
}

/*
	Used to initilize a directory process to clean the text files
*/
void init(){
	os=getOsName();
	//sets the workingDirectory to be the texts folder.  Note that the ..
	//is needed because we run the programs from within the run folder.
	if(os.compare("Windows")==0){
		workingDirectory="..\\texts";
	}else{
		workingDirectory="../texts";
	}
	//*** reads stop words into vector **///
	stopWords=vector<string>();
	fstream textfile;
	if(os.compare("Windows")==0){
		textfile.open("..\\stop_words.txt");
	}else{
		textfile.open("../stop_words.txt");
  }
	int x=0;
	char c;
	while (!textfile.eof()){
		c=textfile.get();//assign a char to c
		while(c==' '){
			c=textfile.get();
		}
		stopWords.push_back("");//create a new space for new word
		while((c!='\n') && !textfile.eof()){//split words by'\n'
			if(c<91 && c>64){//convert string to all lower case
				c+=32;
			}
			if(c>=32 && c<=127)//make sure all charters are visible and make sense
				stopWords[x]=stopWords[x]+c;//build words char by char
			c=textfile.get();
		}
		if(stopWords[x].back()==' '){//delete useless ' ' at the end of words
			stopWords[x].pop_back();
		}
		x++;
	}
	textfile.close();
	//*** end of reading stop words into vector **///

	//** creates hash table of stop words: makes stop word recognition much more
	//efficiant
	for(string s: stopWords){
		stopWordsHash.insert(HashedObj(s));
	}


}

//getM returns the number of Vowel-Consosnant sequences or VCs noted in a from of
// VC^M, this is another essentual Porter helper method.
int getM(string b,unsigned int endSize){ //endSize is how far we are counting the VCs to keep them away from any suffixes
	unsigned int j= 0;
	int counter = 0;
	if(endSize>b.size()){//a check to ensure that we aren't going to access the string out side of its index
		return 0;
	}
	while( j+2<=b.size()-endSize){//increments in a +2 manner untill  it hits the end of where it should stop checking
		if(isVowel(b,j) && !isVowel(b,j+1)){//checks the space at j is a vowel and the space one ahead is not a vowel
			counter++;
		}
		j++;
	}
	return counter;
	}

//endsIn is  returns a boolean based on if the word has the same last indexes as end
//This used several times for if statements in the Porter alogrithm

bool endsIn(string word, string end){
	if(word.size()<end.size()){// A simple check to ensure that the end is always smaller than or equal to the word
		return false;
	}

	bool match=true;
	for(unsigned int i=0;i<end.size() && match;i++){//Until either the end is fully traversed or math is false
		if(end[end.size()-i-1]!=word[word.size()-i-1]){//applying i in a manner of subtracting to traverse the indexes from last to first of end
			match=false;
		}
	}
	return match;
}


//For quickly searching through the char arrays to confirm that a char is in fact
// a mamber of one of them.
//need this for Porter methods system as a whole

//isVowel is a helper method designed to find that a certain index of a string
// is a vowel returning a boolean based on that fact

bool isVowel(string check, int index){
	char vowels[]={'a','e','i','o','u'}; //An Array of the 5 vowels that the porter alogrithm uses
	for(int i =0; i<5; i++){//Simple for loop going through the array to the
		if(check[index] == vowels[i]){
			return true;
		}
	}

	if(check[index]=='y' && index>0){//Additional check for the ys that aren't in front
		if(!isVowel(check,index-1)){// is checking that there is a consonant in front of it
			return true;
		}
	}
	return false;
}


///********************************
///********************************
//  ALL CODE PAST THIS POINT IS USED TO READ AND PROCESS INPUT
//  FOR THE COMMAND LINE PROGRAM.

/*
 * print Instructions
 */
void printInstructions(){
 	cout<<"Instructions:"<<endl;
 	cout<<"\t help (h) :  \t\t     show these instructions again\n"<<endl;
 	cout<<"\t cleanUpFiles(clean or \"1\"): clean up stopWords and stem,\n\t\t\t\t     then rewrite to a new file into\n\t\t\t\t     corpus folder"<<endl;
 	cout<<"\n\t quit (q): \t\t     quit program"<<endl;
}
/*
 * Welcome screen
 * Ask user's input to go through instructions.
 */
void runCmdLineProgram(){
	cout<<"\n**Welcome to Abraham, Tyler and Qichao's String Process Program**\n"<<endl;
	printInstructions();
	string usrInput;
	cout<<"Please Enter (h for help):";
	cin>>usrInput;
	while(usrInput.compare("q")!=0 && usrInput.compare("quit")!=0){
		if(usrInput.compare("help")==0 || usrInput.compare("h")==0){
			printInstructions();
			cout<<"Please Enter:";
			cin>>usrInput;
		}
		else if(usrInput.compare("clean")==0 || usrInput.compare("1")==0|| usrInput.compare("cleanUpFiles")==0){
			processDirectory();
			cout<<"Done"<<endl;
			cout<<"Please Enter (h for help):";
			cin>>usrInput;
		}
		else{
			cout<<"\n**Invalid Input, try again."<<endl;
			cout<<"Please Enter (h for help):";
			cin>>usrInput;
		}
	}//end while
	cout<<"Bye Bye"<<endl;
}
