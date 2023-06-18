#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::map;
using std::set;
/*
struct node{
    std::map<char, int> to;
    bool terminal;
};

void add(const std::string& s, std::vector<node>& trie) {
    int v = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (!trie[v].to.count(s[i])) {
            trie.emplace_back();
            trie[v].to[s[i]] = (int)trie.size() - 1;
        }
        v = trie[v].to[s[i]];
    }
    trie[v].terminal = true;
}

void dfs(int v, bool* used, const string& current_string, const std::vector<node>& trie, vector<string>& answer_array) {
    used[v] = true;
    const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
    if (trie[v].terminal) {
        answer_array.push_back(current_string);
    }
    for (int i = 0; i < ALPHABET.size(); ++i) {
        if (trie[v].to.count(ALPHABET[i])) {
            int u = trie[v].to.at(ALPHABET[i]);
            if (!used[u]) {
                dfs(u, used, current_string + ALPHABET[i], trie, answer_array);
            }
        }
    }
}
 */
int N = 0;

string big_str(const string& s) {
    ++N;
    return (N > 100000 ? "" : (s + big_str(s)));
}
/*
int main() {
//    node root;
//    vector<node> trie(1);
//    trie[0] = root;
    set<string> set1;
    string s;
    cin >> s;
//    s = big_str(".c..bb.a..");
    string temp;
    int j;
    string without_words;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] != '.') {
            temp = "";
            for (j = i; j < s.size() && s[j] != '.'; ++j) {
                temp += s[j];
            }
            i = j - 1;
//            add(temp, trie);
            set1.insert(temp);
            without_words += '#';
        }
        else {
            without_words += '.';
        }
    }
//    cout << without_words << '\n';

//    int n = trie.size();
    int n = set1.size();

/*
    bool used[n];
    for (int i = 0 ; i < n; ++i)
        used[i] = false;

    string curr = "";
    vector<string> ans;
    for (int i = 0 ; i < n; ++i) {
        if (!used[i])
            dfs(i, used, curr, trie, ans);
    }
    auto it = ans.begin();


    auto it = set1.begin();
    string result = "";
    for (int i = 0; i < without_words.size(); ++i) {
        if (without_words[i] == '#') {
            result += *it;
            ++it;
        }
        else {
            result += '.';
        }
    }
    cout << result;
    return 0;
}
*/

int main() {
    string s;
    cin >> s;
    string rem;
    vector<string> to_sort;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] != '.') {
            string temp;
            int j;
            for (j = i; j < s.size() && s[j] != '.'; ++j) {
                temp.push_back(s[j]);
            }
            to_sort.push_back(temp);
            rem.push_back('$');
            i = j - 1;
        }
        else {
            rem.push_back('.');
        }
    }
//    cout << rem << '\n';
    std::sort(to_sort.begin(), to_sort.end());
    auto it = to_sort.begin();
    for (int i = 0; i < rem.size(); ++i) {
        if (rem[i] != '.') {
            cout << *it;
            ++it;
        }
        else{
            cout << rem[i];
        }
    }
    return 0;
}
