#include <iostream>
#include <algorithm>
#include <vector>


int main(){
    std::vector<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::vector<int>::const_iterator pos;
    pos = std::find(coll.begin(), coll.end(), 1);

    std::cout << "pos " << *pos << std::endl;

    std::vector<int>::const_reverse_iterator rpos(pos);
    std::cout << "rpos " << *rpos << std::endl;

}