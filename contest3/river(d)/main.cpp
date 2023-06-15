#include <iostream>

using namespace std;

typedef long long ll;

struct Node {
    Node *right, *left;
    ll prior, cnt, value, minStat, sumV, addBelow;
};

typedef Node* vertex;

ll cnt(vertex v){
    if (v != nullptr) {
        return v->cnt;
    }
    else {
        return 0;
    }
}

void Update(vertex& v){
    v->cnt = 1 + v->left->cnt + v->right->cnt;
    v->minStat = min(v->value, min(v->left->minStat, v->left->minStat));
    v->sumV = v->left->sumV + v->right->sumV + v->value;
}

void Actualize(vertex& v) {

}

pair<vertex, vertex> Split(vertex& v, ll k){
    if (v == nullptr) {
//        assert(k == 0);
        return make_pair(nullptr, nullptr);
    }
    Actualize(v);
    if (k <= cnt(v->left)){
        pair<vertex, vertex> p1 = Split(v->left, k);
        v->left = p1.second;
        Update(v);
        return make_pair(p1.first, v);
    }
    else {
        pair<vertex, vertex> p1 = Split(v->right, k - cnt(v->left) - 1);
        v->right = p1.first;
        Update(v);
        return make_pair(v,p1.second);
    }
}

int main() {
    return 0;
}
