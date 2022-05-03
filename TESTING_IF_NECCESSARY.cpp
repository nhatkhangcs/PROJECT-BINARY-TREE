
// C++ program to evaluate a prefix expression.
#include <iostream>
// #include "./SECTION 1/1a/1a.h"
// #include "./SECTION 1/1a/1a.h"
#include "./SECTION 1/validArithmetic.h"
#include "./SECTION 2/validLogical.h"
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <utility>
#include <stack>
#include <map>
using namespace std;

int main()
{
    // map<char,char> dictionary;
    // ifstream dict("dictionary.txt");
    // string s; 
    // int i = 0;
    // while(getline(dict,s)){
    //     dictionary.insert(pair<char,char>(s[0],s[2]));
    // }
    // map<char, char>::iterator itr;
    // cout << "\nThe map dictionary is : \n";
    // cout << "\tKEY\tELEMENT\n";
    // for (itr = dictionary.begin(); itr != dictionary.end(); ++itr) {
    //     cout << '\t' << itr->first << '\t' << itr->second<< '\n';
    // }
    
    string testStr;// ="(P+(Q*R)/(S-T))";

    // string testStr="3 + 5 ^ 8";
    // string testStr="3 + 5 ^ 8";
    
    getline(cin, testStr);

    // cout << isOperator('/');
    // cout << nxtOperatorIndex(testStr, 2);
    
    //cout<<arithmeticValidity(testStr);
    cout<<logicalValidity(testStr);
    
    // cout<<isdigit('1');
    // if(validity(testStr)!=0) errorMessage(testStr);
    // infixToPrefix(testStr);
    // cout<<infixToPrefix(testStr);
    // cout<<infixToPostfix(testStr);
    return 0;
}