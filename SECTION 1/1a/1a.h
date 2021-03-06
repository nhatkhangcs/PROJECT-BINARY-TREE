#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

bool isOperator(char c){
    return(!isalpha(c) && !isdigit(c) && c!=')' && c!='(');
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


