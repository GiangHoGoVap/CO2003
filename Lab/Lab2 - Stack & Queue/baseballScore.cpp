#include <iostream>
#include <stack>
using namespace std;

int baseballScore(string ops){
    /*TODO*/
    stack<int> s;
    int ans = 0;
    for (auto i:ops){
        if (i == 'C') s.pop();
        else if (i == 'D'){
            int temp = s.top();
            temp = temp*2;
            s.push(temp);
        } 
        else if (i == '+'){
            int temp1 = s.top();
            s.pop();
            int temp2 = s.top();
            int res = temp1 + temp2;
            s.push(temp1);
            s.push(res);
        }
        else{
        	string str;
        	str.push_back(i);
            int temp = stoi(str);
            s.push(temp);
        }
    }
    while (!s.empty()){
        ans += s.top();
        s.pop();
    }
    return ans;
}

int main(){
	cout << baseballScore("52CD+");
	cout << endl;
	cout << baseballScore("524CD9++");
	return 0;
}
