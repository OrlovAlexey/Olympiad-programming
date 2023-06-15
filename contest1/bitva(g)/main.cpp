#include <iostream>

using std::cin;
using std::cout;

typedef long long ll;

int main() {
    ll n, p, q;
    cin >> n >> p >> q;
    ll *a = new long long[n];
    ll max_ai = 0;
    for(ll i = 0; i < n; ++i){
        cin >> a[i];
        max_ai = (a[i] > max_ai ? a[i] : max_ai);
    }
    ll l = 1;
    ll r = max_ai/q + 1;
    ll m = (l+r)/2;
    bool m_hvatit;
    while(l<r){
        m = (l+r)/2;
        ll razn = m;
        ll v;
        m_hvatit = true;
        if(p == q){
            if(m * q < max_ai)
                m_hvatit = false;
        }
        else {
            for (ll i = 0; i < n; ++i) {
                v = a[i] - m * q;
                if (v > 0) {
                    razn -= v / (p - q) + (v % (p - q) != 0);
                }
                if (razn < 0) {
                    m_hvatit = false;
                    break;
                }
            }
        }
        if(m_hvatit){
            r = m;
        }
        else{
            l = m + 1;
        }
    }
    cout << r;
    return 0;
}
