/* C++ implementation to convert
infix expression to postfix*/
 
#include "1b.h"
using namespace std;
 
// Function to return precedence of operators
// Driver program to test above functions
int main()
{
    string s;
    cout << "Please enter a infix-notation representation of an arithmetic expression: ";
    cin >> s;
    cout << "Infix ---> Postfix: "<< infixToPostfix(s);
    return 0;
}