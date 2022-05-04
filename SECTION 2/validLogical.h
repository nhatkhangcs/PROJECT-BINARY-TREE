#include "./2a/2a.h"
#include <stack>

string removeSpace(string s){
  string removed;
  for(int i=0;i<s.length();i++){
    if(!isspace(s[i])) removed+=s[i];
  }

  cout << removed << '\n';
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

  cout << temp << '\n';
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
      if(s[i]==')'||s[i]=='(') continue;
      if(isOperator(s[i])) return i;
  }
  return -1;
}

/////////////////////////////////////////////////////////////////
bool undefinedError(string str){
  for(int i=0;i<str.length();i++){
    if(isOperator(str[i]) && str[i] != '(' && str[i] != ')'){
      cout << str[i] << '\n';
      if (precedence(str[i]) == 1 || precedence(str[i]) == 2){
          if (precedence(str[i]) == 1){// p&q -> r
            string temp = "";
            int j = i + 1;
            while(str[j] != '\0'){ 
              temp += str[j];
              j++;
            }
            cout << temp << '\n';
            return undefinedError(temp);
          }

          else if (precedence(str[i+1]) == 3){
            cout << "fack" << '\n';
            i++;
            continue;
          }

          else if(precedence(str[i])==2){
            if(precedence(str[i+2])==1){
              cout << "damn it" << '\n';
              continue;
            }
          } 
          else return true;
        }

      else if(precedence(str[i]) == 3 && (str[i+1] == '(' ||precedence(str[i+1])==3)){
        i++;
        continue;
      }

      cout << "That's good Vo Manh Khang" << '\n';

      return true;   
    }
  }

  return false;
}

bool multiOutputError(string str){
  for(int i=0;i<str.length();i++){
    if(isOperator(str[i])){
      if ((precedence(str[i]) == precedence(str[i + 2])
           && precedence(str[i]) != 1 
           && (str[i] != str[i+2]) && str[i] != '(' && str[i] != ')')){
        return true;
      }
      else continue;
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
      cout << "BalancedParenthesis"<<endl;
      return true;
    }
    
    //no operator checkpoint
    else if(nxtOperatorIndex(str,0)==-1){
      cout << "nxOperatorIndex"<<endl;
      return true;
    }
    
    //blank checkpoint
    // else if(syntaxerrorspace(str)) {
    //   cout << "Error space" << '\n';
    //   return true;
    // }
      

    else if(countPropositions(str)!=countPropositions(removeSpace(str))){
      cout << "proposition mismatched"<<endl;
      return true;
    }
    
    // else if (checkOperand(str) ){
    //   cout << "Operand error" << '\n';
    //   return true;//
    // }

    return false;
}
////////////////////////////////////////////////////////////////////////

int logicalValidity(string str){
    if(str.empty()) return 0;
    //parenthesis:
    //blank:
    else if(syntaxError(str)) return 3;
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