#include "project2/stem.cpp"
#include "project1/graphMain.cpp"
#include "project1/Graph.h"
using namespace std;

int main(){

  stem();
  graphMain();
  string q;
  cout<<"Input Query String"<<endl;
  cin>>q;

  ofstream file;
  file.open("txt41.txt");
  int length=0;
  for(unsigned int i=0; i< q.size();i++){
    file << q[i];//writes each poreccessed word out individually
    length+=1;
    file<< " ";//space between words
    if(length>=80){
      file<<"\n";//new lines every 80 characters
      length=0;
    }
  }
  file.close();

}
