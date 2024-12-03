import java.util.*;

public class BuzzDaySale {
public static void main(String[] args) {
Scanner sc = new Scanner(System.in);

// Read input data

int n = sc.nextInt(); // Number of items
int[] ids = new int[n]; // Item IDs

int[] costs = new int[n]; // Item costs

for (int i = 0; i <n; i++) {
ids[i] = sc.nextInt();

for (int i = 0; i <n; i++) {
costs[i] = sc.nextInt();


int budget = sc.nextInt(); // Amount Veda has

// Step 1: Precompute divisors for each ID T
List<Integer>[] divisors = new List[1001]; // For IDs from 1 to 1000
for (int i = 1; i <= 1000; i++) {

divisors[i] = new ArrayList<>();

// Store divisors for each ID in the range 1 to 1000
for (int i = 1; i <= 1000; i++) {
for (int j = i; j <= 1000; j += i) {
divisors[j].add(i);



// Step 2: Map each item ID to its free item count and free item worth
Map<Integer, Integer> freeItemCount = new HashMap<>();
Map<Integer, Integer> freeItemWorth = new HashMap<>();

// Step 3: Calculate the free items for each ID
for (int i = @; i <n; i++) {
int itemId = ids[i];
for (int divisor : divisors[itemId]) {
for (int j = 0; j <n; j++) {
if (ids[j] == divisor && i != j) {
freeItemCount.put(itemId, freeItemCount.getOrDefault(itemId, @) + 1);
freeItemWorth.put(itemId, freeItemWorth.getOrDefault(itemId, @) + costs[j]);

// Step 4: Try each item for purchase and calculate the number of free items and their worth
Q; ly

9;

int maxFreeItems
int maxFreeWorth

for (int i = @; i< n; i++) {
int itemCost = costs[i];
int maxQuantity = budget / itemCost;

if (maxQuantity > @) {
// Free items and worth for purchasing this item
int freeItems = freeItemCount.getOrDefault(ids[i], @) * maxQuantity;
int freeWorth = freeItemWorth.getOrDefault(ids[i], @) * maxQuantity;


// Update if we find a better solution

if (freeItems > maxFreeItems || (freeItems == maxFreeItems && freeWorth > maxFreeWorth)) {
maxFreeItems = freeItems;
maxFreeWorth = freeWorth;

// Output the result
System.out.print(maxFreeItems +

+ maxFreeWorth) ;

sc.close();







#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


int main() {
    int n;
    cin >> n;

    vector<int> ids(n), costs(n);
    for (int i = 0; i < n; i++) cin >> ids[i];
    for (int i = 0; i < n; i++) cin >> costs[i];

    int budget;
    cin >> budget;

    int mfi = 0, mfw = 0;

    for (int i = 0; i < n; i++) {
        int buyCost = costs[i];
        int maxQty = budget / buyCost;

        if (maxQty > 0) {
            int cfi = 0;
            int cfw = 0;


            for (int j = 0; j < n; j++) {
                if (i != j && ids[i] % ids[j] == 0) {
                    cfi += maxQty;
                    cfw += costs[j] * maxQty;
                }
            }

            if (cfi > mfi || 
               (cfi == mfi && cfw > mfw)) {
                mfi = cfi;
                mfw = cfw;
            }
        }
    }

    cout << mfi << " " << mfw << endl;
    return 0;
}

Buzz Sale