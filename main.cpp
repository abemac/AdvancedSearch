#include "project2/stem.cpp"
#include "project1/graphMain.cpp"
#include "project1/Graph.h"
#include <ifstream>

using namespace std;
void readFiles();
void wordCount(vector<doubles> g);
vector<string> dict;
<<<<<<< HEAD
vector<double> counts;
=======
double frequency[];
int * docNum[];
void inputQuery();
void loadDict();
bool isThere(string word);


>>>>>>> 7c7e2776a06acf421f39effbcf12758cc147596f

void inputQuery();
int main(){
  graphMain();
<<<<<<< HEAD
  void inputQuery()
=======
  inputQuery();
>>>>>>> 7c7e2776a06acf421f39effbcf12758cc147596f
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

<<<<<<< HEAD

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



=======
void loadDict(){

}
bool isThere(string word){
  for(int i=0; i<dict.size(); i++){
    if(dict[i].compare(word)==0){
      return true;
    }
  }
>>>>>>> 7c7e2776a06acf421f39effbcf12758cc147596f
}
