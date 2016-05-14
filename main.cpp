#include "project2/stem.cpp"
#include "project1/graphMain.cpp"
#include "project1/Graph.h"
#include <cmath>
#include <algorithm>

using namespace std;

vector<string> dict;	//vector for dictionary
vector<string>query;	//vector for query
vector<string> lastDoc;	//temp vector for last read file
vector<string> unproccesedQuery;
int lastDocNum=-1;
const int MAX_RECUR_LIMIT = 3;
int RECURS=0;
double T = .6;
int NUM_DOCS=40;
double infinity = std::numeric_limits<double>::infinity();
double **frequency;   //frequency[0] = query frequencies
//                       //frequency[1][0] = frequency of first document, word in dict[0]
//                       //frequency[1][1] = frequency of first document, word in dict[1]
//                       //frequency[2][1] = frequency of second document, word in dict[1]
int wordCounts[41];
struct RANK{	//struct for ranking
  int doc;
  double distance;

};
void readFiles();	//Function to read files
int getIndex(string word);	//return index of the word that is in dict(vector).
vector<string> splitString(vector<string> dirty);
void runCmdLineProgram();	//run command line interface
void printInstructions();	//print out instructions after user input "h"
void inputQuery();		//ask user for query and process query and store to query vector
void loadDict();		//read all files and build a dictionary to store all the unique words
bool isThere(string word);	//check the word is in the dictionary
bool queryExists();		//check all inputs are in dictionary
double getFrequency(int i, string word);	//get frequency of the word in the file which index is i
double getQueryFrequency(string word);		//get frequency of the word in input
void addSubtypes();		//find subtype of query
vector<RANK> search();		//vector to store RANK
double computeDocDistance(int docNum);	//compute dictance for the doc which index is docNum
bool RANKcompare(RANK lhs, RANK rhs);	//compare RANK
void inputQuery();		//ask user for input

int main(){
  graphMain();			//build graph of knowledge base
  stem();			//stem all files
  loadDict();			//load dictionary

/*
 *	create a 2D array to store frequence for every word in each file.
 */
  frequency =new double*[41];
  for(unsigned int j=0;j<41;j++){
    frequency[j]=new double[dict.size()];
  }
  for (unsigned int i=1; i<41; i++){
    for(unsigned int j=0; j<dict.size();j++){
      frequency[i][j]=getFrequency(i, dict[j])/wordCounts[i];
    }
  }

  runCmdLineProgram();	//run command line

return 0;
}

void inputQuery(){
  query.clear();	//clean up query
  char input[100];	//a array to store user input
  cout<<"Input Query String: ";
  cin.getline(input,sizeof(input));	//ask and read user input
  for(unsigned int i=0;i<100;i++){
    if(input[i]<91 && input[i]>64)//convert string to all lower case
      input[i]+=32;
  }
  vector<string> tmp;
  tmp.push_back(input);
  query = splitString(tmp);	//split user input to single words
  unproccesedQuery=query;
  query = processQuery(query);	//stem query
}
double getQueryFrequency(string word){	//get frequency of the word in query
  int count=0;
  for(string s: query){
    if(s.compare(word)==0){
      count++;
    }
  }

  return count;
}



void loadDict(){
  for(int i=1; i<41; i++){
    string path;
    if(os.compare("Windows")==0){	//determine file path for different OS
  		if(i<10){
  			path="..\\corpus\\txt0"+to_string(i)+"_cleaned.txt";
  		}
      else{
  			path="..\\corpus\\txt"+to_string(i)+"_cleaned.txt";
  		}
  	}
    else{
  		if(i<10){
  			path="../corpus/txt0"+to_string(i)+"_cleaned.txt";
  		}
      else{
  			path="../corpus/txt"+to_string(i)+"_cleaned.txt";
  		}
    }

    int wordCount=0;
    char c;
    fstream textfile;
    textfile.open(path);	//read file form path
    string word="";
  	while (!textfile.eof()){
  			c=textfile.get();//assign a char to c

  			while(c==' '){
  				c=textfile.get();
  			}
  			//word.push_back("");//create a new space for new word
  			while((c!=',' && c!=' ' && c!='\n') && !textfile.eof()){//split words by ',' ' ' '\n'

  				if(c>=97&& c<=122)//only include letters
  					word=word+c;//build words char by char
  				c=textfile.get();
  			}
        if(word.size()!=0)
          wordCount++;
        if(!isThere(word) && word.size()!=0)
          dict.push_back(word);

        word="";
  	}
    wordCounts[i]=wordCount;
    wordCount=0;

  	textfile.close();

  }
}

