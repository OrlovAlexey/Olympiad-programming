#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Partition(vector<long long>& a, long long p) {
    long long n = a.size();
    long long i = 0, j = n - 1;
    while(true){
        while (i <= n-1 && a[i] < p) ++i;
        while (j >= 0 && a[j] > p) --j;
        if(i > j) break;
        std::swap(a[i], a[j]);
    }
}

long long kth(vector<long long>& A, long long k){
    if(A.size() == 1){
        return A[0];
    }
    else{
        long long x = A.size() / 2;
        vector<long long> B;
        vector<long long> C;
        Partition(A, x);
        long long i = 0;
        for(; i < A.size(); ++i){
            B.push_back(A[i]);
            if(A[i] == x){ break;}
        }
        for(; i < A.size(); ++i){
            C.push_back(A[i]);
        }

        if(k <= B.size()) return kth(B, k);
        else return kth(C, k - B.size());
    }

}

int main() {
    srand(time(nullptr));
    long long n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for(long long i = 0; i < n; ++i){
        cin >> a[i];
    }
    cout << kth(a, k) << endl;
    return 0;
}
