#include <iostream>

using std::cin;
using std::cout;

typedef long long ll;
struct Node {
    Node* left, *right;
    ll value, index;
    ll count = 0;
};

ll cnt = 1;

void upd(ll pos, Node* v, ll tl, ll tr){
    if(tl > tr || !v) {
        return;
    }
    if(tl == tr) {
        v->value = pos;
        v->count++;
        return;
    }
    ll mid = (tl + tr) / 2;
    if(pos <= mid) {
        if(!v->left) {
            Node* n = new Node;
            n = v->left;
//            n->index = ++cnt;
        }
        upd(pos, v->left, tl, mid);
    }
    else {
        if(!v->right) {
            Node* n = new Node;
            n = v->right;
//            n->index = ++cnt;
        }
        upd(pos, v->right, mid+1, tr);
    }
    v->count = v->left->count + v->right->count;
}


ll get_count(ll l, ll r, Node* v, ll tl, ll tr){
    if(!v || l > r) { //|| tl > tr || tl > r || tr < l) {
        return 0;
    }
    if(l == tl && tr == r) {
        return v->count;
    }
    ll tm = (tl + tr) / 2;
    if (r <= tm) {
        get_count(l, r, v->left, tl, tm);
    }
    else {
        get_count(l, r, v->right, tm + 1, tr);
    }
}

int main() {
    Node* root = new Node;
    ll n = 1000000000;
    ll q;
    cin >> q;
    char c;
    ll x;
    for (ll i = 0; i < q; ++i) {
        cin >> c >> x;
        if (c == '+') {
            upd(x-1, root, 0, n-1);
        }
        if (c == '?') {
            cout << get_count(0, x-1, root, 0, n-1) << '\n';
        }
    }
    return 0;
}
