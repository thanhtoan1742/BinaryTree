#include <iostream>

using namespace std;

template<typename T>
class AVLTRee {
private:
    class Node {
        T data;
        int bf; // balance factor
        Node* left, right;

        Node() {
        }

        Node(T _data, int _bf = 0, Node* _left = nullptr, Node* _right = nullptr)
        : data(_data), bf(_bf), left(_left), right(_right) {
        }
    };

private:
    Node* root;
    int nElements;

    /*
     * Balance the tree if root is imbalance.
     * return whether the tree has grown or not (1/0).
     */
    int balance(Node* root) {
        if (root->bf > 1 || root->bf < -1)
            return 0;
    }

    /*
     * return whether the tree has grown or not (1/0).
     */
    int insert(Node* root, const T& data) {
        if (!root) {
            root = new Node(data);
            return 1;
        }

        if (data < root->data) 
            root->bf -= insert(root->left, data);
        else 
            root->bf += insert(root->right, data);

        return balance(root);
    }

public:
    AVLTRee() {
        nElements = 0;
        root = nullptr;
    }

    int size() {
        return nElements;
    }

    bool empty() {
        return nElements;
    }

    void insert(const T& data) {
        insert(root, data);
    }
};

