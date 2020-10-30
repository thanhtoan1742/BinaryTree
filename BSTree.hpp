#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <functional>

template<typename T>
class BSTree {
protected:
    class Node {
        T data;
        Node* pLeft;
        Node* pRight;

    public:
        Node(const T& _data);

        friend class BSTree;
    };


    int nElements;
    Node* pRoot;

    T* add(Node*& pRoot, const T& element);
    T remove(Node*& pRoot, const T& element);
    void clear(Node* pRoot);

    void preorderTravesrse(Node* pRoot, std::function<void (T&)> op);
    void inorderTraverse(Node* pRoot, std::function<void (T&)> op);
    void postorderTraverse(Node* pRoot, std::function<void (T&)> op);

public:
    BSTree();
    ~BSTree();

    bool empty();
    int size();

    T* add(const T& element);
    T remove(const T& element);
    void clear();

    void preorderTravesrse(std::function<void (T&)> op);
    void inorderTraverse(std::function<void (T&)> op);
    void postorderTraverse(std::function<void (T&)> op);

};

template<typename T>
BSTree<T>::Node::Node(const T& _data) 
: data(_data), pLeft(nullptr), pRight(nullptr) {
}


template<typename T> 
BSTree<T>::BSTree() {
    pRoot = nullptr;
    nElements = 0;
}
template<typename T> 
BSTree<T>::~BSTree() {
    clear();
}

template<typename T> 
bool BSTree<T>::empty() {
    return !empty();
}

template<typename T> 
int BSTree<T>::size() {
    return nElements;
}

template<typename T> 
T* BSTree<T>::add(Node*& pRoot, const T& element) {
    if (!pRoot) {
        pRoot = new Node(element);
        ++nElements;
        return &pRoot->data;
    }

    if (element < pRoot->data)
        return add(pRoot->pLeft, element);
    else 
        return add(pRoot->pRight, element);
};

template<typename T> 
T* BSTree<T>::add(const T& element) {
    return add(pRoot, element);
}

template<typename T> 
T BSTree<T>::remove(Node*& pRoot, const T& element) {
    return T();
}

template<typename T> 
T BSTree<T>::remove(const T& element) {
    return remove(pRoot, element);
}

template<typename T> 
void BSTree<T>::clear(Node* pRoot) {
    if (pRoot) {
        clear(pRoot->pLeft);
        clear(pRoot->pRight);
        delete pRoot;
    }
} 

template<typename T> 
void BSTree<T>::clear() {
    clear(pRoot);
}

template<typename T>
void BSTree<T>::preorderTravesrse(Node* pRoot, std::function<void (T&)> op) {
    if (!pRoot)
        return;

    op(pRoot->data);
    preorderTravesrse(pRoot->pLeft, op);
    preorderTravesrse(pRoot->pRight, op);
}

template<typename T>
void BSTree<T>::inorderTraverse(Node* pRoot, std::function<void (T&)> op) {
    if (!pRoot)
        return;

    inorderTraverse(pRoot->pLeft, op);
    op(pRoot->data);
    inorderTraverse(pRoot->pRight, op);
}

template<typename T>
void BSTree<T>::postorderTraverse(Node* pRoot, std::function<void (T&)> op) {
    if (!pRoot)
        return;

    postorderTraverse(pRoot->pLeft, op);
    postorderTraverse(pRoot->pRight, op);
    op(pRoot->data);
}

template<typename T>
void BSTree<T>::preorderTravesrse(std::function<void (T&)> op) {
    preorderTravesrse(pRoot, op);
}

template<typename T>
void BSTree<T>::inorderTraverse(std::function<void (T&)> op) {
    inorderTraverse(pRoot, op);
}

template<typename T>
void BSTree<T>::postorderTraverse(std::function<void (T&)> op) {
    postorderTraverse(pRoot, op);
}


#endif // BSTREE_HPP
