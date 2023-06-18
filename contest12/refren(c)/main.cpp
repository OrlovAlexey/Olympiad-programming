#include <iostream>
#include <map>

using namespace std;

struct node {
    long long l, r, par, link;
    std::map<long long, long long> edges;
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
    long long v, pos; // polong longs on the letter under number pos on the edge leading to v
    state(long long v, long long pos) : v(v), pos(pos) {}
};

state go(state st, long long l, long long r, long long s[], node t[]) {
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

long long split(state st, long long s[], node t[], long long& tree_size) { // splitting edge
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

long long get_link(long long v, long long s[], node t[], long long& tree_size) {
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

void tree_extend(long long pos, long long s[], long long n, node t[], long long& tree_size, state& ptr) {
    long long mid = 1, leaf;
    while(mid) {
        state nptr = go(ptr, pos, pos + 1, s, t);
        if (nptr.v != -1) { // doesn't create new node and go further or stop
            ptr = nptr;
            return;
        }
        mid = split(ptr, s, t, tree_size);
        leaf = tree_size++;
        t[leaf] = node(pos, n, mid); // creating new node (leaf case)
        t[mid].to(s[pos]) = leaf; // connecting old with new

        ptr.v = get_link(mid, s, t, tree_size); // getting up via suff_link
        ptr.pos = t[ptr.v].len();
    }
}


void dfs_leaves(long long v, long long n, node t[], long long leaves[]) {
    if (t[v].r == n) {
        leaves[v] = 1;
        return;
    }
    long long leaves_sum = 0;
    for (auto p : t[v].edges) {
        long long u = p.second;
        dfs_leaves(u, n, t, leaves);
        leaves_sum += leaves[u];
    }
    leaves[v] = leaves_sum;
}

void dfs_depth(long long v, long long n, node t[], long long depth[]) {
    if (v == 0) {
        depth[v] = 0;
    }
    for (auto p : t[v].edges) {
        long long u = p.second;
        depth[u] = depth[v] + t[u].len() - (t[u].r == n);
        dfs_depth(u, n, t, depth);
    }
}

void dfs_to_find_refren(long long v, long long& refren_vertex, long long& refren, node t[], const long long leaves[], const long long depth[]) {
    if (leaves[v] * depth[v] > refren) {
        refren = leaves[v] * depth[v];
        refren_vertex = v;
    }
    for (auto p : t[v].edges) {
        long long u = p.second;
        dfs_to_find_refren(u, refren_vertex, refren, t, leaves, depth);
    }
}


void dfs_to_find_substring_with_refren(long long v, long long& refren_vertex, long long refren, node t[], const long long leaves[], const long long depth[]) {
    if (leaves[v] * depth[v] == refren) {
        refren_vertex = v;
    }
    for (auto p : t[v].edges) {
        long long u = p.second;
        dfs_to_find_substring_with_refren(u, refren_vertex, refren, t, leaves, depth);

    }
}

int main() {
    long long n, m;
    cin >> n >> m;
    ++n;
    long long s[n];
    for (long long i = 0; i < n - 1; ++i) {
        cin >> s[i];
    }
    s[n - 1] = 0;
    long long max_n_vertexes = 3 * n;
    node tree[max_n_vertexes];
    for (long long i = 0; i < n; ++i) {
        tree[i] = node();
    }
    long long tree_size = 1;
    state ptr(0, 0);
    for (long long i = 0; i < n; ++i) {
        tree_extend(i, s, n, tree, tree_size, ptr);
    }
//    cout << tree_size << '\n';
    long long leaves[max_n_vertexes];
    dfs_leaves(0, n, tree, leaves);
    long long depth[max_n_vertexes];
    dfs_depth(0, n, tree, depth);
//    dfs_prlong longing(0, tree, leaves, depth);

    long long refren = 0;
    long long refren_vertex;
    dfs_to_find_refren(0, refren_vertex, refren, tree, leaves, depth);
//    dfs_to_find_substring_with_refren(0, refren_vertex, refren, tree, leaves, depth);
//    cout << refren_vertex << '\n';

    bool is_ending = (tree[refren_vertex].r == n);
    cout << refren << '\n';
    cout << depth[refren_vertex] << '\n';
    long long temp = refren_vertex;
    long long ans_size = depth[refren_vertex];
    long long answer[ans_size];
    long long t = 0;
    while (temp != 0) {
        for (long long i = 0; i < tree[temp].len(); ++i) {
            long long c = s[tree[temp].r - i - 1];
            if (c == 0)
                continue;
            answer[t++] = c;
        }
        temp = tree[temp].par;
    }
    for (long long i = 0; i < ans_size; ++i) {
        cout << answer[ans_size - i - 1] << " ";
    }
    return 0;
}