#include "./1a/1a.h"
int nxtOperatorIndex(string s, int index){
  for(int i=index+1;i<s.length();i++){
      if(isOperator(s[i])) return i;
  }
  return -1;
}
bool undefinedError(string str){
  for(int i=0;i<str.length();i++){
    if(isOperator(str[i])&&isOperator(str[nxtOperatorIndex(str,i)])){
      if(precedence(str[i])==1&&precedence(str[nxtOperatorIndex(str,i)])==1) continue;
      else return true;
    }// 4+)(3*2
  }
  return false;
}
bool multiOutputError(string str){
  for(int i=0;i<str.length();i++){
    if(isOperator(str[i])&&isOperator(str[nxtOperatorIndex(str,i)])){
      char op1 = str[i];
      char op2 = str[nxtOperatorIndex(str,i)];
      if(op1=='/'||op1=='-'){
        if(precedence(op1)==precedence(op2)) return true;
      }
    }
  }
  return false;
}
bool syntaxError(string str){
    int opening=0;
    int closing=0;
    for(int i=0;i<str.length();i++){
        if(str[i]=='(') opening++;
        else if(str[i]==')') closing++;
    }
    if(opening != closing) return true;
    return false;
}
int validity(string str){
    //consecutive operators:
    if(undefinedError(str)) return 1;
    //precedence order:
    else if(multiOutputError(str)) return 2;
    //parenthesis:
    else if(syntaxError(str)) return 3;
    //floating point:
    //blank:
    
    return 0;
}
void errorMessage(string str){
  switch(validity(str)){
    case 1: cout << "undefined error";break;
    case 2: cout << "multiple output";break;
    case 3: cout << "syntax error";break;
    default: break;
  }
  
}



