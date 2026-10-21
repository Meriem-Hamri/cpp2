#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::reverse(coll.begin(), coll.end());

    for (int x : coll) {
        std::cout << x << " ";
    }

    return 0;
}