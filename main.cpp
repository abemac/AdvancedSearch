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
  file>>q;
  file.close();

}
