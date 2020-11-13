#include <functional>

using namespace std;

template<typename T>
class AVLTRee {
private:
    class Node {
    public:
        T data;
        int bf; // balance factor
        Node* pLeft;
        Node* pRight;

        Node() {
        }

        Node(T _data, int _bf = 0, Node* _left = nullptr, Node* _right = nullptr)
        : data(_data), bf(_bf), pLeft(_left), pRight(_right) {
        }
    };

private:
    Node* pRoot;
    int nElements;

    /*
     * Balance the tree if root is imbalance.
     * Return whether the tree has grown or not (1/0).
     */
    int balance(Node*& pRoot) {
        return 0;
    }

    /*
     * Return whether the tree has grown or not (1/0).
     */
    int insert(Node*& pRoot, const T& data) {
        if (!pRoot) {
            pRoot = new Node(data);
            return 1;
        }

        if (data < pRoot->data) 
            pRoot->bf -= insert(pRoot->pLeft, data);
        else 
            pRoot->bf += insert(pRoot->pRight, data);

        if (pRoot->bf > 1 || pRoot->bf < -1)
            return 0;
        return balance(pRoot);
    }

    void inorderTraverse(Node* pRoot, function<void (T&)> op) {
        if (!pRoot)
            return;

        inorderTraverse(pRoot->pLeft, op);
        op(pRoot->data);
        inorderTraverse(pRoot->pRight, op);
    }

public:
    AVLTRee() {
        nElements = 0;
        pRoot = nullptr;
    }

    int size() {
        return nElements;
    }

    bool empty() {
        return nElements;
    }

    void insert(const T& data) {
        insert(pRoot, data);
    }

    void inorderTraverse(function<void (T&)> op) {
        return inorderTraverse(pRoot, op);
    }
};

