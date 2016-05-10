#include "project2/stem.cpp"
#include "project1/graphMain.cpp"
#include "project1/Graph.h"
#include <cmath>
using namespace std;
void readFiles();

void wordCount(vector<double> g);
vector<string> dict;
vector<string>query;

<<<<<<< HEAD
int NUM_DOCS=40;

double **frequency;   //frequency[0] = query frequencies
                      //frequency[1][0] = frequency of first document, word in dict[0]
                      //frequency[1][1] = frequency of first document, word in dict[1]
                      //frequency[2][1] = frequency of second document, word in dict[1]
=======

double frequency[][]; //frequency[0][0] = frequency of first document, word in dict[0]
                      //frequency[0][1] = frequency of first document, word in dict[1]
                      //frequency[1][1] = frequency of second document, word in dict[1]
>>>>>>> ced910bb7ddce7690d9584d3d3f7baafa2f40e49

void inputQuery();
void loadDict();
bool isThere(string word);

void search();
<<<<<<< HEAD
double computeDocRank(int docNum);
=======
void computeDocRank(int doc,int word);
>>>>>>> ced910bb7ddce7690d9584d3d3f7baafa2f40e49

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


<<<<<<< HEAD
=======
// double frequency[][]; //frequency[0][0] = frequency of first document, word in dict[0]
//                       //frequency[0][1] = frequency of first document, word in dict[1]
//                       //frequency[1][1] = frequency of second document, word in dict[1]

void search(){
  vector<double> docRanks;
>>>>>>> ced910bb7ddce7690d9584d3d3f7baafa2f40e49

void search(){
  struct RANK{
    int doc;
    int docRank;
  }
  vector<RANK> docRanks;
  for(int i=1;i<NUM_DOCS;i++){
    
  }
}
<<<<<<< HEAD

double computeDocRank(int docNum){
  double rank=0;
  for (int i = 0;i<dict.size();i++){
    rank+=(frequency[0][i]-frequency[docNum][i])*(frequency[0][i]-frequency[docNum][i]);
  }
  rank = sqrt(rank);
  return rank;
}
=======
>>>>>>> ced910bb7ddce7690d9584d3d3f7baafa2f40e49
