#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

/// Helper ///
bool isOperator(char c){
    return(!isalpha(c) && !isdigit(c) && c!=')' && c!='(');
}

bool isOperand(char x){
   return isdigit(x);
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
///In -> Pre///
///In -> Post///
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
///Eval(pre || post)///
string postToInfix(string post){
    stack<string> s; 
  
    for (int i=0; i < post.length(); i++) { 
        if (post[i] == ' ') continue;
      
        else if (isOperand(post[i])) { 
           string op(1, post[i]); 
           s.push(op); 
        } 

        else if ((post[i] == '-' || post[i] == '+') && i <= post.length() - 2){
          string temp = "";
          while(post[i] != ' '){
            temp += post[i];
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
            s.push("(" + op2 + post[i] + op1 + ")" ); 
        } 
    } 

    return s.top();
}

string preToInfix(string pre) {
  stack<string> s;
 
  int length = pre.size();
 
  for (int i = length - 1; i >= 0; i--) {
 
    if (isOperator(pre[i])) {
 
      string op1 = s.top();   s.pop();
      string op2 = s.top();   s.pop();
 
      string temp = "(" + op1 + pre[i] + op2 + ")";
 
      s.push(temp);
    }
 
    else {
      s.push(string(1, pre[i]));
    }
  }
 
  return s.top();
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

double evaluatePostfix(string exp){
    Stack* stack = createStack(exp.length());
    int i;
 
    if (!stack) return -1;
 
    for (i = 0; exp[i]; i++){
        

        if(exp[i] == ' ') continue;

        else if(isOperator(exp[i]) && isdigit(exp[i+1])) continue;

        else if (isdigit(exp[i])) {
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
            while(exp[j] != ' ') j--;
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
