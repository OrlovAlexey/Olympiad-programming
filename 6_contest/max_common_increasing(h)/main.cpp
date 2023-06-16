#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

void solution(int size1, const vector<int>& first_sequence, int size2, const vector<int>& second_sequence, vector<vector<int>>& dp) {
    int dp_for_best_element;
    for (int i = 1; i <= size1; ++i) {
        dp_for_best_element = 0;
        for (int j = 1; j <= size2; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (first_sequence[i-1] == second_sequence[j-1] && dp[i-1][j] < dp_for_best_element + 1) {
                dp[i][j] = dp_for_best_element + 1;
            }
            if (first_sequence[i-1] > second_sequence[j-1] && dp[i-1][j] > dp_for_best_element) {
                dp_for_best_element = dp[i-1][j];
            }
        }
    }
}

void print_answer(int size1, int size2, const vector<vector<int>>& dp) {
    int answer = 0;
    for (int j = 1; j <= size2; ++j) {
        if (answer < dp[size1][j]) {
            answer = dp[size1][j];
        }
    }
    cout << answer << '\n';
}

int main() {
    int size1, size2;
    cin >> size1 >> size2;
    vector<int> first_sequence(size1), second_sequence(size2);
    for (int i = 0; i < size1; ++i) {
        cin >> first_sequence[i];
    }
    for (int j = 0; j < size2; ++j) {
        cin >> second_sequence[j];
    }
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, 0));
    solution(size1, first_sequence, size2, second_sequence, dp);
    print_answer(size1, size2, dp);
    return 0;
}
