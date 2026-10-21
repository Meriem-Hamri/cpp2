#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::vector<int>::const_reverse_iterator rpos;

    for (rpos = coll.rbegin(); rpos != coll.rend(); rpos+=2) {
        std::cout << *rpos << " ";
    }

    return 0;
}