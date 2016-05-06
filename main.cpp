#include "project2/stem.cpp"
#include "project1/graphMain.cpp"
#include "project1/Graph.h"
using namespace std;

int main(){

  stem();
  graphMain();
  string q;
  cout<<"Input Query String"<<endl;
<<<<<<< HEAD
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

=======
  cin>>q;

  ofstream ofs;
  ofs.open("txt41.txt", out | trunc);
  ofs<<q;
  ofs.close();
>>>>>>> 093a5ab8cc35a649c403f360a483f447db5a138f
}
