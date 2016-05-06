#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "project1/Graph.h"
#include <sstream>
//#include "Node.h"
using namespace std;
vector<string> input=vector<string>();//vector stores all the input from text file
Graph graph= Graph();//graph
void readFile();//function reads text from file and store in input
void buildGraph();//function build Graph using input vector
void graphMain();

////////////////////////////////////////////////////
//fuctions used for the command line program
void printInstructions();//prints instructions for command line program
bool processUsrInput(string usrInput);//process user input
string formatInput(string usrInput); //formats string input to match our graph data
bool isValidInput(string usrInput);//checks if the input is valid
void runCmdLineProgram();
////////////////////////////////
void graphMain(){

	readFile();

	buildGraph();
  
}//end main


//main procedures


void readFile(){
	int x=0;
	char c;
	fstream textfile;
	textfile.open("graph_hyponymy.txt");

	while (!textfile.eof()){
		c=textfile.get();//assign a char to c
		while(c==' '){
			c=textfile.get();
		}
		input.push_back("");//create a new space for new word
		while((c!=',' && c!=':' && c!='\n') && !textfile.eof()){//split words by ',' ':' '\n'
			if(c==' ')c='_';//convert space to '_' inside the word
			else if(c<91 && c>64)//convert string to all lower case
				c+=32;
			if(c>=32 && c<=127)//make sure all charters are visible and make sense
				input[x]=input[x]+c;//build words char by char
			c=textfile.get();
		}
		if(c==':'){// add ':' at the end of word if there is one
			input[x]=input[x]+c;
		}
		if(input[x].back()=='_'){//delete useless '_' at the end of words
			input[x].pop_back();
		}
		x++;
	}

	textfile.close();
	input.pop_back();//remove the last char which is empty
}//end readFile()


void buildGraph(){
	unsigned int i=0;//index of vector
	while(i<input.size()){
		Node* n;//temp pointer of node

		if(!graph.containsVertice(input[i])){			//check if the graph has the node
														//with the same name, if no, add
														//to graph
			n = new Node(input[i]);						// assign the new node with i th string in vector input
			graph.addVertice(n);						// add n to the graph
		}//end if
		else{
			n=graph.findVertice(input[i]);				//if there is the node in graph
														//assign the node to the temp pointer n
		}//end else


		if(input[i].back()==':'){						//check if there is ':' at the back of the string
														//if yes jump to next index to add children to n

			i++;										//increase index by 1;
			while(i<input.size() && input[i].back()!=':'){
				if(!graph.containsVertice(input[i])){	//prevent duplication
					Node* n2=new Node(input[i]);
					graph.addVertice(n2);
					n->addChild(n2);
				}//end if
				else{//if the input string is in the graph, find it out add to the children list of n
					Node* n3 = graph.findVertice(input[i]);
					n->addChild(n3);
				}//end else
				i++;
			}//end while
		}//end if
	}//end while
}//end buildGraph()




///********************************
///********************************
///********************************
///********************************
///********************************
///********************************
///********************************
///********************************
///********************************
///********************************
///********************************
///********************************
//  ALL CODE PAST THIS POINT IS USED TO READ AND PROCESS INPUT
//  FOR THE COMMAND LINE PROGRAM.  IT IS NOT COMMENTED BECAUSE
//  IT IS NOT THE MAIN PART OF THIS PROJECT.


/*
 * Start screen
 */
void runCmdLineProgram(){
	bool goOn = true;
	cout<<"\n**Welcome to Abraham and Qichao's Taxonomy Graph Program**\n"<<endl;
	printInstructions();
	string usrInput;

	while(goOn){
			cout<<"\nEnter a command (h for help):";
			cin>>usrInput;
			goOn=processUsrInput(usrInput);

	}
}

/*
 * print Instructions
 */
void printInstructions(){
	cout<<"Instructions:"<<endl;
	cout<<"\t help (h) :  \t\t     show these instructions again"<<endl;
	cout<<"\t citeSubtypes (cst):   \t     cite the number of subtypes a certain order"<<endl;
	cout<<"\t numSubSpecies (nss): \t     find number of subspecies of a type"<<endl;
	cout<<"\t lowestCommonAncestor (lca): find lowest common ancsestor of \n\t\t\t\t     two types starting from another type"<<endl;
	cout<<"\n\t quit (q): \t\t     quit program"<<endl;
	cout<<"\n\t NOTE: use \"_\" for any spaces needed to input"<<endl;
	cout<<"\t NOTE: after each command is typed, prompts will appear to enter\n\t       parameters"<<endl;
}

