#include <iostream>
#include <ofstream>
#include "project2/stem.cpp"
<<<<<<< HEAD
#include "project1/graphMain.cpp"
#include "project1/Graph.h"
=======
using namespace std;

>>>>>>> 80b128581af302b8bfb668c6d4362bc00e047629

using namespace std;
int main(){
<<<<<<< HEAD
  stem();
  graphMain();
  cout<<isValidInput("cat")<<endl;
  return 0;
=======
  string q;
  cout<<"Input Query String"<<endl;
  cin>>q>>endl;

  ofstream ofs;
  ofs.open("txt41.txt", out | trunc);
  ofs<<q;
  ofs.close();

>>>>>>> 80b128581af302b8bfb668c6d4362bc00e047629
}
