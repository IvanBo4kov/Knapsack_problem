#include <vector>
#include <iostream>

using namespace std;

int solve(const int& n, const vector<int>& values, const vector<int>& weights, const int& W) {
    vector<vector<int>> memo(n+1, vector<int>(W+1));
    for (int i = 0; i <= W; i++) {
        memo[0][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            memo[i][j] = memo[i-1][j];
            if (j - weights[i - 1] >= 0) {
                memo[i][j] = max(memo[i][j], memo[i-1][j - weights[i-1]] + values[i-1]);
            }
        }
    }
    return memo[n][W];
}

int main() {
    int n, W;
    cin >> n >> W;
    vector<int> values;
    vector<int> weights;
    for (int i = 0; i < n; i++) {
        int value, weight;
        cin >> value >> weight;
        values.push_back(value);
        weights.push_back(weight);
    }
    int max_val = solve(n, values, weights, W);
    cout << max_val << endl;
    return 0;
}
