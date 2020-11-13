#include "BSTree.hpp"
#include "AVLTRee.hpp"
#include <vector>

#include <iostream>

int main() {
    AVLTRee<int> avl;
    vector<int> items = {21, 23, 3, 14, 5};

    for (auto e: items)
        avl.insert(e);
    
    avl.inorderTraverse([](const int& e) {
        cout << e << ' ';
    });
    cout << '\n';

    cout << "Accepted, no error\n";
}
