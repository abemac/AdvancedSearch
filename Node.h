/*
 * Node.h
 *
 *  Created on: 2016年4月4日
 *      Author: SuperG
 */

#ifndef NODE_H_
#define NODE_H_
#include <string>
#include <list>
using namespace std;

class Node{
private:
	string name;//string name
	list<Node*> children;//list of pointers to children

public:
	/*
	 * Constructor
	 * @parameter string name2
	 */
	Node(string name2);

	/*
	 * getName()
	 * return a string which is the name
	 * of the Node
	 */
	string getName();

	/*
	 * getChildren()
	 * return the list of all the children
	 */
	list<Node*> getChildren();

	/*
	 * addChild(Node * child)
	 * void function
	 * @parameter a point of the parent node
	 * Add a child to the list of parent node
	 */
	void addChild(Node* child);


	bool visited; // boolean value shows if the node has visited


	int distanceFromSource; //integer value shows the distance from sp01
							//using only in question3
	Node* parent;			//pointer of the node's parent
};





#endif /* NODE_H_ */
