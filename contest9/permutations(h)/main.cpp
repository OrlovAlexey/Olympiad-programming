#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::unordered_map;
using std::unordered_set;
using str = std::string;

//struct Node {
//    long long v;
//    vector<long long> permutation;
//    Node(long long v, const vector<long long>& permutation) : v(v), permutation(permutation) {}
//
//};

unordered_map<long long, long long> dist1;
unordered_map<long long, long long> dist2;
queue<long long> q1;
queue<long long> q2;
//unordered_set<str> used1;
//unordered_set<str> used2;
//unordered_map<long long, bool> used;


long long n;
long long layer = 50;
long long inf = 100000000;
long long number = 0;
/*
unordered_set<str> get_perms(const str& perm) {
    unordered_set<str> sons;
    str temp_perm;
    for (long long i = 0; i < n; ++i) {
        for (long long j = i + 1; j < n; ++j) {
            temp_perm = perm;
            for (long long k = 0; k < (j - i) / 2 + 1; ++k) {
                std::swap(temp_perm[i + k], temp_perm[j - k]);
            }
            str new_perm = temp_perm;
//            number++;
            sons.insert(new_perm);
        }
    }
    return sons;
}*/

inline long long power_of_10(short z) {
    long long x = 1;
    for (short i = 0; i < z; ++i) {
        x *= 10;
    }
    return x;
}

unordered_set<long long> get_perms(long long perm) {
    unordered_set<long long> sons;
    vector<short> original;
    short sh;
    for (short z = 0; z < n; ++z) {
        sh = (perm % power_of_10(z + 1)) / power_of_10(z);
        original.push_back(sh);
    }
    vector<short> temp_perm;
    for (long long i = 0; i < n; ++i) {
        for (long long j = i + 1; j < n; ++j) {
            temp_perm = original;
            for (long long k = 0; k < (j - i) / 2 + 1; ++k) {
                std::swap(temp_perm[i + k], temp_perm[j - k]);
            }
            long long new_perm = 0;
            for (auto it = temp_perm.rbegin(); it != temp_perm.rend(); ++it) {
//                cout << *it + 1;
                new_perm += *it;
                new_perm *= 10;
            }
//            cout << "\n\n";
            new_perm /= 10;
//            cout << new_perm + 1111 << '\n';
            sons.insert(new_perm);
        }
    }
    return sons;
}

long long double_bfs(long long s, long long t){
//    dist1.assign(layer, inf);
//    dist2.assign(layer, inf);
    dist1[s] = 0;
    dist2[t] = 0;
    q1.push(s);
    q2.push(t);
    while(!q1.empty() && !q2.empty()) {
        long long v;
        long long size1 = q1.size();
        for (long long z = 0; z < size1; ++z) {
            v = q1.front();
            q1.pop();
            for (long long to : get_perms(v)) {
                if (dist1.find(to) != dist1.end()) {
                    continue;
                }
                dist1[to] = dist1[v] + 1;
                q1.push(to);
                if (dist2.find(to) != dist2.end()) {
                    return dist1[to] + dist2[to];
                }
            }
//            used1.insert(v);
        }
        long long size2 = q2.size();
        for (long z = 0; z < size2; ++z) {
            v = q2.front();
            q2.pop();
            for (long long to : get_perms(v)) {
                if (dist2.find(to) != dist2.end()) {
                    continue;
                }
                dist2[to] = dist2[v] + 1;
                q2.push(to);
                if (dist1.find(to) != dist1.end()) {
                    return dist1[to] + dist2[to];
                }
            }
//            used2.insert(v);
        }
//        layer *= 50;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.tie(nullptr);
    cin >> n;
    str first_permutation;
    long long c;
    for (long long i = 0; i < n; ++i) {
        cin >> c; --c;
        first_permutation += std::to_string(c);
    }
    long long start = std::stoll(first_permutation);
    str second_permutation;
    for (long long i = 0; i < n; ++i) {
        cin >> c; --c;
        second_permutation += std::to_string(c);
    }
    long long finish = std::stoll(second_permutation);
    if (start == finish) {
        cout << 0 << '\n';
        return 0;
    }
//    cout << start << '\n';
//    cout << finish << '\n';
//    dist1.assign(100000, inf);
//    dist2.assign(100000, inf);
    cout << double_bfs(start, finish);
    return 0;
}
