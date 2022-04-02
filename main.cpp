#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int solve(int n, vector<int> values, vector<int> weights, int W) {
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
    int result = 0;
    for (int i = W; i >= 0; i--) {
        if(memo[n][i] != 0) {
            result = memo[n][i];
            break;
        }
    }
    return result;
}

int main() {
    string path = "/Users/ivanbockov/knapsack";
       auto it = fs::directory_iterator(path);
       vector<fs::path> array_path;
       copy_if(fs::begin(it), fs::end(it), std::back_inserter(array_path),
           [](const auto& entry) {
               return fs::is_regular_file(entry);
       });
    for (auto& p : array_path) {
        ifstream fin;
        fin.open(p.string());
        int n, W;
        fin >> n >> W;
        vector<int> values;
        vector<int> weights;
        for (int i = 0; i < n; i++) {
            int value, weight;
            fin >> value >> weight;
            values.push_back(value);
            weights.push_back(weight);
        }
        int max_value = solve(n, values, weights, W);
        cout << max_value << endl;
    }
    return 0;
}
