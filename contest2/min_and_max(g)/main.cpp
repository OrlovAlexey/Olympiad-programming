#include <iostream>

using namespace std;

long long min_max[100000]; //  индексы мин кучи  в индексы макс кучи
long long max_min[100000]; // лежат индексы макс кучи

class heap_max;

class heap_min{
public:
    long long n = 0;
    long long* a = new long long[100000];
    long long index_max = max_min[0];
    heap_max* ptr;

    void siftUp(long long i){
        while(i > 0 && a[i] < a[(i-1)/2]){
            std::swap(a[i], a[(i-1)/2]);
            std::swap(max_min[min_max[i]], max_min[min_max[(i-1)/2]]);
            std::swap(min_max[i], min_max[(i-1)/2]);
            i = (i-1) / 2;
        }
    }

    void siftDown(long long i){
        while(2*i+1 <= n-1) {
            long long j = -1;
            if(a[2*i+1] < a[i]){ j = 2*i + 1; }
            if(2*i+2 <= n-1 && a[2*i+2] < a[i] && (j==-1 || a[2*i+1] > a[2*i+2])){ j = 2*i + 2; }
            if(j==-1) break;
            else{
                std::swap(a[i], a[j]);
                std::swap(min_max[i], min_max[j]);
                std::swap(max_min[min_max[i]], max_min[min_max[j]]);
                i = j;
            }
        }
    }

    void insert(long long x){
        a[++n-1] = x;
        siftUp(n-1);
    }

    long long getMin(){
        return a[0];
    }

    void extractMin();

    ~heap_min(){
        delete[] a;
    }
};

class heap_max{
public:
    long long n = 0;
    long long* a = new long long[100000];
    long long index_min = 0;
    heap_min* ptr;

    void siftUp(long long i){
        while(i > 0 && a[i] > a[(i-1)/2]){
            std::swap(a[i], a[(i-1)/2]);
            i = (i-1) / 2;
        }
    }

    void siftDown(long long i){
        while(2*i+1 <= n-1) {
            long long j = -1;
            if(a[2*i+1] > a[i]){ j = 2*i + 1; }
            if(2*i+2 <= n-1 && a[2*i+2] > a[i] && (j==-1 || a[2*i+1] < a[2*i+2])){ j = 2*i + 2; }
            if(j==-1) break;
            else{
                std::swap(a[i], a[j]);
                std::swap(max_min[i], max_min[j]);
                std::swap(min_max[max_min[i]], min_max[max_min[j]]);
                i = j;
            }
        }
    }

    void insert(long long x){
        a[++n-1] = x;
        siftUp(n-1);
    }

    long long getMax(){
        return a[0];
    }

    void extractMax(){
        a[0] = a[n-1];
        max_min[0] = max_min[n-1];
        min_max[max_min[0]] = min_max[max_min[n-1]];
        --n;
        siftDown(0);
    }

    ~heap_max(){
        delete[] a;
    }
};

void heap_min::extractMin(){
    a[0] = a[n-1];
    ptr->a[max_min[0]] = ptr->a[n-1];
    long long index = max_min[0];
    min_max[0] = min_max[n-1];
    max_min[min_max[0]] = max_min[min_max[n-1]];

    --n;
    siftDown(0);
}

int main() {
    heap_min a_min;
    heap_max a_max;
    long long n;
    char c;
    cin >> n;
    for(long long i = 0; i < n; ++i){
        string s;
        cin >> s;
        long long x = 0;
        if(s[0] == 'I'){
            long long j = 7;
            while(s[j] != ')'){
                x = 10 * x + (s[j] - 48);
                ++j;
            }
            a_max.insert(x);
            a_min.insert(x);
        }
        else if(s[5] == 'x'){
            cout << a_max.getMax() << '\n';
            a_max.extractMax();
        }
        else if(s[5] == 'n'){
            cout << a_min.getMin() << '\n';
            a_min.extractMin();
        }
    }
    return 0;
}
