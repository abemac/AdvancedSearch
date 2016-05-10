#include "project2/stem.cpp"
#include "project1/graphMain.cpp"
#include "project1/Graph.h"
using namespace std;
void readFiles();
<<<<<<< HEAD
void wordCount(vector<double> g);
vector<string> dict;

//double frequency[][]; //frequency[0][0] = frequency of first document, word in dict[0]
=======
vector<string> dict;

double **frequency;  //frequency[0][0] = frequency of first document, word in dict[0]
                      //frequency[0][1] = frequency of first document, word in dict[1]
                      //frequency[1][1] = frequency of second document, word in dict[1]
>>>>>>> 7e48045c3da61f3bd6b37f59a0cdd0530553dfd7

//create for number of docs: frequency = new double *[numDocs];
//add frequencies to document 1: frequencies[0]= new double[numberOfWords];



void inputQuery();
void loadDict();
bool isThere(string word);

void search();
double computeDocRank(int doc);

void inputQuery();
int main(){
  graphMain();
  //inputQuery();
  stem();

  loadDict();
  cout<<dict.size()<<endl;
  return 0;

}

void inputQuery(){
  string q;
  cout<<"Input Query String"<<endl;
  cin>>q;

  ofstream file;
  file.open("../texts/txt41.txt");
  file<<q;
  file.close();
}

<<<<<<< HEAD
=======


>>>>>>> 7e48045c3da61f3bd6b37f59a0cdd0530553dfd7
void loadDict(){
  for(int i=0; i<40; i++){
    string path;
    if(os.compare("Windows")==0){
  		if(fileNum<10){
  			path="corpus\\txt0"+to_string(i+1)+"_cleaned.txt";
  		}
      else{
  			path="corpus\\txt"+to_string(i+1)+"_cleaned.txt";
  		}
  	}
    else{
  		if(fileNum<10){
  			path="corpus/txt0"+to_string(i+1)+"_cleaned.txt";
  		}else{
  			path="corpus/txt"+to_string(i+1)+"_cleaned.txt";
  		}
    }

    int x=0;
  	char c;
  	fstream textfile;
  	textfile.open(path);
    string word="";
  	while (!textfile.eof()){
  			c=textfile.get();//assign a char to c
  			while(c==' '){
  				c=textfile.get();
  			}
  			//word.push_back("");//create a new space for new word
  			while((c!=',' && c!=' ' && c!='\n') && !textfile.eof()){//split words by ',' ' ' '\n'

  				if(c>=97&& c<=122)//only include letters
  					word=word+c;//build words char by char
  				c=textfile.get();
  			}
        if(!isThere(word)){
          dict.push_back(word);
        }
  			if(dict.size()==0)
  				dict.pop_back();
  			else{
  				x++;
  			}
  	}

  	textfile.close();

  }
}
bool isThere(string word){
  for(int i=0; i<dict.size(); i++){
    if(dict[i].compare(word)==0){
      return true;
    }
  }

}



// double frequency[][]; //frequency[0][0] = frequency of first document, word in dict[0]
//                       //frequency[0][1] = frequency of first document, word in dict[1]
//                       //frequency[1][1] = frequency of second document, word in dict[1]

void search(){
  vector<double> docRanks;

}

double computeDocRank(int doc){

}
