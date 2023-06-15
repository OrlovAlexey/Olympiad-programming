#include <iostream>
#include <stack>

using std::cin;
using std::cout;
using std::stack;


struct Rectangle {
    long long width = 0;
    long long height = 0;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    stack<Rectangle> st;
    long long n;
    long long max_s = 0;
    cin >> n;
    for (long long i = 0; i <= n; ++i) {
        long long h = 0;
        if(i != n){
            cin >> h;
        }
        if(!st.empty() && st.top().height > h){
            while(!st.empty() && st.top().height > h){
                Rectangle pred = st.top();
                st.pop();
                if(max_s < pred.height*pred.width){  max_s = pred.height*pred.width;  } //обновил max_s
                if(!st.empty() && st.top().height > h){  //сравнил высоту предпредыдущего и текущего
                    if(max_s < st.top().height*(st.top().width + pred.width)){
                        max_s = st.top().height*(st.top().width + pred.width); //обновил max_s
                    }
                    Rectangle t = st.top();
                    st.pop();
                    st.push(Rectangle{t.width + pred.width, t.height}); //положил в стек обрезанный прямоугольник большей ширины
                }
                else{
                    if(max_s < h*(1 + pred.width)){
                            max_s = h*(1 + pred.width);  //обновил max_s
                    }
                    st.push(Rectangle{1 + pred.width, h}); //положил в стек обрезанный прямоугольник большей ширины
                    break;
                }
            }
        }
        else{
            st.push(Rectangle{1, h});
        }
    }
    long long sum_width = 0;
    while(!st.empty()){ //обновляем max_s пробегая по неубываюшим прямоугольникам
        Rectangle t = st.top();
        st.pop();
        sum_width += t.width;
        if(max_s < t.height*sum_width){
            max_s = t.height*sum_width;
        }
    }
    cout << max_s << std::endl;
    return 0;
}
