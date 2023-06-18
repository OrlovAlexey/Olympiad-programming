#include <iostream>

using namespace std;

int ALPHABET_SIZE = 256;

int first_iteration(int n, int cnt[], const string& s, int c[], int p[]) {
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        cnt[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        ++cnt[s[i]];
    }
    for (int i = 1; i < ALPHABET_SIZE; ++i) {
        cnt[i] += cnt[i-1];
    }
    for (int i = n - 1; i >= 0; --i) {
        p[--cnt[s[i]]] = i;
    }
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; ++i) {
        if (s[p[i]] != s[p[i-1]]) {
            classes++;
        }
        c[p[i]] = classes - 1;
    }
    return classes;
}

void next_iteration(int k, int n, int& classes, int c[], int p[]) {
    int new_p[n], new_c[n];
    for (int i = 0; i < n; ++i) {
        new_p[i] = (p[i] + n - (1 << k)) % n;
    }
    int cnt[ALPHABET_SIZE];
    for (int i = 0; i < classes; ++i) {
        cnt[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        ++cnt[c[new_p[i]]];
    }
    for (int i = 1; i < classes; ++i) {
        cnt[i] += cnt[i-1];
    }
    for (int i = n - 1; i >= 0; --i) {
        p[--cnt[c[new_p[i]]]] = new_p[i];
    }
    new_c[p[0]] = 0;
    classes = 1;
    for (int i = 1; i < n; ++i) {
        if (c[p[i]] != c[p[i-1]] || c[(p[i] + (1 << k)) % n] != c[(p[i-1] + (1 << k)) % n]) {
            ++classes;
        }
        new_c[p[i]] = classes - 1;
    }
    for (int i = 0; i < n; ++i) {
        c[i] = new_c[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int K;
    cin >> K;
    string s;
    string temp;
    for (int i = 0; i < K; ++i) {
        cin >> temp;
        s += temp;
        s += std::to_string(i);
    }
    int n = (int)s.size();

    // suffix array
    int cnt[ALPHABET_SIZE];
    int c[n];
    int p[n];
    int classes = first_iteration(n, cnt, s, c, p);

    for (int k = 0; (1 << k) < n; ++k) {
        next_iteration(k, n, classes, c, p);
    }

    // lcp
    int N = n - 1;
    int lcp[N];
    for (int i = 0; i < N; ++i) {
        lcp[i] = 0;
//        cout << s.substr(p[i]) << " ";
        for (int j = 0; s[p[i] + j] == s[p[i + 1] + j]; ++j) {
            ++lcp[i];
        }
//        cout << lcp[i] <<  '\n';
    }

    // sparse table
    int log[N + 1];
    log[1] = 0;
    for (int i = 2; i <= N; i++) {
        log[i] = log[i/2] + 1;
    }
    int M = log[N];

    int sparse[N][M + 1];
    for (int i = 0; i < N; i++) {
        sparse[i][0] = lcp[i];
    }

    for (int j = 1; j <= M; j++) {
        for (int i = 0; i + (1 << j) <= N; i++) {
            sparse[i][j] = min(sparse[i][j-1], sparse[i + (1 << (j - 1))][j - 1]);
        }
    }

    // precount
    int first_divider[n];
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (!isalpha(s[j])) {
                first_divider[i] = s[j] - 48;
                break;
            }
        }
    }

//    int j1 = log[10 - 4 + 1];
//    cout << max(sparse[4][j1], sparse[10 - (1 << j1) + 1][j1]) << '\n';

//    for (int i = 0; i < n - 1; ++i ) {
//                cout << i << " " << s.substr(p[i]) << " ";
//                cout << lcp[i] << '\n';
//    }



    // algo
    int entries[K];
    for (int i = 0; i< K; ++i)
        entries[i] = 0;
    int answer = 0;
    int all_entries = 0;
    int ans_suffix;
    for (int l = 0, r = -1; l < n; ++l) {
        while (all_entries < K || l >= r) {
            ++r;
            if (r >= n) {
                goto end_cycle;
            }
            if (++entries[first_divider[p[r]]] == 1) {
                all_entries++;
            }
        }
        int j = log[r - l];
//        answer = max(min(sparse[l][j], sparse[r - (1 << j)][j] + 1), answer);
        if (min(sparse[l][j], sparse[r - (1 << j)][j]) > answer) {
            answer = min(sparse[l][j], sparse[r - (1 << j)][j]);
            ans_suffix = l;
        }
        if (--entries[first_divider[p[l]]] == 0) {
            all_entries--;
        }
    }

    end_cycle:
//    cout << answer << '\n';
    cout << s.substr(p[ans_suffix], answer) << '\n';
    return 0;
}