bool isThere(string word){	//check if the word is in dictionary
  for(unsigned int i=0; i<dict.size(); i++){
    if(dict[i].compare(word)==0){
      return true;
    }
  }
  return false;

}
int getIndex(string word){	//retrun the index of the word in dictionary
  for (unsigned int i=0; i<dict.size(); i++){
    if(dict[i].compare(word)==0){
      return i;
    }
  }
  return -1;

}



double getFrequency(int i, string word){	//return frequency of the word in the file which index is i
  if(lastDocNum==i){	//check if the file has been read
    int count=0;
    for(string s : lastDoc){	// check the word's frequence in temp vector
      if(s.compare(word)==0){
        count++;
      }
    }
    return count;
  }

  lastDoc.clear();	//clear temp vector

  string path;
  if(os.compare("Windows")==0){	//determine file path for different OS
    if(i<10){
      path="..\\corpus\\txt0"+to_string(i)+"_cleaned.txt";
    }
    else{
      path="..\\corpus\\txt"+to_string(i)+"_cleaned.txt";
    }
  }
  else{
    if(i<10){
      path="../corpus/txt0"+to_string(i)+"_cleaned.txt";
    }
    else{
      path="../corpus/txt"+to_string(i)+"_cleaned.txt";
    }
  }
  int count=0;
  char c;
  fstream textfile;
  textfile.open(path);
  string x="";
  while (!textfile.eof()){	//read words from files
      c=textfile.get();		//assign a char to c
      while(c==' '){
        c=textfile.get();
      }
      while((c!=',' && c!=' ' && c!='\n') && !textfile.eof()){//split words by ',' ' ' '\n'

        if(c>=97&& c<=122)//only include letters
          x=x+c;//build words char by char
        c=textfile.get();
      }
      lastDoc.push_back(x);	//load words into temp vector
      if(x.compare(word)==0){
        count++;
      }
      x="";
  }
  textfile.close();
  lastDocNum=i;
  return count;
}


// double **frequency;   //frequency[0] = query frequencies
//                       //frequency[1][0] = frequency of first document, word in dict[0]
//                       //frequency[1][1] = frequency of first document, word in dict[1]
//                       //frequency[2][1] = frequency of second document, word in dict[1]



bool RANKcompare(const RANK lhs, const RANK rhs) { return lhs.distance < rhs.distance; }	//compare distances of two RANKs

vector<RANK> search(){	//return a sorted list of RANKs
  vector<RANK> docRanks;
  for(int i=1;i<41;i++){
    RANK tmp;
    tmp.doc=i;
    tmp.distance=computeDocDistance(i);	//compute distance between query and the file,index of i
    docRanks.push_back(tmp);		//add the RANK to the list
  }
  sort(docRanks.begin(),docRanks.end(),RANKcompare);
  //check if below Threshold T

  if(docRanks[0].distance > T && RECURS< MAX_RECUR_LIMIT){
    RECURS++;
    addSubtypes();
    docRanks=search();

  }else{
    cout<<"\n     Document Ranking:"<<endl;
    cout<<"Doc #"<<docRanks[0].doc<<" (distance = "<<docRanks[0].distance<<")"<<endl;
    cout<<"Doc #"<<docRanks[1].doc<<" (distance = "<<docRanks[1].distance<<")"<<endl;
    cout<<"Doc #"<<docRanks[2].doc<<" (distance = "<<docRanks[2].distance<<")"<<endl;
    cout<<"Doc #"<<docRanks[3].doc<<" (distance = "<<docRanks[3].distance<<")"<<endl;
    cout<<"Doc #"<<docRanks[4].doc<<" (distance = "<<docRanks[4].distance<<")"<<endl;
    cout<<"Doc #"<<docRanks[5].doc<<" (distance = "<<docRanks[5].distance<<")\n"<<endl;
  }
  return docRanks;

}


double computeDocDistance(int docNum){		//get distance between query and the file which index is docNum
  if(queryExists()){
    double distance=0;
    for (unsigned int i = 0;i<dict.size();i++){
      distance+=(frequency[0][i]-frequency[docNum][i])*(frequency[0][i]-frequency[docNum][i]);
    }
    distance = sqrt(distance);
    return distance;
  }else return infinity;
}



vector<string> splitString(vector<string> dirty){	//split query to single words and return the vector of the processed query
  vector<string> clean;
  for(unsigned int i=0;i<dirty.size();i++){
    string line = dirty[i];
    unsigned int k=0;
    for(unsigned int j=0; j< line.size();j++){
        if(line[j] == '_' || line[j] == ' '){
          clean.push_back(line.substr(k,j-k));
              k=j+1;
        }
        if(j+1 == line.size()){
          clean.push_back(line.substr(k,j-k+1));
        }
    }
  }
  return clean;
}

