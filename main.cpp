#include <iostream>
#include "project2/stem.cpp"
#include "project1/graphMain.cpp"
#include "project1/Graph.h"

using namespace std;
int main(){
  stem();
  graphMain();
  cout<<isValidInput("cat")<<endl;
  return 0;
}
