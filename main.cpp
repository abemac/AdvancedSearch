#include "project2/stem.cpp"
#include "project1/graphMain.cpp"
#include "project1/Graph.h"
#include <cmath>
#include <alogrithm>
using namespace std;
void readFiles();
vector<string> dict;
vector<string>query;

int NUM_DOCS=40;

double **frequency;   //frequency[0] = query frequencies
                      //frequency[1][0] = frequency of first document, word in dict[0]
                      //frequency[1][1] = frequency of first document, word in dict[1]
                      //frequency[2][1] = frequency of second document, word in dict[1]

void inputQuery();
void loadDict();
bool isThere(string word);

void search();
double computeDocRank(int docNum);
bool RANKcompare(RANK lhs, RANK rhs);
struct RANK{
  RANK(int doc_,int docRank_):doc{doc_},docRank{docRank_}{};
  int docRank;
  int doc;
}

void inputQuery();
int main(){
  //graphMain();
  //inputQuery();
  //stem();

  loadDict();
  for (string i : dict){
    cout<<i<<endl;
  }
  cout<<dict.size()<<endl
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
  for(int i=1; i<40; i++){
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

    int x=0;
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
        if(!isThere(word)){
          dict.push_back(word);
        }
  			if(dict.size()==0)
  				dict.pop_back();
  			else{
  				x++;
  			}
        word="";
  	}
    cout<<"there"<<endl;
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
