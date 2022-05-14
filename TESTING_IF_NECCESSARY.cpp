#include "validArith.h"
// #include "arithModule.h"
#include <iomanip>
int main(){
    string exp;
    cout << "Input either a prefix or a postfix expression: ";
    getline(cin, exp);
    if (isdigit(exp[0])){
      string temp = postToInfix(exp);
      cout << temp << '\n';
      if(!errorMessage(postToInfix(exp)))
       cout << "Postfix evaluation: "<< fixed << setprecision(3) << evaluatePostfix(exp);
    }

    else{
      string temp = preToInfix(exp);
      cout << temp << '\n';
      if(!errorMessage(temp))
      cout << "Prefix evaluation: " << fixed << setprecision(3) << evaluatePrefix(exp);
    }
    return 0;
}