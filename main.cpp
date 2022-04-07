#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int solve(int n, vector<int> values, vector<int> weights, int W) {
    vector<int> memo1(W+1, 0);
    vector<int> memo2(W+1, 0);
    for (int i = 1; i <= n; i++) {
        vector<int> temp = memo1;
        memo1 = memo2;
        memo2 = temp;
        for (int j = 0; j <= W; j++) {
            memo2[j] = memo1[j];
            if (j - weights[i - 1] >= 0) {
                memo2[j] = max(memo2[j], memo1[j - weights[i-1]] + values[i-1]);
            }
        }
    }
    int result = 0;
    for (int i = W; i >= 0; i--) {
        if(memo2[i] != 0) {
            result = memo2[i];
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
        cout << p.string() << endl;
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
