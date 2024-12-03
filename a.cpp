
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

vector<pair<int, int>> normalizeShape(const vector<pair<int, int>>& vertices) {
    int n = vertices.size();
    vector<pair<int, int>> minRotation = vertices;

    for (int i = 0; i < n; ++i) {
        vector<pair<int, int>> rotated(vertices.begin() + i, vertices.end());
        rotated.insert(rotated.end(), vertices.begin(), vertices.begin() + i);


        if (rotated < minRotation) {
            minRotation = rotated;
        }
    }
    return minRotation;
}

vector<int> findMatchingPairs(const vector<vector<pair<int, int>>>& earrings) {
    map<vector<pair<int, int>>, vector<int>> normalizedShapes;

    for (int i = 0; i < earrings.size(); ++i) {
        vector<pair<int, int>> normalized = normalizeShape(earrings[i]);
        normalizedShapes[normalized].push_back(i + 1);
    }


    for (const auto& entry : normalizedShapes) {
        if (entry.second.size() == 2) {
            return entry.second;
        }
    }
    return {};
}


int main() {
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> earrings(n);

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        vector<pair<int, int>> vertices(k);
        for (int j = 0; j < k; ++j) {
            cin >> vertices[j].first >> vertices[j].second;
        }
        earrings[i] = vertices;
    }


    vector<int> result = findMatchingPairs(earrings);
    if (!result.empty()) {
        cout << result[0] << " " << result[1] << endl;
    } else {
        cout << endl;
    }

    return 0;
}



Execution Time5.59 sec
Detailspair.cpp In function std vector int findMatchingPairs const std vector std vector std pair int int pair.cpp 28 23 warning comparison of integer expressions of different signedness int and std vector std vector std pair int int size_type aka long unsigned int -Wsign-compare 28 | for int i = 0 i earrings.size ++i | ^




#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> ids(n), costs(n);
    for (int i = 0; i < n; i++) cin >> ids[i];
    for (int i = 0; i < n; i++) cin >> costs[i];

    int budget;
    cin >> budget;

    int mfi = 0, mfw = 0; // Maximum friendliness index and friendliness weight

    for (int i = 0; i < n; i++) {
        if (costs[i] <= 0) continue; // Skip if the cost is invalid (to avoid division by zero)
        int buyCost = costs[i];
        int maxQty = budget / buyCost; // Maximum quantity we can buy with the budget

        if (maxQty > 0) {
            int cfi = 0; // Current friendliness index
            int cfw = 0; // Current friendliness weight

            for (int j = 0; j < n; j++) {
                if (i != j && ids[i] % ids[j] == 0) {
                    cfi += maxQty; // Increment friendliness index
                    cfw += costs[j] * maxQty; // Increment friendliness weight
                }
            }

            // Update maximum friendliness index and weight
            if (cfi > mfi || (cfi == mfi && cfw > mfw)) {
                mfi = cfi;
                mfw = cfw;
            }
        }
    }

    cout << mfi << " " << mfw << endl;
    return 0;
}