/*
 * convert users input to machine readable data
 * and looping to show instruction until user quit
 */
bool processUsrInput(string usrInput){
	if(usrInput.compare("h")==0 || usrInput.compare("help")==0){
		printInstructions();
		return true;
	}
	else if(usrInput.compare("citeSubtypes")==0 || usrInput.compare("cst")==0){
		int num;
		string sp;
		string inp;
		int order;
		cout<<"\tEnter starting point (SP): ";
		cin>>inp;
		sp = formatInput(inp);
		while(!isValidInput(sp)){
			cout<<"\t**Invalid input"<<endl;
			cout<<"\tEnter starting point (SP): ";
			cin>>inp;
			sp = formatInput(inp);
		}
		cout<<"\tEnter max number of subTypes to find: ";
		cin >>inp;
		istringstream(inp)>> num;
		while(num<0){
			cout<<"\t**Invalid input"<<endl;
			cout<<"\tEnter max number of subTypes to find: ";
			cin >>inp;
			istringstream(inp)>> num;
		}
		cout<<"\tEnter order: ";
		cin>>inp;
		istringstream(inp)>> order;
		while(order<0){
			cout<<"\t**Invalid input"<<endl;
			cout<<"\tEnter order: ";
			cin>>inp;
			istringstream(inp)>> order;

		}
		cout<<"Result: \n"<<endl;
		graph.citeSubtypes(sp,num,order);
		return true;
	}
	else if(usrInput.compare("numSubSpecies")==0 || usrInput.compare("nss")==0){
		string sp;
		string inp;
		int order;
		cout<<"\tEnter starting point (SP): ";
		cin >>inp;
		sp=formatInput(inp);
		while(!isValidInput(sp)){
				cout<<"\t**Invalid input"<<endl;
				cout<<"\tEnter starting point (SP): ";
				cin >>inp;
				sp=formatInput(inp);
		}
		inputArg:
		cout<<"\tEnter max order (or \"ALL\" for all subspecies): ";
		cin >>inp;
		inp=formatInput(inp);
		if(inp.compare("all")==0){
			cout<<"Result:\n"<<endl;
			cout<<graph.numSubSpecies(sp)<< " total subspecies of "<<sp<<endl;
		}else{
			istringstream(inp)>>order;
			if(order<0 ||(order==0 && inp.compare("0")!=0)){
				cout<<"\t**Invalid input"<<endl;
				goto inputArg;
			}
			cout<<"Result:\n"<<endl;
			cout<<graph.numSubSpecies(sp,order)<<" subspecies of "<<sp<<" of order <= "<<order<<endl;

		}
		return true;

	}
	else if (usrInput.compare("lowestCommonAncestor")==0|| usrInput.compare("lca")==0){
		string inp;
		string sp03;
		string sp02;
		string sp01;
		cout<<"\tEnter starting point (SP01): ";
		cin>>inp;
		sp01=formatInput(inp);
		while(!isValidInput(sp01)){
			cout<<"\t**Invalid input"<<endl;
			cout<<"\tEnter starting point (SP01): ";
			cin>>inp;
			sp01=formatInput(inp);
		}
		cout<<"\tEnter SP02: ";
		cin>>inp;
		sp02=formatInput(inp);
		while(!isValidInput(sp02)){
			cout<<"\t**Invalid input"<<endl;
			cout<<"\tEnter SP02: ";
			cin>>inp;
			sp02=formatInput(inp);
		}
		cout<<"\tEnter SP03: ";
		cin>>inp;
		sp03=formatInput(inp);
		while(!isValidInput(sp03)){
			cout<<"\t**Invalid input"<<endl;
			cout<<"\tEnter SP03: ";
			cin>>inp;
			sp03=formatInput(inp);
		}
		cout<<"Result:\n"<<endl;
		graph.commonAncestor(sp01,sp02,sp03);
		return true;
	}

	else if (usrInput.compare("quit")==0 || usrInput.compare("q")==0){
		return false;
	}
	else {
		cout<<"\n**Invalid input"<<endl;
		return true;
	}
}

string formatInput(string usrInput){
	string returnString;
	for(char c: usrInput){
		if(c<91 && c>64)//convert string to all lower case
			c+=32;
		if(c>=32 && c<=127)//make sure all charters are visible and make sense
			returnString.push_back(c);//build word char by char
	}
	return returnString;
}

bool isValidInput(string usrInput){//check input if it is in the boundary
	bool returnVal=false;
	for(Node* n: *(graph.getVertices())){
		if((n->getName()).compare(usrInput)==0){
			returnVal=true;
		}
	}
	return returnVal;
}
