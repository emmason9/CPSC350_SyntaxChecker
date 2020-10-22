/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 3: Syntax Checker
*/

#include "DelimiterSyntax.h"
#include <algorithm> //for transform to lower

DelimiterSyntax :: DelimiterSyntax(){
  myFiles = new FileProcessor();
  currentLineNumber = 0;
  delimiterStack = new GenStack<char>();
  delimiterLineNumberStack = new GenStack<int>();
}

DelimiterSyntax :: ~DelimiterSyntax(){
  delete myFiles;
  delete delimiterStack;
}

//opens and runs each line of the given file as well as prompts user if they want to do it again
void DelimiterSyntax :: RunSyntaxCheck(string FileName){
  bool runAgainBool = true;
  string currentFileName = FileName;
  while(runAgainBool){
    string currentLine;
    bool errorBool = false;
    bool fileTest = myFiles->OpenReaderFile(currentFileName);
    if (!fileTest){ //if the reader can't opent the file
      cout<<"File name given is not readable. Try again."<<endl;
      errorBool = true;
    }
    //while there's no errors.
    while(getline(myFiles->Reader, currentLine) && !errorBool){
      currentLineNumber++;
      errorBool = CheckLine(currentLine);
      if(errorBool){
        break;
      }
    }
    if (delimiterStack->isEmpty() && !errorBool) {
      cout<<"No delimiter errors found!"<<endl;
    } else if (delimiterStack->isEmpty() == false){
      cout<<"Missing ending delimiter. Starts at line "<<delimiterLineNumberStack->pop()<<endl;
      break;
    }
    myFiles->Reader.close();
    runAgainBool = RunAgain();
    if(runAgainBool){
      //reset line number for next file
      currentLineNumber = 0;
      string userFileName;
      cout<<"What file name would you like to check?(please include the extention!) "<<endl;
      cin>>userFileName;
      cout<<"you said: "<<userFileName<<endl;
      currentFileName = userFileName;
      continue;
    }
  }//end of while loop
}

//returns T/F as to whether there is a deliimiter syntax error(t) or not(f).
bool DelimiterSyntax :: CheckLine(string line){
  char poppedDelimiter;
  //iterating through the line
  for(int i=0; i<line.length(); ++i){
    //check if the delimiter is in a char ex. '{' or not
    if(line[i-1] == '\'' && line[i+1] == '\''){
      continue;
    //trying to not count the delimiters that are chars/strings
    }

    //want to push any starting delimiters first!
    if(line[i] == '(' || line[i] == '{' || line[i] == '['){
      delimiterStack->push(line[i]);
      delimiterLineNumberStack->push(currentLineNumber);
    }
    //if we find any ending limiters, it should match with the top delimiter in the stack
    //checking ()
    if(line[i] == ')'){
      poppedDelimiter = delimiterStack->pop();
      if(poppedDelimiter != '('){
        if(poppedDelimiter == '{'){
          cout<<"Line "<<currentLineNumber<<":";
          cout<<" Error... expected '}' and found "<<line[i]<<endl;
          return true; //there is an error, so true
        } else if (poppedDelimiter == '['){
          cout<<"Line "<<currentLineNumber<<":";
          cout<<" Error... expected ']' and found "<<line[i]<<endl;
          return true; //there is an error, so true
        }
      } else {
        delimiterLineNumberStack->pop(); //getting rid of the line number
      }

      //checking {}
    } else if(line[i] == '}'){
      poppedDelimiter = delimiterStack->pop();
      if(poppedDelimiter != '{'){
        if(poppedDelimiter == '('){
          cout<<"Line "<<currentLineNumber<<":";
          cout<<" Error... expected ')' and found "<<line[i]<<endl;
          return true; //there is an error, so true
        } else if (poppedDelimiter == '['){
          cout<<"Line "<<currentLineNumber<<":";
          cout<<" Error... expected ']' and found "<<line[i]<<endl;
          return true; //there is an error, so true
        }
      } else {
        delimiterLineNumberStack->pop(); //getting rid of the line number
      }

      //checking []
    } else if(line[i] == ']'){
      poppedDelimiter = delimiterStack->pop();
      if(poppedDelimiter != '['){
        if(poppedDelimiter == '{'){
          cout<<"Line "<<currentLineNumber<<":";
          cout<<" Error... expected '}' and found "<<line[i]<<endl;
          return true; //there is an error, so true
        } else if (poppedDelimiter == '('){
          cout<<"Line "<<currentLineNumber<<":";
          cout<<" Error... expected ')' and found "<<line[i]<<endl;
          return true; //there is an error, so true
        }
      } else {
        delimiterLineNumberStack->pop(); //getting rid of the line number
      }
    }
  }//end of for loop
}

//asks user if they'd like to check another file with a different name
bool DelimiterSyntax :: RunAgain(){
  while(true){
    string userResponse;
    cout<<"Would you like to check another file?\n'yes' or 'no'"<<endl;
    cin>>userResponse;
    transform(userResponse.begin(), userResponse.end(), userResponse.begin(), :: tolower);
    if(userResponse == "yes"){
      return true;
      break;
    } else if (userResponse == "no" || userResponse == "quit"){
      return false;
      break;
    } else {
      cout<<"Couldn't recognize your input. Try again. You can also 'quit'"<<endl;
    }
  }//end of while loop
}
