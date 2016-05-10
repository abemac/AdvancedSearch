#include "project2/stem.cpp"
#include "project1/graphMain.cpp"
#include "project1/Graph.h"

#include <vector>

#include <ifstream>


using namespace std;
void readFiles();
void wordCount(vector<doubles> g);
vector<string> dict;

double frequency[][]; //frequency[0][0] = frequency of first document, word in dict[0]

void inputQuery();
void loadDict();
bool isThere(string word);

void search();

void inputQuery();
int main(){
  graphMain();
  //inputQuery();
  stem();

  loadDict();
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


void  wordCount(){
  int total;
  string path;
  string line;
  string length;
  count=1;
  while(count < 42){

    if(fileNum<10){
      path="../corpus/txt0"+count+"_cleaned.txt";
    }
    else{
      path="../corpus/txt"+count+"_cleaned.txt";
    }

    ifstream myFile(path);
    if( myFile.is_open()){
      length=line.size();
      int i =0;
      while(i < length){

      }
    }
    else{
      cout<<"NOT FOUND"<<endl;
    }

    counts[i-1]=total;
    count++;
    total = 0;
}

void loadDict(){
  for(int i=0; i<40; i++){
    string path;
    if(os.compare("Windows")==0){
  		if(fileNum<10){
  			path="corpus\\txt0"+to_string(i+1)+"_cleaned.txt";
  		}
      else{
  			path="corpus\\txt"+to_string(i+1)+"_cleaned.txt";
  		}
  	}
    else{
  		if(fileNum<10){
  			path="corpus/txt0"+to_string(i+1)+"_cleaned.txt";
  		}else{
  			path="corpus/txt"+to_string(i+1)+"_cleaned.txt";
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
  	}

  	textfile.close();

  }
}
bool isThere(string word){
  for(int i=0; i<dict.size(); i++){
    if(dict[i].compare(word)==0){
      return true;
    }
  }

}





void search(){
  vector<double> docRanks;

}
