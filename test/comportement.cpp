#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3};

    auto it = v.begin();

    v.insert(v.begin(), 0);

    cout << *it;
}