void addSubtypes(){		//find and add subtypes of query
  vector<string> additions;
  vector<string> temp;

  for(unsigned int i =0; i< query.size();i++){
      if(graph.containsVertice(query[i])){	//check if the query is in graph
        temp= graph.citeSubtypes(query[i],3,1);	//get 3 oder-1 subtypes of the query
      }else{
        temp.clear();
      }
      for(unsigned int j=0;j<temp.size();j++){
        if(additions.size() < 3){
          bool inAlready=false;
          for(string s: query){
            if(s.compare(temp[j])==0){
              inAlready=true;
            }else {
              vector<string> tmp2;
              tmp2.push_back(temp[j]);
              tmp2= splitString(tmp2);
              unsigned int count=0;
              for(string s: tmp2){
                for (string s2: query){
                  if(s.compare(s2)==0){
                    count++;
                  }
                }
              }
              if (count>=tmp2.size()){
                inAlready=true;
              }else{
                inAlready=false;
              }
            }
          }
          if(!inAlready){
            additions.push_back(temp[j]);
          }
        }
        if(additions.size() == 3){
          break;
        }
      }

      if(additions.size() == 3){
        break;
      }
  }

  vector<string> clean = splitString(additions);
  if(clean.size()>0){
    cout<<"\nYour query was appended with: ";
  }
  for(unsigned int k =0; k < clean.size(); k++){
    query.push_back(clean[k]);
    cout<<clean[k]<<" ";
  }
  if(clean.size()>0){
    cout<<""<<endl;
  }
  query=processQuery(query);
  for(unsigned int j=0; j<dict.size();j++){
    frequency[0][j]=getQueryFrequency(dict[j])/query.size();//for query
  }

}

bool queryExists(){		//return a boolean for if the word in query is in the dictionary
  for(string s: query){
    if(isThere(s)){
      return true;
    }
  }
  return false;
}

void printInstructions(){	// print out instructions
 	cout<<"Instructions:"<<endl;
 	cout<<"\t help (h) :  \t\t     show these instructions again\n"<<endl;
 	cout<<"\t Start Search(search or \"1\"): start input query,\n\t\t\t\t"<<endl;
 	cout<<"\n\t quit (q): \t\t     quit program"<<endl;
}
/*
 * Welcome screen
 * Ask user's input to go through instructions.
 */
void runCmdLineProgram(){

  cout<<"\n**Welcome to Abraham, Tyler and Qichao's Advanced Search Program**\n"<<endl;
  printInstructions();
  vector<string> usrInput;
  char input[100];
  cout<<"Please Enter (h for help):";
  cin.getline(input,sizeof(input));

  for(unsigned int i=0;i<100;i++){
    if(input[i]<91 && input[i]>64)//convert string to all lower case
      input[i]+=32;
  }
  usrInput.push_back(input);
	while(usrInput[0].compare("q")!=0 && usrInput[0].compare("quit")!=0){
    		RECURS=0;
		if(usrInput[0].compare("help")==0 || usrInput[0].compare("h")==0){
			printInstructions();
			cout<<"Please Enter:";
      			usrInput.pop_back();
			cin.getline(input,sizeof(input));
      			for(unsigned int i=0;i<100;i++){
        			if(input[i]<91 && input[i]>64)//convert string to all lower case
          			input[i]+=32;
      			}
      			usrInput.push_back(input);
		}
		else if(usrInput[0].compare("search")==0 || usrInput[0].compare("1")==0){
			inputQuery();
      			for(unsigned int j=0; j<dict.size();j++){
        			frequency[0][j]=getQueryFrequency(dict[j])/query.size();//for query
      			}
			search();
			cout<<"Please Enter (h for help):";
      			usrInput.pop_back();
      			cin.getline(input,sizeof(input));
      			for(unsigned int i=0;i<100;i++){
        			if(input[i]<91 && input[i]>64)//convert string to all lower case
          			input[i]+=32;
      			}
      			usrInput.push_back(input);
		}
		else{
			cout<<"\n**Invalid Input, try again."<<endl;
			cout<<"Please Enter (h for help):";
      			usrInput.pop_back();
      			cin.getline(input,sizeof(input));
      			for(unsigned int i=0;i<100;i++){
        			if(input[i]<91 && input[i]>64)//convert string to all lower case
          			input[i]+=32;
      			}
      			usrInput.push_back(input);
		}
	}//end while
	cout<<"Bye Bye"<<endl;
}
