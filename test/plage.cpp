#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto debut = std::find(coll.begin(), coll.end(), 3);
    auto fin = std::find(coll.begin(), coll.end(), 7);

    std::reverse(debut, fin + 1);

    for (int x : coll) {
        std::cout << x << " ";
    }

    return 0;
}