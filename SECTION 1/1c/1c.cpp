#include <iostream>
#include <stack>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iomanip> 
#include "1c.h"

using namespace std;

double evaluatePostfix(string exp){
    Stack* stack = createStack(exp.length());
    int i;
 
    if (!stack) return -1;
 
    for (i = 0; exp[i]; i++){
        if(exp[i] == ' ') continue;

        else if (isdigit(exp[i])) {
            string t = "";
            int j = i;
            while(exp[j] != ' ') j++;
            j--;
            for (i; i <= j; i++){   
                t += exp[i];
            }

            double result = stod(t);
            while(exp[i] != ' ') i++;
            i--;
            push(stack,result);
        }

        else{
            if (!isdigit(exp[i]) && !isdigit(exp[i + 1]) && i + 1 < exp.length()) {
                cout << "UNDEFINED ERROR";
                exit(0);
            }

            else if ((exp[i] == '/' && exp[i + 1] == '*') || (exp[i] == '*' && exp[i + 1] == '/') || (exp[i] == '-' && exp[i + 1] == '+') || (exp[i] == '+' && exp[i + 1] == '-')){
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
            while(exp[i] != ' ') i--;
            i++;
            for (i; i <= j; i++){
                t += exp[i];
            }

            double result = stod(t);
            while(exp[j] != ' ') j--;
            j++;
            push(stack, result);
        }

        else{
            if (!isdigit(exp[j]) && !isdigit(exp[j - 1]) && j - 1 >= 0) {
                cout << "UNDEFINED ERROR";
                exit(0);
            }

            else if (exp[j] == ' ' && exp[j - 2] == ' '){
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
    cout << "Input either an infix or an postfix expression: ";
    getline(cin, exp);
    if (isdigit(exp[0])) cout << "Postfix evaluation: " << fixed << setprecision(3) << evaluatePostfix(exp);
    else cout << "Prefix evaluation: " << fixed << setprecision(3) << evaluatePrefix(exp);
    return 0;
}