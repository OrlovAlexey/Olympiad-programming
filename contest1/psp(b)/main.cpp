#include <iostream>
#include <stack>

int main() {
    std::string s;
    std::stack <char> st;
    std::cin >> s;
    for(int i=0; i<s.size(); ++i){
        if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
            st.push(s[i]);
        }
        else{
            if(st.empty()){
                std::cout << "no";
                return 0;
            }
            if(s[i] == ')' && st.top() == '['){
                std::cout << "no";
                return 0;
            }
            if(s[i] == ']' && st.top() == '('){
                std::cout << "no";
                return 0;
            }
            if(s[i] == '}' && st.top() == '['){
                std::cout << "no";
                return 0;
            }
            if(s[i] == '}' && st.top() == '('){
                std::cout << "no";
                return 0;
            }
            if(s[i] == ')' && st.top() == '{'){
                std::cout << "no";
                return 0;
            }
            if(s[i] == ']' && st.top() == '{'){
                std::cout << "no";
                return 0;
            }
            st.pop();
        }
    }
    if(st.empty()){
        std::cout << "yes";
    }
    else{
        std::cout << "no";
    }
    return 0;
}
