#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

bool isOperator(char c){
    return(!isalpha(c) && !isdigit(c) && c!=')' && c!='(' && (c == '+' || c == '-' || c == '*' || c == '/' || c == '^'));
}

int precedence(char C){
    if (C == '+' || C == '-')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else if (C == '^')
        return 3;
    return 0;
}

bool properFloatingPoint(string s){
  for(int i=0;i<s.length();i++){
    if(s[i]=='.'){
      if(!isdigit(s[i+1])) return false;
    }
  }
  return true;
}
string removeSpace(string s){
  string removed;
  for(int i=0;i<s.length();i++){
    if(!isspace(s[i])) removed+=s[i];
  }
  return removed;
}
int numberInString(string s){
  int count = 0;
  bool flag = false;
  for(int i=0;i<s.length();i++){
    if(isdigit(s[i])){
      if(flag==false) count++;
      flag = true;
    }
    else flag = false;
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
    bool flag=false;
    //parentheses checkpoint
    if(!balancedParentheses(extractBrackets(str))) 
      flag = true;
    //no operator checkpoint
    else if(nxtOperatorIndex(str,0)==-1) 
      flag = true;
    //blank checkpoint
    else if((numberInString(str)-numberInString(removeSpace(str)))!=0){ 
      flag = true;
    }
    //floating point checkpoint
    else if(!properFloatingPoint(str)) 
      flag = true;
    return flag;
}
int arithmeticValidity(string str){

    if(undefinedError(str)) return 1;

    else if(multiOutputError(str)) return 2;

    else if(syntaxError(str)) return 3;
    return 0;
}
bool errorMessage(string str){
  switch(arithmeticValidity(str)){
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
 
string infixToPostfix(string s){
    stack<char> st; 
    string result;
 
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') continue;
        char c = s[i];
        if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
            || (c >= '0' && c <= '9')) ||( c == '-' && s[i-1] == '(' ))
            result += c;
 

        else if (c == '(') st.push('(');
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
 
    return result;
}

string infixToPrefix(string infix){
    int l = infix.size();
    reverse(infix.begin(), infix.end());
    for (int i = 0; i < l; i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        }
        else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }
    string prefix = infixToPostfix(infix);
 
    reverse(prefix.begin(), prefix.end());
 
    return prefix;
}

int main(){
    string s;
    cout << "Please enter a infix-notation representation of an arithmetic expression: ";
    getline(cin,s);
    if(!errorMessage(s)) cout << "Infix ---> Prefix: " << infixToPrefix(s);
    return 0;
}