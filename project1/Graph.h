/*
 * Graph.h
 *
 *  Created on: Apr 5, 2016
 *      Author: SuperG
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <string>
#include <vector>
#include "Node.h"
using namespace std;

/*
	Graph is our data structure used to represent the taxonomy graph
*/
class Graph{
private:
	vector<Node*> vertices;

	/*
		initializes all values needed for BFS, such as distanceFromSource,
		visited, parent.
	*/
	void initializeBFS();

	/*
		returns true if all vertices have been visited
	*/
	bool allVisited();
public:
	Graph();//Constructor
	~Graph();//Destructor

	/*
		adds a vertice of type Node* to this graph
	*/
	void addVertice(Node *n);

	/*
		prints a BFS of this graph
	*/
	void printBFS(int startIndex);

	/*
		returns true if this Graph contains 'name', false otherwise
	*/
	bool containsVertice(string name);

	/*
		finds and returns the vertice 'name', if it exists
	*/
	Node* findVertice(string name);

	/*
		finds and returns the first Non-visited vertice it finds. If all
		vertices are visited, it returns nullptr
	*/
	Node* findNonVisitedVertice();

	/*
		returns the vector of vertices in this graph
	*/
	vector<Node*>* getVertices();

	//methods to answer questions:

	/*
		starting from 'sp', prints out 'num' subtypes with distance from 'sp'
		equal to 'order'.
	*/
	vector<string> citeSubtypes(string sp,int num,int order);

	/*
		returns the number of subspecies of 'sp' that are a distance away from 'sp'
		less than or equal to 'order'
	*/
	int numSubSpecies(string sp,int order);

	/*
		returns the number of all subtypes of 'sp'
	*/
	int numSubSpecies(string sp);

	/*
		starting from 'sp1', it prints out the lowest common Ancestor of
		'sp2' and 'sp3'
	*/
	void commonAncestor(string sp1, string sp2,string sp3);


};



#endif /* GRAPH_H_ */
