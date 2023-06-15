#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;



int main() {
    int delta = 0;
    int ans = 0;
    int n;
    cin >> n;
    int* a = new int[n];
    int* b = new int[n];
    for(int i = 0; i < n; ++i){
        cin >> a[i] >> b[i];
    }
    vector< pair<int, bool> > v(2*n);
    for(int i = 0; i < 2*n; ++i){
        if(i<n){
            v[i].first = a[i];
            v[i].second = false;
        }
        else{
            v[i].first = b[i-n];
            v[i].second = true;
        }
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < 2*n; ++i){
        if(delta == 1){
            ans += v[i].first - v[i-1].first;
        }
        if(v[i].second == false){
            ++delta;
        }
        else{
            --delta;
        }
    }
    cout << ans << endl;
    return 0;
}
