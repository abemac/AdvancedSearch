/*
 * Node.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: SuperG
 */
#include "project1/Node.h"
using namespace std;
Node::Node(string name2){
	/*
	 * check if there is ':' at the back
	 * if there is pop it.
	 */
	if(name2.back()==':'){
		name2.pop_back();
	}
	name=name2; //initialize name to name2
	visited=false;//initialize visited to false
}


string Node::getName(){
	return name;//return string name
}

list<Node*> Node::getChildren(){
	return children;//return the list of children
}

void Node::addChild(Node* child){
	children.push_back(child);// add a node to the back of the list
}
