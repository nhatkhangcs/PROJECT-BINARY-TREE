#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

bool isOperator(char c)
{
    return (!isalpha(c) && !isdigit(c) && !isspace(c));
    // return (c=='+'||c=='-'||c=='*'||c=='/'||c=='^');
}

int precedence(char C)
{
    if (C == '+' || C == '-')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else if (C == '^')
        return 3;
    return 0;
}

string infixToPostfix(string infix)
{
 
    stack<char> charStack; 
    string result;
 
    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];
 
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
            || (c >= '0' && c <= '9'))
            result += c;
 

        else if (c == '(') charStack.push('(');
        else if (c == ')') {
            while (charStack.top() != '(') {
                result += charStack.top();
                charStack.pop();
            }
            charStack.pop();
        }
 
        else {
            while (!charStack.empty()
                   && precedence(infix[i]) <= precedence(charStack.top())) {
                if (c == '^' && charStack.top() == '^')
                    break;
                else {
                    result += charStack.top();
                    charStack.pop();
                }
            }
            charStack.push(c);
        }
    }
 
    while (!charStack.empty()) {
        result += charStack.top();
        charStack.pop();
    }
 
    return result;
}


string infixToPrefix(string infix)
{
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








