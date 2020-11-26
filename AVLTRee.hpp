#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>
#include <string>
#include <queue>
#include <sstream>
#include <utility>

using namespace std;

template<typename T>
class AVLTRee {
    string SPACE;

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
    int height;

    void rotateLeft(Node*& pRoot) {
        auto p = pRoot->pRight;
        pRoot->pRight = p->pLeft;
        p->pLeft = pRoot;
        pRoot = p;
    }

    void rotateRight(Node*& pRoot) {
        auto p = pRoot->pLeft;
        pRoot->pLeft = p->pRight;
        p->pRight = pRoot;
        pRoot = p;
    }

    int balance(Node*& pRoot) {
        if (pRoot->bf < -1 && pRoot->pLeft->bf == -1) {
            rotateRight(pRoot);
            pRoot->bf = 0;
            pRoot->pRight->bf = 0;
            return 0;
        }

        if (pRoot->bf < -1 && pRoot->pLeft->bf == 0) {
            rotateRight(pRoot);
            pRoot->bf = 1;
            pRoot->pRight->bf = -1;
            return 1;
        }

        if (pRoot->bf < -1 && pRoot->pLeft->bf == 1) {
            rotateLeft(pRoot->pLeft);
            rotateRight(pRoot);
            pRoot->pLeft->bf = !(pRoot->bf == 1);
            pRoot->pRight->bf = -(pRoot->bf == -1);
            pRoot->bf = 0;
            return 0;
        }

        if (pRoot->bf > 1 && pRoot->pRight->bf == 1) {
            rotateLeft(pRoot);
            pRoot->bf = 0;
            pRoot->pLeft->bf = 0;
            return 0;
        }

        if (pRoot->bf > 1 && pRoot->pRight->bf == 0) {
            rotateLeft(pRoot);
            pRoot->bf = -1;
            pRoot->pLeft->bf = 1;
            return 1;
        }

        if (pRoot->bf > 1 && pRoot->pRight->bf == -1) {
            rotateRight(pRoot->pRight);
            rotateLeft(pRoot);
            pRoot->pLeft->bf = !(pRoot->bf == 1);
            pRoot->pRight->bf = -(pRoot->bf == -1);
            pRoot->bf = 0;
            return 0;
        }

        return 0;
    }

    int insert(Node*& pRoot, const T& data) {
        if (!pRoot) {
            pRoot = new Node(data);
            return 1;
        }

        if (data < pRoot->data) {
            pRoot->bf -= insert(pRoot->pLeft, data);
            if (pRoot->bf < -1) 
                return balance(pRoot);
            return pRoot->bf == -1;
        }
        else {
            pRoot->bf += insert(pRoot->pRight, data);
            if (pRoot->bf > 1) 
                return balance(pRoot);
            return pRoot->bf == 1;
        } 

        return 0;
    }

    Node* inorderSuccessor(Node* pRoot) {
        pRoot = pRoot->pLeft;
        while (pRoot->pRight)
            pRoot = pRoot->pRight;
        return pRoot;
    }
    
    int remove(Node*& pRoot, const T& data) {
        if (!pRoot) 
            return 0;

        if (data < pRoot->data) {
            pRoot->bf += remove(pRoot->pLeft, data);
            if (pRoot->bf > 2) {
                int g = balance(pRoot);
                return !g;
            }
            return 0; 
        }

        if (data > pRoot->data) {
            remove(pRoot->pLeft, data);
            if (pRoot->bf < -2) {
                int g = balance(pRoot);
                return !g;
            }

            return 0; 
        }

        if (!pRoot->pLeft && !pRoot->pRight) {
            delete pRoot;
            pRoot = nullptr;
            return 1;
        }

        if (pRoot->pLeft && !pRoot->pRight) {
            auto p = pRoot;
            pRoot = p->pLeft;
            delete p;
            return 1;
        }

        if (!pRoot->pLeft && pRoot->pRight) {
            auto p = pRoot;
            pRoot = p->pRight;
            delete p;
            return 1;
        }

        auto p = inorderSuccessor(pRoot);
        pRoot->data = p->data;
        remove(pRoot->pLeft, data);
        if (pRoot->bf < -2) {
            int g = balance(pRoot);
            return !g;
        }
        return 0; 
    }

    void preorderTraverse(Node* pRoot, function<void (T&)> op) {
        if (!pRoot)
            return;

        preorderTraverse(pRoot->pLeft, op);
        preorderTraverse(pRoot->pRight, op);
        op(pRoot->data);
    }

    void inorderTraverse(Node* pRoot, function<void (T&)> op) {
        if (!pRoot)
            return;

        inorderTraverse(pRoot->pLeft, op);
        op(pRoot->data);
        inorderTraverse(pRoot->pRight, op);
    }

    void postorderTraverse(Node* pRoot, function<void (T&)> op) {
        if (!pRoot)
            return;

        postorderTraverse(pRoot->pLeft, op);
        postorderTraverse(pRoot->pRight, op);
        op(pRoot->data);
    }
    
    string dataFormatOut(const T& data) {
        stringstream ss;
        ss << data;

        stringstream res;
        while (ss.str().size() < SPACE.size()) {
            res << ' ';
            ss << ' ';
        }

        res << data;
        return res.str();      
    }

public:
    AVLTRee() {
        nElements = 0;
        height = 0;
        pRoot = nullptr;
        SPACE = "   ";
    }

    int size() {
        return nElements;
    }

    bool empty() {
        return nElements;
    }

    void insert(const T& data) {
        height += insert(pRoot, data);
        ++nElements;
    }

    void remove(const T& data) {
        height -= remove(pRoot, data);
        --nElements;
    }

    // void removeByIndex(int index) {

    // }

    void preorderTraverse(function<void (T&)> op) {
        return preorderTraverse(pRoot, op);
    }

    void inorderTraverse(function<void (T&)> op) {
        return inorderTraverse(pRoot, op);
    }

    void postorderTraverse(function<void (T&)> op) {
        return postorderTraverse(pRoot, op);
    }

    void log() {
        cout << setw(SPACE.size());
        cout << "size: " << nElements << '\n';        

        queue<Node*>* cur = new queue<Node*>();
        queue<Node*>* nex = new queue<Node*>();

        cur->push(pRoot);
        for (int h = height; h; --h) {
            for (int i = 1; i < (1 << (h - 1)); ++i) 
                cout << SPACE;

            bool first = 1;
            while (!cur->empty()) {
                if (first) 
                    first = 0;
                else
                    for (int i = 1; i < (1 << h); ++i) 
                        cout << SPACE;

                auto u = cur->front();
                cur->pop();

                if (u) {
                    cout << dataFormatOut(u->data);
                    nex->push(u->pLeft);
                    nex->push(u->pRight);
                }
                else {
                    cout << SPACE;      
                    nex->push(nullptr);
                    nex->push(nullptr);
                }
            }

            for (int i = 1; i < (1 << (h - 1)); ++i) 
                cout << SPACE;
            cout << '\n';
            swap(cur, nex);
        }
        
        delete cur;
        delete nex;
        cout << "\n\n";
    }
};