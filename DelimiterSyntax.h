/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 3: Syntax Checker
*/

#include "GenStack.h"
#include "FileProcessor.h"

class DelimiterSyntax{
  public:
    DelimiterSyntax();
    ~DelimiterSyntax();

    void RunSyntaxCheck(string FileName);

  private:
    FileProcessor *myFiles;
    int currentLineNumber;
    GenStack<char> *delimiterStack;
    GenStack<int> *delimiterLineNumberStack;

    bool CheckLine(string line);
    bool RunAgain();

};
