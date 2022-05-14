#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip> 

using namespace std;

bool isOperand(char x){
   return isdigit(x);
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

class Stack{
    public:
    int top;
    unsigned capacity;
    double* array;
};

Stack* createStack( unsigned capacity ){
    Stack* stack = new Stack();
 
    if (!stack) return NULL;
 
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = new double[(stack->capacity * sizeof(double))];
 
    if (!stack->array) return NULL;
 
    return stack;
}
 
double isEmpty(Stack* stack){
    return stack->top == -1 ;
}
 
double peek(Stack* stack){
    return stack->array[stack->top];
}
 
double pop(Stack* stack){
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}
 
void push(Stack* stack,double op){
    stack->array[++stack->top] = op;
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

bool balancedParentheses(string expr){
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
        if(precedence(str[i+1])!=1)  
          // 11: ++ -- -> okay, but 21: *+ /- *- /+ 31: ^+ ^- still okay  
          return true;
        else continue;

      }
    }

    // 
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

    else if(nxtOperatorIndex(str,0)==-1) 
      flag = true;

    else if((numberInString(str)-numberInString(removeSpace(str)))!=0)
      flag = true;
    

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

string postToInfix(string exp){
    stack<string> s; 
  
    for (int i=0; i < exp.length(); i++) { 
        if (exp[i] == ' ') continue;
      
        else if (isOperand(exp[i])){
          string temp = "";
          if (isOperator(exp[i-1])) temp += exp[i-1];
          while(exp[i] != ' '){
            temp += exp[i];
            i++;
          }
          i--;
          s.push(temp);
        }
  
        else{ 
            string op1 = s.top(); 
            s.pop();
            if (s.empty()) return ""; 
            string op2 = s.top(); 
            s.pop(); 
            s.push("(" + op2 + exp[i] + op1 + ")" ); 
        } 
    } 

    return s.top();
}

string preToInfix(string pre_exp) {
  stack<string> s;
 
  int length = pre_exp.size();
 
  for (int i = length - 1; i >= 0; i--) {

    if (pre_exp[i] == ' ') continue;

    else if (isOperand(pre_exp[i])){
      int j = i;
      while(pre_exp[j] != ' ') j--;
      j++;
      string temp = "";
      for (int k = j; k <= i; k++){
        temp += pre_exp[k];
      }
      i = j;

      s.push(temp);
    }
 
    else if (isOperator(pre_exp[i])) {
      
      string op1 = s.top();   s.pop();
      if (s.empty()){
        return "";
      }
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

double evaluatePostfix(string exp){
    Stack* stack = createStack(exp.length());
    int i;
 
    if (!stack) return -1;
 
    for (i = 0; exp[i]; i++){

        if(exp[i] == ' ') continue;

        else if(isOperator(exp[i]) && isdigit(exp[i+1])) {
            string t = "";
            int j = i;
            int k;
            while(exp[j] != ' ') j++;
            j--;
            if (exp[j-1] == '-' || exp[j - 1] == '+') t+= exp[j-1];
            for (k =i; k <= j; k++){   
                t += exp[k];
            }

            i = k - 1;
            double result = stod(t);
            push(stack,result);
        }

        else if (isdigit(exp[i])){
          string t = "";
          int j = i;
          while(exp[j] != ' ') {
            t += exp[j];
            j++;
          }

          i = j - 1;
          push(stack, stod(t));
        }

        else{
            if ((exp[i] == '/' && exp[i + 1] == '*') || (exp[i] == '*' && exp[i + 1] == '/') || (exp[i] == '-' && exp[i + 1] == '+') || (exp[i] == '+' && exp[i + 1] == '-')){
                cout << "MULTI-OUTPUT ERROR";
                exit(0);
            }            

            else{
                double val1 = pop(stack);
                double val2 = pop(stack);
                switch (exp[i]){
                    case '+': 
                        push(stack, val2 + val1); break;
                    case '-': 
                        push(stack, val2 - val1); break;
                    case '*': 
                        push(stack, val2 * val1); break;
                    case '/': 
                        if (val1 == 0){
                            cout << "DIVIDED-BY-0 ERROR";
                            exit(0);
                        }
                        push(stack, val2 / val1); break;
                    case '^': 
                        if (val1 == 0 && val2 == 0){
                            cout << "UNDEFINED ERROR";
                            exit(0);
                        }
                        push(stack, pow(val2,val1)); break;
                }
            }
        }
    }
    return pop(stack);
}

double evaluatePrefix(string exp){
    Stack* stack = createStack(exp.length());
    int j;
 
    if (!stack) return -1;

    for (int j = exp.length() - 1; j >= 0; j--){
        if (exp[j] == ' ') continue;
        else if (isdigit(exp[j])){
            string t = "";
            int i = j;
            while(exp[i] != ' ') {
                t+=exp[i];
                i--;
            }

            if (t[0] == '-' || t[0] == '+') reverse(t.begin() + 1, t.end());
            else reverse(t.begin(), t.end());

            double result = stod(t);

            cout << t << '\n';            while(exp[j] != ' ') j--;
            j++;
            push(stack, result);
        }

        else{

            if (exp[j] == ' ' && exp[j - 2] == ' '){
                cout << "UNDEFINED ERROR";
                exit(0);
            }

            else if ((exp[j] == '/' && exp[j - 2] == '*') || (exp[j] == '*' && exp[j - 2] == '/')){
                cout << "UNDEFINED ERROR";
                exit(0);
            }

            double val1 = pop(stack);
            double val2 = pop(stack);
            switch (exp[j]){
                case '+': 
                    push(stack, val1 + val2); break;
                case '-': 
                    push(stack, val1 - val2); break;
                case '*': 
                    push(stack, val1 * val2); break;
                case '/': 
                {
                    if (val2 == 0){
                        cout << "DIVIDE-BY-0 ERROR";
                        exit(0);
                    }
                    push(stack, val1 / val2); break;
                }
                case '^': 
                    push(stack, pow(val1,val2)); break;
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
      cout << temp << '\n';
      if(!errorMessage(postToInfix(exp)))
       cout << "Postfix evaluation: "<<fixed<<setprecision(3) << evaluatePostfix(exp);
    }

    else{
      string temp = preToInfix(exp);
      if(!errorMessage(temp))
      cout << "Prefix evaluation: " << fixed << setprecision(3) << evaluatePrefix(exp);
    }
    return 0;
}