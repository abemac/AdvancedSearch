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

  ofstream ofs;
  ofs.open("txt41.txt", out | trunc);
  ofs<<q;
  ofs.close();
}
