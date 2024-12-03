#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

struct Item {
    int id;
    int cost;
};

vector<int> findFactors(int id, const vector<int>& ids) {
    vector<int> factors;
    for (int other_id : ids) {
        if (other_id != id && id % other_id == 0) {
            factors.push_back(other_id);
        }
    }
    return factors;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) {
        cout << "0 0" << endl;
        return 0;
    }

    vector<Item> items(N);
    vector<int> ids(N);

    // Input item IDs
    for (int i = 0; i < N; ++i) {
        if (!(cin >> items[i].id)) {
            cout << "0 0" << endl;
            return 0;
        }
        ids[i] = items[i].id;
    }

    // Input item costs
    for (int i = 0; i < N; ++i) {
        if (!(cin >> items[i].cost)) {
            cout << "0 0" << endl;
            return 0;
        }
    }

    int A; // Amount Veda has
    if (!(cin >> A)) {
        cout << "0 0" << endl;
        return 0;
    }

    // Precompute factors for each item
    unordered_map<int, vector<int>> itemToFreeItems;
    for (const Item& item : items) {
        vector<int> factors = findFactors(item.id, ids);
        itemToFreeItems[item.id] = factors;
    }

    int maxFreeItems = 0;
    int maxTotalWorth = 0;

    // Iterate over each item to consider as purchase
    for (const Item& item : items) {
        int maxQuantity = A / item.cost; // Maximum quantity of this item Veda can buy
        if (maxQuantity == 0) continue;

        vector<int> freeItemIDs = itemToFreeItems[item.id];
        int numFreePerUnit = freeItemIDs.size();
        int totalCostOfFreePerUnit = 0;

        // Calculate total cost of free items per unit purchase
        for (int freeID : freeItemIDs) {
            auto it = find_if(items.begin(), items.end(), [&](const Item& i) { return i.id == freeID; });
            if (it != items.end()) {
                totalCostOfFreePerUnit += it->cost;
            }
        }

        // Try all possible quantities from 1 to maxQuantity
        for (int qty = 1; qty <= maxQuantity; ++qty) {
            int totalCost = qty * item.cost;
            if (totalCost > A) break;

            int totalFreeItems = qty * numFreePerUnit;
            int totalWorthOfFreeItems = qty * totalCostOfFreePerUnit;

            // Update if we find a better option
            if (totalFreeItems > maxFreeItems || 
                (totalFreeItems == maxFreeItems && totalWorthOfFreeItems > maxTotalWorth)) {
                maxFreeItems = totalFreeItems;
                maxTotalWorth = totalWorthOfFreeItems;
            }
        }
    }

    // Output the result
    cout << maxFreeItems << " " << maxTotalWorth << endl;
    return 0;
}