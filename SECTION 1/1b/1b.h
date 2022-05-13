#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int prec(char C){
    if (C == '+' || C == '-')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else if (C == '^')
        return 3;
    return 0;
}

string infixToPostfix(string s)
{
 
    stack<char> st; 
    string result;
 
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') continue;
        char c = s[i];
 
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
            || (c >= '0' && c <= '9'))
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
                   && prec(s[i]) <= prec(st.top())) {
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