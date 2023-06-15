#include <iostream>
#include "vector"
#include "algorithm"
using namespace std;

typedef long long ll;

struct Node {
    ll element;
    Node* left;
    Node* right;
//    Node* parent;
    ll height;
//    ~Node(){
//        delete left;
//        delete right;
//    }
};

typedef Node* vertex;

//vertex constroot;

class avl_tree {
public:
//    vertex root;

    avl_tree() {
//        root = nullptr;
//        constroot = new Node;
//        constroot->element = 1000000001;
//        constroot->left = nullptr;
//        constroot->right = nullptr;
//        constroot->height = -1;
    }
    void insert(ll x, vertex& v) {
//        if(v == constroot) v = root;
        if (v == nullptr) {
            v = new Node;
            v->element = x;
            v->left = nullptr;
            v->right = nullptr;
            v->height = 0;
        }
        else {
            if (x < v->element) {
                insert(x, v->left);
                if ((height(v->left) - height(v->right)) == 2) {
                    if (x < v->left->element) {
                        v = small_right_rotate(v);
                    }
                    else {
                        v = big_right_rotate(v);
                    }
                }
            }
            else if (x > v->element) {
                insert(x, v->right);
                if ((height(v->right) - height(v->left)) == 2) {
                    if (x > v->right->element) {
                        v = small_left_rotate(v);
                    }
                    else {
                        v = big_left_rotate(v);
                    }
                }
            }
        }
        v->height = max(height(v->left), height(v->right)) + 1;
    }// Вставляем вершину с ключои x

    vertex exists(ll x, vertex& v) {
//        if(v == constroot) v = root;
        if (v == nullptr) {
//            cout << "false" << '\n';
            return nullptr;
        }
        else {
            if (x < v->element) {
                return exists(x, v->left);
            }
            else {
                if (x > v->element) {
                    return exists(x, v->right);
                }
                else {
//                    cout << "true" << '\n';
                    return v;
                }
            }
        }
    }// Проверка существования вершины по ключу x

    void delete_vertex(ll x, vertex& v) {
//        if(v == constroot) v = root;
        if (v == nullptr) {}
        else if (x < v->element) {
            delete_vertex(x, v->left);
        }
        else if (x > v->element) {
            delete_vertex(x, v->right);
        }
        else if ((v->left == nullptr) && (v->right == nullptr)) {
            vertex temp = v;
            v = nullptr;
            delete temp;
        }
        else if (v->left == nullptr) {
            vertex temp = v;
            v = v->right;
            delete temp;
        }
        else if (v->right == nullptr) {
            vertex temp = v;
            v = v->left;
            delete temp;
        }
        else {
            v->element = delete_min(v->right);
        }
    }// Удаление вершины по ключу x

    ll delete_min(vertex& v) {
        if (v->left == nullptr) {
            ll temp = v->element;
            vertex temp_v = v;
            v = v->right;
            delete temp_v;
            return temp;
        }
        else {
            return delete_min(v->left);
        }
    } // Удаляет наименьший ключ в поддереве вершины v

    bool next(ll x, ll& result, vertex v){
        if (v == nullptr) return false;

        if (x >= v->element) {
            return next(x, result, v->right);
        }
        else {
            if(!next(x, result, v->left)) {
                result = v->element;
            }
            return true;
        }
    }

    bool prev(ll x, ll& result, vertex& v) {
        if(v == nullptr) return false;

        if(x <= v->element) {
            return prev(x, result, v->left);
        } else {
            if(!prev(x, result, v->right)) {
                result = v->element;
            }
            return true;
        }
    }

    ll height(vertex& v) {
        if (v == nullptr) {
            return -1;
        }
        else {
            return v->height;
        }
    }// Получение высоты поддерева вершины v

    vertex small_right_rotate(vertex& v1) {
        vertex v2;
        v2 = v1->left;
        v1->left = v2->right;
        v2->right = v1;
        v1->height = max(height(v1->left), height(v1->right)) + 1;
        v2->height = max(height(v2->left), v1->height) + 1;
        return v2;
    }// Малое правое вращение с вершиной v1 в корне

    vertex small_left_rotate(vertex& v1) {
        vertex v2;
        v2 = v1->right;
        v1->right = v2->left;
        v2->left = v1;
        v1->height = max(height(v1->left), height(v1->right)) + 1;
        v2->height = max(v1->height,height(v2->right)) + 1;
        return v2;
    }// Малое левое вращение с вершиной v1 в корне

