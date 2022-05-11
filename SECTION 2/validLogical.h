#include "./2a/2a.h"
#include <stack>

string removeSpace(string s){
  string removed;
  for(int i=0;i<s.length();i++){
    if(!isspace(s[i])) removed+=s[i];
  }

  return removed;
}

string noiseRemoved(string s){

  // s = removeSpace(s);
  string temp = "";
  for (int i = 0; i < s.length(); i++){
    if (s[i] == '(' && s[i+1] == ')'){
      i++;
    }

    else temp+=s[i];
  }

  /* nếu ( ) thì ổn không, có
  int i,j;
  for (i = 0; i < temp.length(); i++){
    if (temp[i] == '(') break;
  }

  for (j = temp.length(); j >= 0; j--){
    if (temp[j] == ')') break;
  }
  //////   ((p&q))
  //////   0123456
  for (int z = i + 1; z <= j - 1; z++){
    if (temp[z] == '(' && temp[j - i - z] == ')') {//temp[1]=) and temp[5]=')'
      temp.erase(z, z + 1);
  //////   (p&q))
      temp.erase(j - i - z,j - i - z + 1); 
  //////   (p&q)
    }
  }

  */

  return temp;
}


//
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
//Check if multiple space appears in the code, if there is, so it's error
// bool syntaxerrorspace(string s){
//   for (int i = 0; i + 1 < s.length(); i++){
//     if (s[i] == ' ' && s[i + 1] == ' ') return true;
//   }
//   return false;
// }


//////////////////////////////////////////////////////////////////

//remove


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
      if(isOperator(s[i])) return i;
  }
  return -1;
}
int nxtParenIndex(string s, int index){
  for(int i=index+1;i<s.length();i++){
      if(s[i] == ')' || s[i] == '(') return i;
  }
  return -1;
}
/////////////////////////////////////////////////////////////////


bool undefinedError(string str){
  int len = str.size();
  /*
    exceptions: !!p, p&!q, p>q>r, p&!!q, (p&q)|r
    !!p = [3,3,0];
    p&!q = [0,2,3,0];
    (p&q)|r = [-1,0,2,0,-1,2,0]
    p>q>r = [0,1,0,1,0]
    ===undefined error===
    p&&q = [0,2,2,0]
    p||q = [0,2,2,0]
    p|>q = [0,2,1,0]
  */
  int* pArr = new int[len]; //array of precedence
  for(int i = 0; i < len; i++){
    char c = str[i];
    switch(precedence(c)){
      case -1:
        pArr[i] = -1;
        break;
      case 1:
        pArr[i] = 1;
        break;
      case 2:
        pArr[i] = 2;
        break;
      case 3:
        pArr[i] = 3;
        break;
      default:
        pArr[i] = 0;
        break;
    }
  }
  for(int i = 0; i < len; i++){
    //error: 22, 12, 31
    //exceptions: 13, 
    if((pArr[i]==pArr[i+1]&&pArr[i]==2)
    || (pArr[i]==2 && pArr[i+1] == 1)
    || (pArr[i]==1&&pArr[i+1]==2)
    || (pArr[i]==3&&(pArr[i+1]==1||pArr[i+1]==2))
    ) return true;
  }
  return false;
}

bool multiOutputError(string str){
  for(int i = 0; i<str.length(); i++){
    if(
      isOperator(str[i])
      && ((precedence(str[nxtOperatorIndex(str,i)])==2
      && precedence(str[i]) == 2) || (precedence(str[nxtOperatorIndex(str,i)])==2
      && precedence(str[i]) == 1))
      && nxtOperatorIndex(str,i) != (i + 1)
    ){
      if (nxtParenIndex(str,i) != -1 
          && str[nxtOperatorIndex(str,i)] < str[nxtParenIndex(str,i)]
          ) 
        return true;
      else if (nxtParenIndex(str,i) == -1 ) 
        return true;
      
    }
  }
  return false;
}

////////////////////////////////////////////////////////////////////////
//Improved?
bool syntaxError(string str){
    //parentheses checkpoint
    if(!balancedParentheses(extractBrackets(str)))
    {
      return true;
    }
    
    //no operator checkpoint
    else if(nxtOperatorIndex(str,0)==-1&&countPropositions(str)!=0){
      return true;
    }
    
    //blank checkpoint
    // else if(syntaxerrorspace(str)) {
    //   return true;
    // }
      

    else if(countPropositions(str)!=countPropositions(removeSpace(str))){
      return true;
    }
    
    // else if (checkOperand(str) ){
    //   return true;//
    // }

    return false;
}
////////////////////////////////////////////////////////////////////////

int logicalValidity(string str){
    // if(str.empty()) return 0;
    //parenthesis:
    //blank:
    if(syntaxError(str)) return 3;
    //precedence order:
    else if(multiOutputError(removeSpace(str))) return 2;
    //consecutive operators:
    else if(undefinedError(removeSpace(str))) return 1;
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