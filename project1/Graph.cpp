/*
 * Graph.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: SuperG
 */


#include "Graph.h"
#include <iostream>
#include <list>
#include <climits>
using namespace std;

/**
  ******See header file for function documention*****
**/


Graph::Graph(){
    vertices= vector<Node*>();  //initializes the vector of vertices
}
Graph::~Graph(){
    for(Node*n : vertices){
      delete n;
    }
}

void Graph::addVertice(Node*n){
  vertices.push_back(n);  //adds to end of the vector
}

void Graph::printBFS(int startIndex){
  initializeBFS();
  list<Node*> queue = list<Node*>();
  queue.push_front(vertices[startIndex]);
  while(queue.size()!=0){
    Node* tmp=queue.back();   //takes the next Node to be processed from the queue
    cout<<tmp->getName()<<endl;//prints this node
    list<Node*> children = tmp->getChildren();
    tmp->visited=true;        //marks the current Node as visited
    for(Node* n: children){
      if(n->visited==false)
        queue.push_front(n);  //enques all unvisited children
    }
    queue.pop_back();  //deletes the current Node from the queue

  }

  while(!allVisited()){  //needed in case the graph is not connected
                        //BFS,  same as above
    queue.push_front(findNonVisitedVertice());
    while(queue.size()!=0){
      Node* tmp=queue.back();
      cout<<tmp->getName()<<endl;
      list<Node*> children = tmp->getChildren();
      tmp->visited=true;
      for(Node* n: children){
        if(n->visited==false)
          queue.push_front(n);
      }
      queue.pop_back();

    }
  }

}

//answer to question methods
//*******************************
vector<string> Graph::citeSubtypes(string sp,int num,int order){
  initializeBFS();
  vector<string> sub;
  list<Node*> queue = list<Node*>();
  queue.push_front(findVertice(sp));//finds the vertice with name 'sp'
  queue.back()->distanceFromSource=0;//'sp' is 0 away from itself
  int numPrinted=0;// to keep track of the number of subtypes found
  if(order==0){
	  //cout<<"\t0 subspecies have found at order 0"<<endl;
  }
  else{
    bool stop=false;
	  while(queue.size()!=0 && !stop){//only need to go until numPrinted=num
		  Node* tmp=queue.back();
		  list<Node*> children = tmp->getChildren();
		  tmp->visited=true;
		  for(Node* n: children){//enques all Non-visited children
			  if(n->visited==false)
				  queue.push_front(n);
			  n->distanceFromSource=tmp->distanceFromSource+1;//sets the distance from 'sp'
			  if(n->distanceFromSource==order && numPrinted<num){ //prints this vertice if applicable
				  //cout<<n->getName()<<" (order: "<<n->distanceFromSource<<")"<<endl;
          sub.push_back(n->getName());
				  numPrinted++;
          if(numPrinted >= num){
            stop=true;
          }
			  }

		  }
      if(tmp->distanceFromSource > order){
        stop=true;
      }
		  queue.pop_back();

	  }
  }
return sub;
}

int Graph::numSubSpecies(string sp,int order){
  initializeBFS();
  list<Node*> queue = list<Node*>();
  queue.push_front(findVertice(sp));//finds the vertice with name 'sp' and pushes to queue
  queue.back()->distanceFromSource=0;
  int count=0;  //keeps track of the number of subspecies
  bool stop=false;
  while(queue.size()!=0 && !stop){
    Node* tmp=queue.back();
    list<Node*> children = tmp->getChildren();
    tmp->visited=true;
    for(Node* n: children){
      if(n->visited==false)
        queue.push_front(n);
        n->distanceFromSource=tmp->distanceFromSource+1;
        if(n->distanceFromSource<=order){
          count++;//increments the number of subspecies if applicable
        }
    }
    if(tmp->distanceFromSource>order){
      stop=true; //terminates BFS when order reached
    }
    queue.pop_back();

  }

  return count;


}
int Graph::numSubSpecies(string sp){
  initializeBFS();
  list<Node*> queue = list<Node*>();
  queue.push_front(findVertice(sp));//finds the vertice with name 'sp' and pushes to queue
  queue.back()->distanceFromSource=0;
  int count=0;//keeps track of number of subspecies

  while(queue.size()!=0){
    Node* tmp=queue.back();
    list<Node*> children = tmp->getChildren();
    tmp->visited=true;
    for(Node* n: children){
      if(n->visited==false)
        queue.push_front(n);
        n->distanceFromSource=tmp->distanceFromSource+1;
        count++;//always increments until BFS terminates
    }
    queue.pop_back();

  }

  return count;

}

