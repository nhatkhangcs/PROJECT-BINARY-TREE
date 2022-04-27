
// C++ program to evaluate a prefix expression.
#include <iostream>
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
    map<char,char> dictionary;
    ifstream dict("dictionary.txt");
    string s; 
    int i = 0;
    while(getline(dict,s)){
        dictionary.insert(pair<char,char>(s[0],s[2]));
    }
    map<char, char>::iterator itr;
    cout << "\nThe map dictionary is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = dictionary.begin(); itr != dictionary.end(); ++itr) {
        cout << '\t' << itr->first << '\t' << itr->second<< '\n';
    }
    return 0;
}