#include "BSTree.hpp"

#include <iostream>

// TODO: add unittest.
int main() {
    BSTree<int> bst;

    int n = 15;
    for (int i = 0; i < n; ++i) {
        int val = rand()%100;
        
        std::cout << val << ' ';
        bst.add(val);
    }
    std::cout << '\n';

    bst.inorderTraverse([](int& e) {
        std::cout << e << ' ';
    });
    std::cout << '\n';

}