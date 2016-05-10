#include "project2/stem.cpp"
#include "project1/graphMain.cpp"
#include "project1/Graph.h"
#include <ifstream>

using namespace std;
void readFiles();
void wordCount(vector<doubles> g);
vector<string> dict;
vector<double> counts;

void inputQuery();
int main(){
  graphMain();
  void inputQuery()
  stem();

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



}
