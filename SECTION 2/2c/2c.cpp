// C++ program to evaluate value of a postfix
// expression having multiple digit operands
#include <iostream>
#include <stack>
#include <string.h>
#include <map>
#include <cmath>
#include <utility>
#include <algorithm>
#include "2c.h"
#include <fstream>

using namespace std;

//POSTFIX EVALUATION
bool evaluatePostfix(string exp)
{
    map<char,bool> dictionary;
    ifstream dict("dictionary.txt");
    string s; 
    while(getline(dict,s)){
        dictionary[s[0]] = (s[2] == '1');
    }

    Stack* stack = createStack(exp.length());
 
    if (!stack) return -1;
 
    for (int i = 0; exp[i]; i++)
    {

        if(exp[i] == ' ') continue;
         
        else if (isalpha(exp[i])) push(stack, dictionary[exp[i]]);
         
        else if (exp[i] == '!')
        {
            push(stack, !pop(stack));
        } 
        
        else
        {
            bool val1 = pop(stack);
            bool val2 = pop(stack);
            switch (exp[i])
            {
                case '>': push(stack, !val2 || val1); break;
                case '|': push(stack, val2 || val1); break;
                case '&': push(stack, val2 && val1); break;
                case '+': push(stack, val2 ^ val1); break;
            }
        }
    }
    return pop(stack);
}

//PREFIX EVALUATION
bool evaluatePrefix(string exp)
{
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
         
        else if (exp[j] == '!')
        {
            push(stack, !pop(stack));
        } 
        else
        {

            bool val1 = pop(stack);
            bool val2 = pop(stack);
            switch (exp[j])
            {
                case '>': push(stack, !val1 || val2); break;
                case '|': push(stack, val1 || val2); break;
                case '&': push(stack, val1 && val2); break;
                case '+': push(stack, val1 ^ val2); break;
            }
        }
    }
 
    return pop(stack);
}


int main()
{
    string exp;
    cout << "Input either an infix or an postfix expression: ";
    getline(cin, exp);
    if (isalpha(exp[0])) cout << "Postfix evaluation: " << evaluatePostfix(exp);
    else cout << "Prefix evaluation: " << evaluatePrefix(exp);
    return 0;
}