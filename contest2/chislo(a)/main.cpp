#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using std::string;

bool cmp(string& a, string& b) {
    if (a + b > b + a) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    std::vector<string> v;
    std::fstream input;
    std::fstream output;
    input.open("number.in", std::fstream::in);
    output.open("number.out", std::fstream::out);
    for(string line; getline(input, line); ){
        v.push_back(line);
    }
    std::sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < v.size(); ++i) {
        output << v[i];
    }
    return 0;
}
