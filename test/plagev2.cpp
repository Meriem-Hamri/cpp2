#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <iterator>
using namespace std;

int main(){
    deque<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    deque<int>::const_iterator pos1;
    pos1 = std::find(coll.cbegin(), coll.cend(), 2);

    deque<int>::const_iterator pos2;
    pos2 = std::find(coll.cbegin(), coll.cend(), 7);

    auto print = [](int value) { cout << value << ' '; };
    for_each(pos1, pos2, print);
    cout << endl;

    deque<int>::const_reverse_iterator rpos1(pos1);
    deque<int>::const_reverse_iterator rpos2(pos2);

    for_each(rpos2, rpos1,print);
    cout << endl;

}