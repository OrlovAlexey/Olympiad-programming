#include <iostream>
#include <map>

using namespace std;

struct node {
    int l, r, par, link;
    std::map<char, int> edges;
    explicit node(int l = 0, int r = 0, int par = -1) : l(l), r(r), par(par), link(-1), edges() {}
    int& to(char c) {
        if (!edges.count(c))
            edges[c] = -1;
        return edges[c];
    }
    int len() const {
        return r - l;
    }
};

struct state {
    int v, pos; // points on the letter under number pos on the edge leading to v
    state(int v, int pos) : v(v), pos(pos) {}
};

state go(state st, int l, int r, const string& s, node t[]) {
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

int split(state st, const string& s, node t[], int& tree_size) { // splitting edge
    if (st.pos == t[st.v].len()) {
        return st.v;
    }
    if (st.pos == 0) {
        return t[st.v].par;
    }
    node v = t[st.v];
    int new_u = tree_size++;
    t[new_u] = node(v.l, v.l + st.pos, v.par); // creating new node on the edge
    t[new_u].to(s[v.l + st.pos]) = st.v; // connecting new node and old node
    t[v.par].to(s[v.l]) = new_u; // connecting parent and new node
    t[st.v].l += st.pos; // moving l -> l+pos
    t[st.v].par = new_u; // connecting old node and new node
    return new_u;
}

int get_link(int v, const string& s, node t[], int& tree_size) {
    if (t[v].link != -1) {
        return t[v].link;
    }
    if (t[v].par == -1) {
        return 0;
    }
    int to = get_link(t[v].par, s, t, tree_size);
    t[v].link = split(go(state(to, t[to].len()), t[v].l + (t[v].par == 0), t[v].r, s, t), s, t, tree_size);
    return t[v].link;
}

void tree_extend(int pos, const string& s, node t[], int& tree_size, state& ptr) {
    int mid = 1, leaf;
    while(mid) {
        state nptr = go(ptr, pos, pos + 1, s, t);
        if (nptr.v != -1) { // doesn't create new node and go further or stop
            ptr = nptr;
            return;
        }
        mid = split(ptr, s, t, tree_size);
        leaf = tree_size++;
        t[leaf] = node(pos, (int)s.size(), mid); // creating new node (leaf case)
        t[mid].to(s[pos]) = leaf; // connecting old with new

        ptr.v = get_link(mid, s, t, tree_size); // getting up via suff_link
        ptr.pos = t[ptr.v].len();
    }
}


void dfs_new_naming(int v, node t[], node new_t[], int& new_tree_size, int new_names[]) {
    for (auto p : t[v].edges) {
        int u = p.second;
        int new_name = new_tree_size++;
        new_names[u] = new_name;
        new_t[new_name].r = t[u].r;
        new_t[new_name].l = t[u].l;
        new_t[new_name].par = new_names[v];
        dfs_new_naming(u, t, new_t, new_tree_size, new_names);
        new_t[new_name].link = new_names[t[u].link];
        for (auto edge : t[u].edges)
            new_t[new_name].edges.insert(std::make_pair(edge.first, new_names[edge.second]));
    }
}

void dfs_printing(int v, node t[]) {
    for (auto p : t[v].edges) {
        int u = p.second;
//        cout << u << " " << p.first << " ";
        cout << t[u].par << " " << t[u].l << " " << t[u].r << '\n';
        dfs_printing(u, t);
    }
}

int main() {
    std::string s;
    cin >> s;
    int n = (int)s.size();
    node tree[3*n];
    for (int i = 0; i < 3*n; ++i) {
        tree[i] = node();
    }
    int tree_size = 1;
    state ptr(0, 0);
    for (int i = 0; i < n; ++i) {
        tree_extend(i, s, tree, tree_size, ptr);
    }
    node new_tree[3*n];
    new_tree[0] = tree[0];
    int new_names[3*n];
    new_names[0] = 0;
    int new_tree_size = 1;
    dfs_new_naming(0, tree, new_tree, new_tree_size, new_names);
    new_tree[0].edges = std::map<char, int>();
    for (auto edge : tree[0].edges)
        new_tree[0].edges.insert(std::make_pair(edge.first, new_names[edge.second]));
    cout << tree_size << '\n';
    dfs_printing(0, new_tree);
    return 0;
}
