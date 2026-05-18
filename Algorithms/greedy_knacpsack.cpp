#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(pair<int,int> a, pair<int,int> b) {
    return (double)a.first / a.second > (double)b.first / b.second;}

int main() {
    // {value, weight}
    vector<pair<int,int>> items = {{50,4}, {70,5}, {60,3}, {90,6}, {40,2}};
    int W = 15; // capacity

    // Step 1: Sort by value/weight per kg
    sort(items.begin(), items.end(), cmp);
    double totalValue = 0;

    for (auto it : items) {
        if (W >= it.second) {
            totalValue += it.first;   // take full
            W -= it.second;
        } else {
            totalValue += (double)it.first * W / it.second; // take fraction
            break; // stop
        }
    }

    cout << "Maximum value = " << totalValue << endl;
}