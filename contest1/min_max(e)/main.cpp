#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m, l, q, a_index, b_index, left, right, mid;
    cin >> n >> m >> l;
    int **a = new int*[n];
    int **b = new int*[m];
    for(int i=0; i < n; i++){
        a[i] = new int[l];
        for(int j=0; j < l; j++){
            cin >> a[i][j];
        }
    }
    for(int i=0; i < m; i++){
        b[i] = new int[l];
        for(int j=0; j< l; j++){
            cin >> b[i][j];
        }
    }
    cin >> q;
    for(int i=0; i < q; ++i){
        cin >> a_index >> b_index;
        //vector<int> x = a[a_index-1];
        //vector<int> y = b[b_index-1];
        --b_index; --a_index;
        left = 0;
        right = l-1;
        while(right-left>1){
            mid = (left+right)/2;
            if(a[a_index][mid]>b[b_index][mid]){
                right = mid;
            }
            else {
                left = mid;
            }

        }
//        if(right == l){
//            right--;
//        }
//        else if(right != 0 && max(x[right], y[right]) > max(x[right-1], y[right-1])) {
//            right--;
//        }
        if(max(a[a_index][left], b[b_index][left]) < max(a[a_index][right], b[b_index][right])){
            cout << left+1 << '\n';
        }
        else {
            cout << right+1 << '\n';
        }
    }
    delete []a;
    delete []b;
    return 0;
}