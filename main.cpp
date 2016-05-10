#include "project2/stem.cpp"
#include "project1/graphMain.cpp"
#include "project1/Graph.h"
using namespace std;
void readFiles();
int wordCount();
vector<string> dict;
double frequency[];
int * docNum[];
void inputQuery();
void readWords();



int main(){
  graphMain();
  inputQuery();
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

void read(){

}
