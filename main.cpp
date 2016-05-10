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

int NUM_DOCS=40;

double **frequency;   //frequency[0] = query frequencies
//                       //frequency[1][0] = frequency of first document, word in dict[0]
//                       //frequency[1][1] = frequency of first document, word in dict[1]
//                       //frequency[2][1] = frequency of second document, word in dict[1]

void inputQuery();
void loadDict();
bool isThere(string word);
double getFrequency(int i, string word);
int wordCounts[40];

void search();
double computeDocRank(int docNum);
struct RANK{
  RANK(int doc_,int docRank_):doc{doc_},docRank{docRank_}{};
  int doc;
  int docRank;

};
bool RANKcompare(RANK lhs, RANK rhs);


void inputQuery();
int main(){
  //graphMain();
  //inputQuery();
  //stem();
  loadDict();
<<<<<<< HEAD
  double frequency[40][dict.size()];
  for(int i=0; i<NUM_DOCS; i++){
    for (int j=0; j<dict.size(); j++){
      frequency[i][j]=getFrequency(i, dict[j])/wordCounts[i];
=======
  frequency =new double*[40];
  for(unsigned int j=0;j<40;j++){
    frequency[j]=new double[dict.size()];
  }
  for (unsigned int i=0; i<40; i++){
    for(int j=0; j<dict.size();j++){
      frequency[i][j]= getFrequency(i,dict[j]);
>>>>>>> 240a39c0f0c9f734ab844e41fa3b205b7a2c3a00
    }
  }

  return 0;

}

void inputQuery(){
  string q;
  cout<<"Input Query String"<<endl;
  cin>>q;

  ofstream file;
  file.open("../texts/txt41.txt");
  file<<q;
  file.close();
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

    int count=0;
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
        count++;
        if(!isThere(word)){
          dict.push_back(word);
        }
        word="";
  	}
    wordCounts[i]=count;
    count=0;

  	textfile.close();

  }
}

bool isThere(string word){
  for(int i=0; i<dict.size(); i++){
    if(dict[i].compare(word)==0){
      return true;
    }
  }
  return false;

}
int getIndex(string word){
  for (int i=0; i<dict.size(); i++){
    if(dict[i].compare(word)==0){
      return i;
    }
  }
  return -1;

}
double getFrequency(int i, string word){
<<<<<<< HEAD
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
      if(x.compare(word)==0){
        count++;
      }
      x="";
  }

  textfile.close();
  return count;
=======

>>>>>>> 240a39c0f0c9f734ab844e41fa3b205b7a2c3a00
}


// double **frequency;   //frequency[0] = query frequencies
//                       //frequency[1][0] = frequency of first document, word in dict[0]
//                       //frequency[1][1] = frequency of first document, word in dict[1]
//                       //frequency[2][1] = frequency of second document, word in dict[1]



bool RANKcompare(RANK lhs, RANK rhs) { return lhs.docRank > rhs.docRank; }

void search(){
  RANK docRanks[NUM_DOCS];
  for(int i=1;i<NUM_DOCS;i++){
    docRanks[i]=RANK(i,computeDocRank(i));
  }
  sort(RANK,RANK+NUM_DOCS,RANKcompare);
  //check if below Threshold T

  cout<<"Document Ranking:"<<endl;
  cout<<docRanks[1].doc<<endl;
  cout<<docRanks[2].doc<<endl;
  cout<<docRanks[3].doc<<endl;
  cout<<docRanks[4].doc<<endl;
  cout<<docRanks[5].doc<<endl;
  cout<<docRanks[6].doc<<endl;




}


double computeDocRank(int docNum){
  double rank=0;
  for (int i = 0;i<dict.size();i++){
    rank+=(frequency[0][i]-frequency[docNum][i])*(frequency[0][i]-frequency[docNum][i]);
  }
  rank = sqrt(rank);
  return rank;
}



vector<string> loadsubtypes(vector<string> dirty){
  vector<string> clean;
  for(int i=0;i<dirty.size();i++){
    string line = dirty[i];
    int k=0;
    for(int j=0; j< line.size();j++){
        if(line[j] == '_'){
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
