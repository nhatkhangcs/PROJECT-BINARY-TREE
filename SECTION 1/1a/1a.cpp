#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

bool isOperand(char x){
   return (isdigit(x) || isalpha(x));
}

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
int countOperands(string s){
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
    if(isOperator(s[i])) return i;
  }
  return -1;
}
bool undefinedError(string str){
  for(int i=0;i<str.length();i++){
    if(isOperator(str[i])){
      if(precedence(str[i])!=0&&precedence(str[i+1])!=0){
        if(precedence(str[i+1])!=1) 
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

    if(!balancedParentheses(extractBrackets(str))) 
      flag = true;

    else if(nxtOperatorIndex(str,0)==-1&&countOperands(str)!=1) 
      flag = true;

    else if((countOperands(str)!=countOperands(removeSpace(str)))){ 
      flag = true;
    }

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
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        if (isOperand(c))
          result+=c;

        else if (c == ' ' && s[i+1] != ' ') {
          if (result[result.length()-1] != ' ') result += c;
        }

        else if(precedence(c)==1
        &&(i==0||isOperator(s[i-2]))
        &&isOperand(s[i+1])){
          result += c;
          result += s[i+1]; 
          ++i;
        }

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
                    result = result + st.top() + " ";
                    st.pop();
                }
            }
            st.push(c);
        }
    }
 
    while (!st.empty()) {
        result = result + " " + st.top();
        st.pop();
    }

    return result;
}

string proReverse(string prefix){
  reverse(prefix.begin(), prefix.end());
  
    string buffer = "";
    string ans = "";

    int le = prefix.length();
    for (int i = 0; i < le; i++){
      if (prefix[i] != ' '){
        buffer += prefix[i];
      }

      else{
        reverse(buffer.begin(), buffer.end());
        ans += buffer + " ";
        buffer = "";
      }
    }
    
    reverse(buffer.begin(), buffer.end());
    ans += buffer;
    
    return ans;
}

string infixToPrefix(string infix){
    infix = proReverse(infix);
    int l = infix.size();
    stack<char> st; 
    string result = "";
    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (isOperand(c))
          result+=c;

        else if (c == ' ' && infix[i+1] != ' ') {
          if (result[result.length()-1] != ' ') result += c;
        }

        else if(precedence(c)==1
        &&(i==0||isOperator(infix[i-2]))
        &&isOperand(infix[i+1])){
          result += c;
          result += infix[i+1]; 
          ++i;
        }

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
                   && precedence(infix[i]) < precedence(st.top())) {
                if (c == '^' && st.top() == '^')
                    break;
                else {
                    result = result + st.top() + " ";
                    st.pop();
                }
            }
            st.push(c);
        }
    }
 
    while (!st.empty()) {
        result = result + " " + st.top();
        st.pop();
    }

    return proReverse(result);
}
    
int main(){
    string s;
    cout << "Please enter a infix-notation representation of an arithmetic expression: ";
    getline(cin,s);
    if(!errorMessage(s)) cout << "Infix ---> Prefix: " << removeSpace(infixToPrefix(s));
    return 0;
}