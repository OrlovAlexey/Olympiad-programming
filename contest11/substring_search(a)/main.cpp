#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> pi_function(const string& s) {
	int n = s.length();
	vector<int> pi(n);
	for (int i = 1; i < n; ++i) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j]) {
			j = pi[j-1];
		}
		if (s[i] == s[j]) {
			++j;
		}
		pi[i] = j;
	}
	return pi;
}

int main(){
	string s, t;
	cin >> s >> t;
	string new_s = t;
	new_s += '#';
	new_s += s;
	vector<int> pi = pi_function(new_s);
	for (int i = 0; i <= s.length(); ++i) {
		if (t.length() == pi[t.length() + i]) {
			cout << (i - t.length())<< " ";
		}
	}
	return 0;
}
