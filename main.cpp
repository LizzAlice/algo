#include <iostream>
#include <vector>
#include <random>
#include "SkipList.h"

using namespace std;

int main() {
    vector<int64_t> vector1 = {5,1,3, 17872, -2, 9,1,9,3};
    SkipList liast(vector1);
    liast.insert(1);
    liast.insert(-6);

    liast.remove(1);
    cout << liast.find(1) << endl;
    cout << liast.find(17872) << endl;
    liast.printSkipList();
    cout << liast.remove(-6) << endl;
    liast.printSkipList();
    return 0;
}