    vertex big_right_rotate(vertex& v1) {
        v1->left = small_left_rotate(v1->left);
        return small_right_rotate(v1);
    }// Большое правое вращение с вершиной v1 в корне

    vertex big_left_rotate(vertex& v1) {
        v1->right = small_right_rotate(v1->right);
        return small_left_rotate(v1);
    }// Большое левое вращение с вершиной v1 в корне

    void cout_in_order(vertex v) {
        if (v != nullptr) {
            cout_in_order(v->left);
            cout << v->element << '\t';
            cout_in_order(v->right);
        }
    }// вывести в порядке возрастания

    void delete_tree(vertex& v)
    {
        vertex temp;
        if (v != nullptr)
        {
            delete_tree(v->left);
            delete_tree(v->right);
            temp = v;
            delete temp;
            v = nullptr;
        }
    }
};


int main() {
//    string s;
//    ll x;
    avl_tree a;
    vertex root_a = nullptr;
//    cin >> s;
//    do {
//    cin >> x;
//    if (s[0] == 'i') {
//        a.insert(x, root_a);
//    } else if (s[0] == 'd') {
//        a.delete_vertex(x, root_a);
//    } else if (s[0] == 'e') {
//        if (a.exists(x, root_a) == nullptr) {
//            cout << "false" << '\n';
//        } else {
//            cout << "true" << '\n';
//        }
//    } else if (s[0] == 'n') {
//        ll temp = 1000000001;
//        a.next(x, temp, root_a);
//        if (temp == 1000000001) cout << "none" << '\n';
//        else cout << temp << '\n';
//    } else if (s[0] == 'p') {
//        ll temp = 1000000001;
//        a.prev(x, temp, root_a);
//        if (temp == 1000000001) cout << "none" << '\n';
//        else cout << temp << '\n';
//    }
//    }while(cin >> s);
//        cout << '\n';
//        a.cout_in_order(root_a);
//        cout << '\n';
//    a.delete_tree(root_a);
//    cout << '\n';
//    a.cout_in_order(root_a);
//    cout << '\n';

    for (ll i = 0; i < 10000; ++i) {
        a.insert(i, root_a);
    }
//    for (ll i = 100000000; i > 0; --i) {
//        a.insert(i, root_a);
//    }
//    for (ll i = 0; i < 100000000; ++i) {
//        a.delete_vertex(i, root_a);
//    }
//    cout << '\n';
//    a.cout_in_order(root_a);
//    cout << '\n';
/*
    avl_tree b;
    vertex root = nullptr;
    b.insert(300, root);
    b.insert(200, root);
    b.insert(100, root);
    b.insert(10003, root);

    b.preorder(root);
    cout << '\n';

    b.inorder(root);
    cout << '\n';

    b.postorder(root);
    cout << '\n';

    ll t = -1;
    cout << b.find_min(root)->element << '\n';
    cout << b.find_max(root)->element << '\n';
    b.next(100, t, root);
    cout << t << '\n';
    b.prev(10003, t, root);
    cout << t << '\n';
    */
/*
    srand(time(nullptr));
    ll MIN = -1500;
    ll MAX = 1500;

    for (ll i = 0; i < 1000; ++i) {
        avl_tree tree;
        vertex root = nullptr;
        vector<ll> arr;

        for (ll j = 0; j < 500 + rand() % 500; ++j) {
            ll x = rand() % (MAX - MIN + 1) + MIN;
            arr.push_back(x);
            tree.insert(x, root);
        }

        for (ll j : arr) {
            if (!tree.exists(j, root)) {
                throw runtime_error("Element " + to_string(j) + " doesn't exist in tree");
            }
        }

        sort(arr.begin(), arr.end());
        auto it = arr.begin();

        for (ll j = MIN; j <= MAX; ++j) {
            if (tree.exists(j, root)) {
                if (it == arr.end() || *it != j)
                    throw runtime_error("Element " + to_string(j) + " exist in tree");
                else while (it != arr.end() && *it == j) ++it;
            }
        }

        it = arr.begin();
        for (ll j = MIN; j <= MAX; ++j) {
            ll result = 0;
            while (it != arr.end() && *it == j) ++it;
            bool next = tree.next(j, result, root);
            if (next && it == arr.end())
                throw runtime_error("There is no next after " + to_string(j) +
                                    ", but the tree thinks that it's " + to_string(result));
            else if (!next && it != arr.end())
                throw runtime_error("Tree thinks that there is no next after " + to_string(j) +
                                    ", but it actually is " + to_string(*it));
            else if (next && result != *it)
                throw runtime_error("Tree thinks that next after " + to_string(j) +
                                    " is " + to_string(result) + ", but it actually is " + to_string(*it));
        }

        auto rit = arr.rbegin();
        for (ll j = MAX; j >= MIN; --j) {
            ll result = 0;
            while (rit != arr.rend() && *rit == j) ++rit;
            bool prev = tree.prev(j, result, root);
            if (prev && rit == arr.rend())
                throw runtime_error("There is no prev before " + to_string(j) +
                                    ", but the tree thinks that it's " + to_string(result));
            else if (!prev && rit != arr.rend())
                throw runtime_error("Tree thinks that there is no prev before " + to_string(j) +
                                    ", but it actually is " + to_string(*rit));
            else if (prev && result != *rit)
                throw runtime_error("Tree thinks that prev before " + to_string(j) +
                                    " is " + to_string(result) + ", but it actually is " + to_string(*rit));
        }

        ll els_to_remove = 1 + rand() % (arr.size() - 1);
        for (ll j = 0; j < els_to_remove; ++j) {
            if(!arr.empty()) {
                ll index = rand() % (arr.size());
                ll x = arr[index];
////            arr.erase(arr.begin() + index);
//                while (find(arr.begin(), arr.end(), x) != arr.end()) {
//                    arr.erase(arr.begin() + index);
//                }
                for (ll k = 0; k < arr.size(); ++k){
                    if (arr[k] == x) {
                        arr.erase(arr.begin() + k);
                        k--;
                    }
                }
                tree.delete_vertex(x, root);
            }
        }

        for (ll j = 0; j < arr.size(); ++j) {
            ll x = MIN + rand() % (MAX - MIN + 1);
            bool flag = true;
            for (ll e : arr)
                if (e == x) {
                    flag = false;
                    break;
                }
            if (flag)
                tree.delete_vertex(x, root);
        }

        for (ll j : arr) {
            if (!tree.exists(j, root)) {
                throw runtime_error("Element " + to_string(j) + " doesn't exist in tree (after removing)");
            }
        }

        sort(arr.begin(), arr.end());
        it = arr.begin();

        for (ll j = MIN; j <= MAX; ++j) {
            if (tree.exists(j, root)) {
                if (it == arr.end() || *it != j)
                    throw runtime_error("Element " + to_string(j) + " exist in tree (after removing)");
                else while (it != arr.end() && *it == j) ++it;
            }
        }

        it = arr.begin();
        for (ll j = MIN; j <= MAX; ++j) {
            ll result = 0;
            while (it != arr.end() && *it == j) ++it;
            bool next = tree.next(j, result, root);
            if (next && it == arr.end())
                throw runtime_error("There is no next after " + to_string(j) +
                                    ", but the tree thinks that it's " + to_string(result) + " (after removing)");
            else if (!next && it != arr.end())
                throw runtime_error("Tree thinks that there is no next after " + to_string(j) +
                                    ", but it actually is " + to_string(*it) + " (after removing)");
            else if (next && result != *it)
                throw runtime_error("Tree thinks that next after " + to_string(j) + " is " + to_string(result) +
                                    ", but it actually is " + to_string(*it) + " (after removing)");
        }

        rit = arr.rbegin();
        for (ll j = MAX; j >= MIN; --j) {
            ll result = 0;
            while (rit != arr.rend() && *rit == j) ++rit;
            bool prev = tree.prev(j, result, root);
            if (prev && rit == arr.rend())
                throw runtime_error("There is no prev before " + to_string(j) +
                                    ", but the tree thinks that it's " + to_string(result) + " (after removing)");
            else if (!prev && rit != arr.rend())
                throw runtime_error("Tree thinks that there is no prev before " + to_string(j) +
                                    ", but it actually is " + to_string(*rit) + " (after removing)");
            else if (prev && result != *rit)
                throw runtime_error("Tree thinks that prev before " + to_string(j) +
                                    " is " + to_string(result) + ", but it actually is " + to_string(*rit) + " (after removing)");
        }
//        delete root;
    }*/
    system("pause");
    system("cls");
    return 0;
}

