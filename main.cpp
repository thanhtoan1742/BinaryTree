#include "BSTree.hpp"
#include "AVLTRee.hpp"

#include <vector>
#include <iostream>

using namespace std;

template<class T>
void printInorder(AVLTRee<T>& avl) {
    avl.inorderTraverse([](T& e) {
        cout << e << ' ';
    });
    cout << '\n';
}

int main() {
    AVLTRee<int> avl;
    // for (int i = 0; i < 20; ++i) {
    //     int v = rand() % 100;
    //     cout << v << ", ";
    //     avl.insert(v);
    // }
    // cout << '\n';
    vector<int> v = {83, 86, 77, 15, 93, 35, 86, 92, 49, 21, 62, 27, 90, 59, 63, 26, 40, 26, 72, 36};
    for (auto e : v) {
        if (e == 21)
            bool err = true;
        avl.insert(e);
        avl.log();
    }
    printInorder(avl);

    // avl.remove(90);
    // printInorder(avl);
}
