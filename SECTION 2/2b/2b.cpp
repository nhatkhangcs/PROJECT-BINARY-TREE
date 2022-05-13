/* C++ implementation to convert
infix expression to postfix*/
 
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;
 
int precedence(char c){
    if (c == '-')
        return 3;
    else if (c == '|' || c == '^' || c == '+')
        return 2;
    else if (c == '>')
        return 1;
    else
        return -1;
}

bool isOperator(char c){
    return(!isalpha(c) && !isdigit(c) && c!=')' && c!='(' && (c == '+' || c == '-' || c == '&' || c == '|' || c == '>'));
}

string removeSpace(string s){
  string removed;
  for(int i=0;i<s.length();i++){
    if(!isspace(s[i])) removed+=s[i];
  }

  return removed;
}

string noiseRemoved(string s){

  string temp = "";
  for (int i = 0; i < s.length(); i++){
    if (s[i] == '(' && s[i+1] == ')'){
      i++;
    }

    else temp+=s[i];
  }

  return temp;
}

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

bool undefinedError(string str){
  int len = str.size();
  int* pArr = new int[len];
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
    if(isOperator(str[i])
      && ((precedence(str[i])==2
      && precedence(str[nxtOperatorIndex(str,i)]) == 2) 
      || (precedence(str[i])==1
      && precedence(str[nxtOperatorIndex(str,i)]) == 2))
      && nxtOperatorIndex(str,i) != (i + 1)
    ){
      if (nxtParenIndex(str,i) == -1 ) 
        return true;
      else if (nxtParenIndex(str,i) != -1 
          && str[nxtOperatorIndex(str,i)] < str[nxtParenIndex(str,i)]
          ) 
        return true;
      
    }
  }
  return false;
}

bool syntaxError(string str){
    if(!balancedParentheses(extractBrackets(str))){

      return true;
    }
    
    else if(nxtOperatorIndex(str,0)==-1&&countPropositions(str)!=0){

      return true;
    }

    else if(countPropositions(str)!=countPropositions(removeSpace(str))){

      return true;
    }

    for (int i = 0; i < str.length(); i++){
      if (!isOperator(str[i])) return true;
    }

    return false;
}

int logicalValidity(string str){

    if(syntaxError(str)) return 3;

    else if(multiOutputError(removeSpace(str))) return 2;

    else if(undefinedError(removeSpace(str))) return 1;
    return 0;
}

bool errorMessage(string str){
  switch(logicalValidity(str)){
    case 1: cout << "undefined error";
            return true;
            break;
    case 2: cout << "multiple output";
            return true;
            break;
    case 3: cout << "syntax error";
            return true;
            break;
    default: return false;
  }
}
 
void infixToPostfix(string s)
{
 
    stack<char> st; 
    string result;
 
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') continue;
        
        char c = s[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            result += c;
 
        else if (c == '(')
            st.push('(');
 
        else if (c == ')') {
            while (st.top() != '(') {
                result += st.top();
                st.pop();
            }
            st.pop();
        }
 
        else {
            while (!st.empty()
                   && precedence(s[i]) <= precedence(st.top())) {
                if (c == '^' && st.top() == '^')
                    break;
                else {
                    result += st.top();
                    st.pop();
                }
            }
            st.push(c);
        }
    }
 
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
 
    cout << result << endl;
}

int main()
{
    string s;
    cout << "Please enter a infix-notation representation of an arithmetic expression: ";
    getline(cin,s);
    cout << "Infix ---> Postfix: ";
    infixToPostfix(s);
    return 0;
}