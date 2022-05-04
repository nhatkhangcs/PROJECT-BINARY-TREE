#include "./2a/2a.h"
#include <stack>

int countPropositions(string s){
  int count=0;
  int state=0;
  for(int i = 0;i<s.length();i++){
    if(isspace(s[i])||isOperator(s[i])){
    	state = 0; 
    }
    else if(state == 0){
    	state = 1;
    	++count;
    }
  }
  return count;
}
//////////////////////////////////////////////////////////////////
//Inserted
bool syntaxerrorspace(string s){
  for (int i = 0; i + 1 < s.length(); i++){
    if (s[i] == ' ' && s[i + 1] == ' ') return true;
  }
  return false;
}

bool checkoperand(string s){
  for (int i = 0; i + 1 < s.length(); i++){
    if (isalpha(s[i]) && isalpha(s[i + 2])) return true;
  }
  return false;
}
//////////////////////////////////////////////////////////////////

string removeSpace(string s){
  string removed;
  for(int i=0;i<s.length();i++){
    if(!isspace(s[i])) removed+=s[i];
  }
  return removed;
}

//////////////////////////////////////////////////////////////////

int numberOfOperators(string s){
  int count = 0;
  for(int i=0;i<s.length();i++){
    if(isOperator(s[i])&&s[i]!='('&&s[i]!=')') 
      count++;
  }
  return count;
}

string extractBrackets(string s){
  string extracted="";
  for(int i=0;i<s.length();i++){
    if(s[i]=='('||s[i]==')') extracted+=s[i];
  }
  return extracted;
}

bool balancedParentheses(string expr){
	stack<char> temp;
		for(int i=0;i<expr.length();i++){
			if(temp.empty()){
				temp.push(expr[i]);
			}
      
			else if((temp.top()=='('&& expr[i]==')') || (temp.top()=='{' && expr[i]=='}') || (temp.top()=='[' && expr[i]==']')){
				temp.pop();
			}
			else{
				temp.push(expr[i]);
			}
		}

		if(temp.empty()){
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
/////////////////////////////////////////////////////////////////
bool undefinedError(string str){
  for(int i=0;i<str.length();i++){
    if(isOperator(str[i])){
      if (precedence(str[i]) == 1 || precedence(str[i]) == 2){
          if (precedence(str[i]) == 1){// p&q -> r
            string temp = "";
            int j = i + 1;
            while(str[j] != '\0'){ 
              temp += str[j];
              j++;
            }
            return undefinedError(temp);
          }

          else if (precedence(str[i+1]) == 3){
            i++;
            continue;
          }
          else if(precedence(str[i])==2){
            if(precedence(str[i+2])==1){
              i+=2;
              continue;
            }
          } 
          else return true;
        }

      else if(precedence(str[i]) == 3 && (str[i+1] == '(' ||precedence(str[i+1])==3)){
        i++;
        continue;
      }

      return true;   
    }
  }
  return false;
}

bool multiOutputError(string str){
  for(int i=0;i<str.length();i++){
    if(isOperator(str[i])){
      if ((precedence(str[i]) == precedence(str[i + 2])) 
           && precedence(str[i]) != 1 
           && (str[i] != str[i+2])){
        return true;
      }
      else continue;
    }
  }
  return false;
}


////////////////////////////////////////////////////////////////////////
//Improved?
bool syntaxError1(string str){
    bool flag=false;
    //parentheses checkpoint
    if(!balancedParentheses(extractBrackets(str))) 
      flag = true;
    //no operator checkpoint
    else if(nxtOperatorIndex(str,0)==-1) 
      flag = true;
    //blank checkpoint
    else if(syntaxerrorspace(str)){ 
      flag = true;
    }
    else if(countPropositions(str)!=countPropositions(removeSpace(str)))
      flag = true;
    else if (checkoperand(str)){
      flag = true;
    }
    return flag;
}
////////////////////////////////////////////////////////////////////////

int logicalValidity(string str){
    //parenthesis:
    //blank:
    if(syntaxError1(str)) return 3;
    //precedence order:
    else if(multiOutputError(str)) return 2;
    //consecutive operators:
    else if(undefinedError(str)) return 1;
    return 0;
}

void errorMessage(string str){
  switch(logicalValidity(str)){
    case 1: cout << "undefined error";break;
    case 2: cout << "multiple output";break;
    case 3: cout << "syntax error";break;
    default: break;
  }
  
}