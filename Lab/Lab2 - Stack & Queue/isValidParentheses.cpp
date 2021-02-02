#include <iostream>
#include <stack>
using namespace std;

bool isValidParentheses (string s){
    /*TODO*/
    stack<char> s1;
    for (unsigned i=0; i<s.length(); i++){
        if (s[i] == '(' || s[i] == '{' || s[i] == '['){
            s1.push(s[i]);
            continue;
        }
        if (s1.empty()) return false;
        switch(s[i])
        {
            case ')':
                if (!s1.empty()){
                    if (s1.top() == '('){
                        s1.pop();
                    }
                    else return false;
                }
                break;
            case '}':
                if (!s1.empty()){
                    if (s1.top() == '{'){
                        s1.pop();
                    }
                    else return false;
                }
                break;
            case ']':
                if (!s1.empty()){
                    if (s1.top() == '['){
                        s1.pop();
                    }
                    else return false;
                }
                break;
        }
    }
    return s1.empty();
}

int main(){
	cout << isValidParentheses("[]") << endl;
	cout << isValidParentheses("[]()") << endl;
	cout << isValidParentheses("[)");
}
