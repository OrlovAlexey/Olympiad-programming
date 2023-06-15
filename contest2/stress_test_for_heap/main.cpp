#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    srand(static_cast<unsigned int>(time(0)));
    int a[10000] = { 0 };
    int k = 0;
    freopen("stest.txt", "w", stdout);
    for(long long i = 1; i < 10000; ++i) {
        int x = rand() % 4;
        int y, ptr, delta;
        switch (x) {
            case 0: y = rand() % 10000;
                cout << "insert " << y << '\n';
                a[i] = 1;
                break;
            case 1: // decreaseKey
                ptr;
                do {
                    ptr = rand() % i + 1;
                }while(a[ptr] != 1);
                delta = rand() % 10000;
                cout << "decreaseKey " << ptr << " " << delta << '\n';
                break;
            case 2: // extractMin
                cout << "extractMin" << '\n';
            case 3: // getMin
                cout << "getMin" << '\n';
        }
    }
    return 0;
}
