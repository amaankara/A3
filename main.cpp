#include "GenStack.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv){
  string filename="";
  if(argc>=2){
    filename = argv[1];
  }
  else{
    cout<< "ERROR: Please enter file name as a command line argument" <<endl;
  }

  GenStack<char> dataS(10);
  GenStack<int> lineS(10);
  ifstream myfile;
  myfile.open(filename);
  string line ="";
  int lineCount = 0;
  while(getline(myfile, line)){
    lineCount++;
    for(int i =0; i<line.length();i++){
      if((line[i]=='(') ||(line[i]==')') ||(line[i]=='[') ||(line[i]==']') ||(line[i]=='{') ||(line[i]=='}') ){
        dataS.push(line[i]);
        lineS.push(lineCount);
      }
    }
  }

  int errorCount = 0
  while(dataS.isEmpty()==0){
    int MaxSize = dataS.mSize;
    GenStack<char> tempData(MaxSize);
    GenStack<int> tempLine(MaxSize);
    for(int i =0;i<MaxSize;++i){
      tempData.push(dataS.pop());
      tempLine.push(lineS.pop());
    }

    char parent = tempData.pop();
    int lineNO = tempLine.pop();

    for(int i=0; i<tempData.mSize;++i){
      dataS.push(tempData.pop());
      lineS.push(tempLine.pop());
    }

    if(parent =='{'){
      if(dataS.peek()=='}'){
        char tempP = dataS.pop();
        int tempL = lineS.pop();
      }
      else{
        cout<<"Line " << lineS.peek() << "expects }" << endl;
        errorCount++;
      }
    }
    else if(parent =='}'){
        cout<<"ERROR, invalid } on line " << lineNO;
        errorCount++;
    }
    else if(parent =='('){
      if(dataS.peek()==')'){
        char tempP = dataS.pop();
        int tempL = lineS.pop();
      }
      else{
        cout<<"Line " << lineS.peek() << "expects )" << endl;
        errorCount++;
      }
    }
    else if(parent==')'){
      cout<<"ERROR, invalid ) on line " << lineNO;
      errorCount++;
    }
    else if(parent =='['){
      if(dataS.peek()==']'){
        char tempP = dataS.pop();
        int tempL = lineS.pop();
      }
      else{
        cout<<"Line " << lineS.peek() << "expects ]" << endl;
        errorCount++;
      }
    }
    else if(parent == ']'){
      cout<<"ERROR, invalid ) on line " << lineNO;
      errorCount++;
    }


    // for(int i = 0; i<MaxSize;i++){
    //   tempData.push(dataS.pop());
    //   tempLine.push(lineS.pop())
    // }
    // if(parent == tempData.peek()){
    //   tempData.pop();
    //   tempLine.pop();
    // }
    // else{
    //   cout<< "There is a bracket missing "<<endl;
    //   cout<< "line no " << tempLine.peek() << "is missing a bracket" <<endl;
    //}
  }


  return 0;
}
