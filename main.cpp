#include "project2/stem.cpp"
#include "project1/graphMain.cpp"
#include "project1/Graph.h"
#include <cmath>
#include <algorithm>

using namespace std;
void readFiles();
vector<string> dict;
vector<string>query;
int getIndex(string word);
vector<string> splitString(vector<string> dirty);
vector<string> lastDoc;
int lastDocNum=-1;
const int MAX_RECUR_LIMIT = 3;
int RECURS=0;
double T = .6;
vector<string> addingSubtypes(vector<string> query);
void runCmdLineProgram();
void printInstructions();


int NUM_DOCS=40;

double **frequency;   //frequency[0] = query frequencies
//                       //frequency[1][0] = frequency of first document, word in dict[0]
//                       //frequency[1][1] = frequency of first document, word in dict[1]
//                       //frequency[2][1] = frequency of second document, word in dict[1]

void inputQuery();
void loadDict();
bool isThere(string word);
double getFrequency(int i, string word);
double getQueryFrequency(string word);
int wordCounts[41];
void addSubtypes();
struct RANK{
  int doc;
  double distance;

};
vector<RANK> search();
double computeDocDistance(int docNum);

bool RANKcompare(RANK lhs, RANK rhs);
void inputQuery();


int main(){
  graphMain();
  stem();
  loadDict();

  frequency =new double*[41];
  for(unsigned int j=0;j<41;j++){
    frequency[j]=new double[dict.size()];
  }
  for (unsigned int i=1; i<41; i++){
    for(unsigned int j=0; j<dict.size();j++){
      frequency[i][j]=getFrequency(i, dict[j])/wordCounts[i];
    }
  }
  runCmdLineProgram();
  // inputQuery();
  // for(unsigned int j=0; j<dict.size();j++){
  //   frequency[0][j]=getQueryFrequency(dict[j])/query.size();//for query
  // }
  // search();

return 0;
}

void inputQuery(){
  query.clear();
  char input[100];
  cout<<"Input Query String: ";
  cin.getline(input,sizeof(input));
  for(unsigned int i=0;i<100;i++){
    if(input[i]<91 && input[i]>64)//convert string to all lower case
      input[i]+=32;
  }
  vector<string> tmp;
  tmp.push_back(input);
  query = splitString(tmp);
  query = processQuery(query);
}
double getQueryFrequency(string word){
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
    if(os.compare("Windows")==0){
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
  	textfile.open(path);
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
        if(!isThere(word) && word.size()!=0){
          dict.push_back(word);
        }
        word="";
  	}
    wordCounts[i]=wordCount;
    wordCount=0;

  	textfile.close();

  }
}

bool isThere(string word){
  for(unsigned int i=0; i<dict.size(); i++){
    if(dict[i].compare(word)==0){
      return true;
    }
  }
  return false;

}
int getIndex(string word){
  for (unsigned int i=0; i<dict.size(); i++){
    if(dict[i].compare(word)==0){
      return i;
    }
  }
  return -1;

}



double getFrequency(int i, string word){
  if(lastDocNum==i){
    double count=0;
    for(string s : lastDoc){
      if(s.compare(word)==0){
        count++;
      }
    }
    return count;
  }

  lastDoc.clear();

  string path;
  if(os.compare("Windows")==0){
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
  while (!textfile.eof()){
      c=textfile.get();//assign a char to c
      while(c==' '){
        c=textfile.get();
      }
      //x.push_back("");//create a new space for new word
      while((c!=',' && c!=' ' && c!='\n') && !textfile.eof()){//split words by ',' ' ' '\n'

        if(c>=97&& c<=122)//only include letters
          x=x+c;//build words char by char
        c=textfile.get();
      }
      lastDoc.push_back(x);
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



bool RANKcompare(const RANK lhs, const RANK rhs) { return lhs.distance < rhs.distance; }

vector<RANK> search(){
  vector<RANK> docRanks;
  for(int i=1;i<41;i++){
    RANK tmp;
    tmp.doc=i;
    tmp.distance=computeDocDistance(i);
    docRanks.push_back(tmp);
  }
  sort(docRanks.begin(),docRanks.end(),RANKcompare);
  //check if below Threshold T

  if(docRanks[0].distance > T && RECURS< MAX_RECUR_LIMIT){
    RECURS++;
    addSubtypes();
    docRanks=search();

  }else{
    cout<<"Document Ranking:"<<endl;
    cout<<docRanks[0].doc<<": "<<docRanks[0].distance<<endl;
    cout<<docRanks[1].doc<<": "<<docRanks[1].distance<<endl;
    cout<<docRanks[2].doc<<": "<<docRanks[2].distance<<endl;
    cout<<docRanks[3].doc<<": "<<docRanks[3].distance<<endl;
    cout<<docRanks[4].doc<<": "<<docRanks[4].distance<<endl;
    cout<<docRanks[5].doc<<": "<<docRanks[5].distance<<endl;
  }
  return docRanks;

}


double computeDocDistance(int docNum){
  double distance=0;
  for (unsigned int i = 0;i<dict.size();i++){
    distance+=(frequency[0][i]-frequency[docNum][i])*(frequency[0][i]-frequency[docNum][i]);
  }
  distance = sqrt(distance);
  return distance;
}



vector<string> splitString(vector<string> dirty){
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

void addSubtypes(){
  vector<string> additions;
  vector<string> temp;

  for(unsigned int i =0; i< query.size();i++){
      temp= graph.citeSubtypes(query[i],3,1);
      for(unsigned int j=0;j<temp.size();j++){
        if(additions.size() < 3){
          additions.push_back(temp[j]);
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
  for(unsigned int k =0; k < clean.size(); k++){
    query.push_back(clean[k]);
  }
  processQuery(query);
  for(unsigned int j=0; j<dict.size();j++){
    frequency[0][j]=getQueryFrequency(dict[j])/query.size();//for query
  }

}

void printInstructions(){
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