void Graph::commonAncestor(string sp01, string sp02, string sp03){
  initializeBFS();
  list<Node*> queue = list<Node*>();
  queue.push_front(findVertice(sp01)); //finds sp01 and pushes to queue
  queue.back()->distanceFromSource=0;
  vector<string> p1;//used to store the path from sp02 to sp01
  vector<string> p2;//used to store the path from sp03 to sp01
  bool found1=false;//keeps track if sp02 has been found
  bool found2=false;//keeps track if sp03 has been found
  Node* sp2=nullptr;
  Node* sp3=nullptr;
  while(queue.size()!=0 && (!found1 || !found2)){//only need to do BFS until sp02 and sp03 have been found
    Node* tmp=queue.back();
    list<Node*> children = tmp->getChildren();
    tmp->visited=true;
    for(Node* n: children){
      if(n->visited==false){
        n->parent=tmp;
        queue.push_front(n);
        n->distanceFromSource=tmp->distanceFromSource+1;

        if(!found1 && (n->getName()).compare(sp02)==0){ //if sp02 is found
          found1=true;//sets flag
          sp2=n;//sets sp2 as this Node

        }
        if(!found2 && (n->getName()).compare(sp03)==0){//if sp03 is found
          found2=true;//sets flag
          sp3=n;//sets sp3 as this node
        }

      }
    }
    queue.pop_back();

  }

  //check if nullptr
  if(sp2==nullptr || sp3==nullptr){
    cout<<"no lowest common anscestor from starting point "<<sp01<<endl;
    return;
  }

  Node*tmp=sp2;
  while(tmp->parent!=nullptr){//stores the path from sp02 to sp01 in p1
    p1.push_back(tmp->parent->getName());
    tmp=tmp->parent;

  }

  tmp=sp3;
  while(tmp->parent!=nullptr){//stores the path from sp03 to sp01 in p2
    p2.push_back(tmp->parent->getName());
    tmp=tmp->parent;
  }
  //finds the lowest common ancestor, which will be the only first node that
  //this double for-loop finds
  for(string i:p1){
    for(string j:p2){
      if(i.compare(j)==0){
        cout<<"The lowest common ancestor is: "<<i<<endl;
        return;
      }
    }
  }
}



//******************************
//private methods


void Graph::initializeBFS(){
  for(Node* n:vertices){
    n->visited=false; //resests visited flag
    n->distanceFromSource=INT_MAX;//distance = Infinity
    n->parent=nullptr;    //clears parent
  }
}

bool Graph::allVisited(){
  for(Node* n: vertices){
    if(n->visited==false){
      return false;//any is not visited, returns false
    }
  }

  return true;    //otherwise, returns true

}

Node* Graph::findNonVisitedVertice(){
  for(Node* n: vertices){
    if(n->visited==false){
      return n;   //first found non-visited vertice is return
    }
  }
  return nullptr;//all vertices are visited
}

bool Graph::containsVertice(string name){
  for(Node *n : vertices){
    if((n->getName()).compare(name)==0){//returns true if the names are equal
      return true;
    }else if (name.back()==':'){//removes colon from end if needed and re-compares
      string name2 = name.substr(0,name.size()-1);
      if((n->getName()).compare(name2)==0){
        return true;
      }
    }
  }
  return false;
}

Node* Graph::findVertice(string name){
  if(name.back()==':'){//removes colon from end if needed
    name= name.substr(0,name.size()-1);
  }

  for(Node *n : vertices){
    if((n->getName()).compare(name)==0){
      return n; //if n-name == name, return n
    }
  }

  return nullptr;


}

vector<Node*>* Graph::getVertices(){
	return &vertices;
}
