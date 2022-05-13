// C++ program to evaluate value of a postfix
// expression having multiple digit operands
#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <cmath>
#include <utility>
#include <algorithm>
#include <fstream>
#include "dictionary.txt"

using namespace std;

bool isOperand(char x)
{
   return (x >= 'a' && x <= 'z') ||
          (x >= 'A' && x <= 'Z');
}

int precedence(char c)
{
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

class Stack
{
    public:
    int top;
    unsigned capacity;
    double* array;
};
 
// Stack Operations
Stack* createStack( unsigned capacity )
{
    Stack* stack = new Stack();
 
    if (!stack) return NULL;
 
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = new double[(stack->capacity * sizeof(double))];
 
    if (!stack->array) return NULL;
 
    return stack;
}
 
double isEmpty(Stack* stack)
{
    return stack->top == -1 ;
}
 
double peek(Stack* stack)
{
    return stack->array[stack->top];
}
 
double pop(Stack* stack)
{
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}
 
void push(Stack* stack,double op)
{
    stack->array[++stack->top] = op;
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

string postToInfix(string exp){
    stack<string> s;
 
    for (int i=0; exp[i]!='\0'; i++)
    {
        if (isOperand(exp[i]))
        {
           string op(1, exp[i]);
           s.push(op);
        }

        else
        {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            s.push("(" + op2 + exp[i] +
                   op1 + ")");
        }
    }

    return s.top();
}

string preToInfix(string pre_exp) {
  stack<string> s;
 
  int length = pre_exp.size();
 
  for (int i = length - 1; i >= 0; i--) {
 
    if (isOperator(pre_exp[i])) {
 
      string op1 = s.top();   s.pop();
      string op2 = s.top();   s.pop();
 
      string temp = "(" + op1 + pre_exp[i] + op2 + ")";
 
      s.push(temp);
    }
 
    else {
      s.push(string(1, pre_exp[i]));
    }
  }
 
  return s.top();
}

bool evaluatePostfix(string exp){
    map<char,bool> dictionary;
    ifstream dict("dictionary.txt");
    string s; 
    while(getline(dict,s)){
        dictionary[s[0]] = (s[2] == '1');
    }

    Stack* stack = createStack(exp.length());
 
    if (!stack) return -1;
 
    for (int i = 0; exp[i]; i++){

        if(exp[i] == ' ') continue;
         
        else if (isalpha(exp[i])) push(stack, dictionary[exp[i]]);
         
        else if (exp[i] == '!'){
            push(stack, !pop(stack));
        } 
        
        else{
            bool val1 = pop(stack);
            bool val2 = pop(stack);
            switch (exp[i]){
                case '>': push(stack, !val2 || val1); break;
                case '|': push(stack, val2 || val1); break;
                case '&': push(stack, val2 && val1); break;
                case '+': push(stack, val2 ^ val1); break;
            }
        }
    }
    return pop(stack);
}

bool evaluatePrefix(string exp){
    map<char,bool> dictionary;
    ifstream dict("dictionary.txt");
    string s; 
    while(getline(dict,s)){
        dictionary[s[0]] = (s[2] == '1');
    }

    Stack* stack = createStack(exp.length());
 
    if (!stack) return -1;
    for (int j = exp.length() - 1; j >= 0; j--) {

        if(exp[j] == ' ') continue;
         
        else if (isalpha(exp[j])) push(stack, dictionary[exp[j]]);
         
        else if (exp[j] == '!'){
            push(stack, !pop(stack));
        } 
        else{

            bool val1 = pop(stack);
            bool val2 = pop(stack);
            switch (exp[j]){
                case '>': push(stack, !val1 || val2); break;
                case '|': push(stack, val1 || val2); break;
                case '&': push(stack, val1 && val2); break;
                case '+': push(stack, val1 ^ val2); break;
            }
        }
    }
 
    return pop(stack);
}


int main(){
    string exp;
    cout << "Input either an prefix or an postfix expression: ";
    getline(cin, exp);

    if (isdigit(exp[0])){
      string temp = postToInfix(exp);
      if(!errorMessage(temp))
      cout << "Postfix evaluation: " << evaluatePostfix(exp);
    }
    
    else {
      if(!errorMessage(preToInfix(exp)))
      cout << "Prefix evaluation: " << evaluatePrefix(exp);
    }
    return 0;
}