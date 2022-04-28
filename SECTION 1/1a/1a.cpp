#include <iostream>
#include "1a.h"
using namespace std;

int main(){
    string s;
    cout << "Please enter a infix-notation representation of an arithmetic expression: ";
    getline(cin,s);
    cout << "Infix ---> Prefix: " << infixToPrefix(s);
    return 0;
}