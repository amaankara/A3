#include "GenStack.h"
#include <iostream>
#include <fstream>

//declaring gloab variables
using namespace std;
//creates stack to hold brackets
GenStack<char> dataS(10);
//creates stack to hold line No of corresponding brackets
GenStack<int> lineS(10);

bool checkDelim(){
  //int errorCount = 0
  //loop until the stack isEmpty
  while(dataS.isEmpty()==0){
    //max size of stack
    int MaxSize = dataS.mSize;
    //temp stack to hold brackets
    GenStack<char> tempData(MaxSize);
    //temp stack to hold line number
    GenStack<int> tempLine(MaxSize);
    //reverse the position of elements in stack so it can check brackets from start of code until the end
    for(int i =0;i<MaxSize;++i){
      tempData.push(dataS.pop());
      tempLine.push(lineS.pop());
    }

    //pop bracket and line number into variables
    char parent = tempData.pop();
    int lineNO = tempLine.pop();

    //check corresponding bracket because the last element in the current stack will correspond to first bracket
    for(int i=0; i<tempData.mSize;++i){
      dataS.push(tempData.pop());
      lineS.push(tempLine.pop());
    }

    //checking the conditions for Errors
    if(parent =='{'){
      if(dataS.peek()=='}'){
        char tempP = dataS.pop();
        int tempL = lineS.pop();
      }
      else{
        cout<<"Line " << lineS.peek() << "expects }" << endl;
        //errorCount++;
        return false;
      }
    }
    else if(parent =='}'){
        cout<<"ERROR, invalid } on line " << lineNO;
        //errorCount++;
        return false;
    }
    else if(parent =='('){
      if(dataS.peek()==')'){
        char tempP = dataS.pop();
        int tempL = lineS.pop();
      }
      else{
        cout<<"Line " << lineS.peek() << "expects )" << endl;
        //errorCount++;
        return false;
      }
    }
    else if(parent==')'){
      cout<<"ERROR, invalid ) on line " << lineNO;
      //errorCount++;
      return false;
    }
    else if(parent =='['){
      if(dataS.peek()==']'){
        char tempP = dataS.pop();
        int tempL = lineS.pop();
      }
      else{
        cout<<"Line " << lineS.peek() << "expects ]" << endl;
        //errorCount++;
        return false;
      }
    }
    else if(parent == ']'){
      cout<<"ERROR, invalid ) on line " << lineNO;
      //errorCount++;
      return false;
    }
  }
  return true;
}



int main(int argc, char** argv){
  //creates string to hold filename
  string filename="";
  if(argc>=2){
    //taking the file name as a command line argument
    filename = argv[1];
  }
  //if no file name was entered
  else{
    cout<< "ERROR: Please enter file name as a command line argument" <<endl;
  }

  //open the file
  ifstream myfile;
  myfile.open(filename);
  string line ="";
  int lineCount = 0;
  //read from the file line by line
  while(getline(myfile, line)){
    lineCount++;
    for(int i =0; i<line.length();i++){
      //if it is a bracket, store in stack
      if((line[i]=='(') ||(line[i]==')') ||(line[i]=='[') ||(line[i]==']') ||(line[i]=='{') ||(line[i]=='}') ){
        //push to GenStack
        dataS.push(line[i]);
        //push line number to stack
        lineS.push(lineCount);
      }
    }
  }

  bool error = checkDelim();
  if(error==true){
    cout<<"There are no errors with the delimiters"<<endl;
    return 0;
  }
  else{
    cout<<"Check the above line and place the correct delimiters on the specified line number" << endl;
    return 0;
  }
}
