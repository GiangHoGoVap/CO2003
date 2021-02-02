#include <iostream>
#include <string>
using namespace std;

/* Your helping functions go here */
string InsertionSort(string a){
	for (unsigned i=0; i<a.length(); i++){
		for (unsigned j=i; j>0 && a[j] < a[j-1]; j--){
			char temp = a[j];
			a[j] = a[j-1];
			a[j-1] = temp;
		}
	}
	return a;
}

bool isPermutation(string a, string b){
	if (a.length() != b.length()) return false;
	string newA = InsertionSort(a);
	string newB = InsertionSort(b);
	for (unsigned i = 0; i<newA.length(); i++){
		if (newA[i] != newB[i]) return false;
	}
	return true;
}

int main(){
	string a = "abba";
	string b ="baba";
	cout << isPermutation(a, b) << endl;
	string aa = "abbac";
	string bb ="baba";
	cout << isPermutation(aa, bb);
}
