#include <iostream>
#include <stack>
using namespace std;

string removeDuplicates(string S){
    /*TODO*/
	stack<char> s;
	for (unsigned i=0; i<S.length(); ++i){
		if (s.empty() || s.top() != S[i]) s.push(S[i]);
		else s.pop();
	}
	string res = "";
	while (!s.empty()){
		res = s.top() + res;
		s.pop();
	}
	return res;
}

int main(){
	cout << removeDuplicates("abbaca");
	cout << endl;
	cout << removeDuplicates("aab");
}
