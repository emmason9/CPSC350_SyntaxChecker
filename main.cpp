/*
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350-01
Assignment 3: Syntax Checker
*/

#include "DelimiterSyntax.h"

int main(int argc, char** argv){

  DelimiterSyntax *SyntaxCheck = new DelimiterSyntax();

  SyntaxCheck->RunSyntaxCheck(argv[1]);

  delete SyntaxCheck;
}
