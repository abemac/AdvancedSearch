#include <iostream>
#include <ofstream>
#include "project2/stem.cpp"
using namespace std;


int main(){
  string q;
  cout<<"Input Query String"<<endl;
  cin>>q>>endl;

  ofstream ofs;
  ofs.open("txt41.txt", out | trunc);
  ofs<<q;
  ofs.close();

}
