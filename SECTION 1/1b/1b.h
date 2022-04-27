#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

bool isOperator(char c)
{
    return (!isalpha(c) && !isdigit(c));
}

int getPriority(char C)
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
    infix = '(' + infix + ')';
    int l = infix.size();
    stack<char> char_stack;
    string output;
 
    for (int i = 0; i < l; i++) {

        
        if (isalpha(infix[i]) || isdigit(infix[i]))
            output += infix[i];

        else if (infix[i] == '(')
            char_stack.push('(');

        else if (infix[i] == ')') {
            while (char_stack.top() != '(') {
                output += char_stack.top();
                char_stack.pop();
            }

            char_stack.pop();
        }

        else if (infix[i] == ' ') continue;

        else{
            if (isOperator(char_stack.top())){
                if(infix[i] == '^')
                {
                    while (getPriority(infix[i]) <= getPriority(char_stack.top()))
                    {
                        output += char_stack.top();
                        char_stack.pop();
                    }
                }
                else
                {
                    while (getPriority(infix[i]) < getPriority(char_stack.top()))
                    {
                        output += char_stack.top();
                        char_stack.pop();
                    }  
                }
 
                char_stack.push(infix[i]);
            }
        }
    }

    while(!char_stack.empty()){
        output += char_stack.top();
        char_stack.pop();
    }

    return output;
}