#include "./1a/1a.h"
string extractBrackets(string s){
  string extracted="";
  for(int i=0;i<s.length();i++){
    if(s[i]=='('||s[i]==')') extracted+=s[i];
  }
  return extracted;
}
bool balancedParentheses(string expr)
{
	stack<char> temp;
		for(int i=0;i<expr.length();i++)
		{
			if(temp.empty())
			{
				temp.push(expr[i]);
			}
			else if((temp.top()=='('&& expr[i]==')') || (temp.top()=='{' && expr[i]=='}') || (temp.top()=='[' && expr[i]==']'))
			{
				temp.pop();
			}
			else
			{
				temp.push(expr[i]);
			}
		}
		if(temp.empty())
		{
			return true;
		}
		return false;
}
int nxtOperatorIndex(string s, int index){
  for(int i=index+1;i<s.length();i++){
      if(s[i]==')'||s[i]=='(') continue;
      if(isOperator(s[i])) return i;
  }
  return -1;
}
bool undefinedError(string str){
  for(int i=0;i<str.length();i++){
    if(isOperator(str[i])){
      if(precedence(str[i])!=0&&precedence(str[i+1])!=0){
        if(!(precedence(str[i])==1&&precedence(str[i+1])==1)) 
          return true;
        else continue;
      }
    }
  }
  return false;
}
bool multiOutputError(string str){
  for(int i=0;i<str.length();i++){
    if(isOperator(str[i])){
      char op1 = str[i];
      char op2 = str[i+2];
      if(op1=='/'||op1=='-'){
        if(precedence(op1)==precedence(op2)) return true;
      }
    }
  }
  return false;
}
bool syntaxError(string str){
    //parentheses checkpoint
    if(balancedParentheses(extractBrackets(str))) return false;
    //floating point checkpoint
    if(nxtOperatorIndex(str,0)==-1) return true;
    //blank checkpoint
    
    return true;
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



