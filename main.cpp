#include <iostream>
#include <ofstream>
#include "project2/stem.cpp"
using namespace std;


int main(){
  string q;
  cout<<"Input Query String"<<endl;
  cin>>q>>endl;

  ofstream file;
  file.open("txt41.txt");
  int length=0;
  for(unsigned int i=0; i< q.size();i++){
    file << q[i];//writes each poreccessed word out individually
    length+=q[i].size();
    file<< " ";//space between words
    if(length>=80){
      file<<"\n";//new lines every 80 characters
      length=0;
    }
  }
  file.close();

}
