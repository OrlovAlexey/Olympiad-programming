#include <iostream>
#include <map>

using namespace std;

struct node {
    long long l, r, par, link;
    std::map<char, long long> edges;
    explicit node(long long l = 0, long long r = 0, long long par = -1) : l(l), r(r), par(par), link(-1), edges() {}
    long long& to(char c) {
        if (!edges.count(c))
            edges[c] = -1;
        return edges[c];
    }
    long long len() const {
        return r - l;
    }
};

struct state {
    long long v, pos; // points on the letter under number pos on the edge leading to v
    state(long long v, long long pos) : v(v), pos(pos) {}
};

state go(state st, long long l, long long r, const string& s, node t[]) {
    while (l < r) {
        if (st.pos == t[st.v].len()) {
            st = state(t[st.v].to(s[l]), 0);
            if (st.v == -1)
                return st;
        } else {
            if (s[t[st.v].l + st.pos] != s[l]) // if the symbol on edge not equals the wanted symbol
                return state(-1, -1);
            if (r - l < t[st.v].len() - st.pos) // if there is enough more space on the edge to place s[r:l]
                return state(st.v, st.pos + r - l);
            l += t[st.v].len() - st.pos;
            st.pos = t[st.v].len();
        }
    }
    return st;
}

long long split(state st, const string& s, node t[], long long& tree_size) { // splitting edge
    if (st.pos == t[st.v].len()) {
        return st.v;
    }
    if (st.pos == 0) {
        return t[st.v].par;
    }
    node v = t[st.v];
    long long new_u = tree_size++;
    t[new_u] = node(v.l, v.l + st.pos, v.par); // creating new node on the edge
    t[new_u].to(s[v.l + st.pos]) = st.v; // connecting new node and old node
    t[v.par].to(s[v.l]) = new_u; // connecting parent and new node
    t[st.v].l += st.pos; // moving l -> l+pos
    t[st.v].par = new_u; // connecting old node and new node
    return new_u;
}

long long get_link(long long v, const string& s, node t[], long long& tree_size) {
    if (t[v].link != -1) {
        return t[v].link;
    }
    if (t[v].par == -1) {
        return 0;
    }
    long long to = get_link(t[v].par, s, t, tree_size);
    t[v].link = split(go(state(to, t[to].len()), t[v].l + (t[v].par == 0), t[v].r, s, t), s, t, tree_size);
    return t[v].link;
}

void tree_extend(long long pos, const string& s, node t[], long long& tree_size, state& ptr) {
    long long mid = 1, leaf;
    while(mid) {
        state nptr = go(ptr, pos, pos + 1, s, t);
        if (nptr.v != -1) { // doesn't create new node and go further or stop
            ptr = nptr;
            return;
        }
        mid = split(ptr, s, t, tree_size);
        leaf = tree_size++;
        t[leaf] = node(pos, (long long)s.size(), mid); // creating new node (leaf case)
        t[mid].to(s[pos]) = leaf; // connecting old with new

        ptr.v = get_link(mid, s, t, tree_size); // getting up via suff_link
        ptr.pos = t[ptr.v].len();
    }
}

void dfs_printing(long long v, node t[]) {
    for (auto p : t[v].edges) {
        long long u = p.second;
//        cout << u << " " << p.first << " ";
        cout << t[u].par << " " << t[u].l << " " << t[u].r << '\n';
        dfs_printing(u, t);
    }
}

bool dfs_checking_word(const string& q, const string& s, node t[]) {
    state ptr(0, 0);
    for (char c : q) {
        if (t[ptr.v].len() == ptr.pos) {
            for (auto edge : t[ptr.v].edges) {
                if (c != edge.first) {
                    continue;
                }
                ptr.v = edge.second;
                ptr.pos = 1;
                goto good;
            }
            return false;
            good:
            continue;
        } else {
            if (c == s[t[ptr.v].l + ptr.pos]) {
                ++ptr.pos;
                // ok
            }
            else {
                return false;
            }
        }
    }
    return true;
}

void low(string& temp) {
    for (auto& c : temp) {
        if (c < 97) {
            c += 32;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::string s;
    string command;
    string temp;
    const long long N = 100000;
    node* tree = new node[2 * N];
    for (long long i = 0; i < 2 * N; ++i) {
        tree[i] = node();
    }
    long long n = 0;
    long long tree_size = 1;
    state ptr(0, 0);
    while (cin >> command) {
        cin >> temp;
        low(temp);
        if (command == "?") {
            if (dfs_checking_word(temp, s, tree)) {
                cout << "YES" << endl;
            }
            else {
                cout << "NO" << endl;
            }
        }
        if (command == "A") {
            for (long long i = 0; i < n + temp.size(); ++i) {
                tree_extend(i, s + temp, tree, tree_size, ptr);
            }
            s += temp;
            n += (long long)temp.size();
        }
    }
    delete[] tree;
    return 0;
}
