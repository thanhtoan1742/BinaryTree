#include <algorithm>
#include <functional>

using namespace std;

template <class K, class V>
class AVLTree {
public:
    class Node {
    protected:
        Node* left;
        Node* right;
        int bf;
        int nE;
    public:
        const K key;
        V value;

    private:
        Node(K _key, V _value, Node* _left = nullptr, Node* _right = nullptr)
        : left(_left), right(_right), bf(0), nE(1), key(_key), value(_value) {
        }

        friend class AVLTree;
    };

protected:
    Node* root;
    int nE;

protected:
    int order_of_key(Node* root, const K& key) {
        if (!root)
            return size();
        
        int cl = root->left ? root->left->nE : 0;
        if (key == root->key)
            return cl;
        if (key < root->key)
            return order_of_key(root->left, key);
        else 
            return cl + 1 + order_of_key(root->right, key);
    }

    Node* find_by_order(Node* root, int order) {
        int cl = root->left ? root->left->nE : 0;
        if (order == cl)
            return root;

        if (order < cl)
            return find_by_order(root->left, order);
        else
            return find_by_order(root->right, order - cl - 1);
    }

    Node* find_by_key(Node* root, const K& key) {
        if (!root)
            return nullptr;

        if (key == root->key)
            return root;

        if (key < root->key)
            return find_by_key(root->left, key);
        else
            return find_by_key(root->right, key);

    }

    void inorder_traverse(Node* root, function<void(const K&, V&)> op) {
        if (!root)
            return;

        inorder_traverse(root->left, op);
        op(root->key, root->value);
        inorder_traverse(root->right, op);
    }   

    Node* add(Node*& root, const K& key, const V& value) {
        if (!root)  {
            root = new Node(key, value);
            return root;
        }

        Node* p = nullptr;
        if (key < root->key)
            p = add(root->left, key, value);
        else
            p = add(root->right, key, value);

        root->nE++;
        return p;
    }

    Node* get_inorder_successor(Node* root) {
        root = root->left;
        while (root->right)
            root = root->right;
        return root;
    }

    void remove_by_key(Node*& root, const K& key) {
        if (key == root->key) {
            if (!root->left && !root->right) {
                delete root;
                root = nullptr;
                return;
            }

            if (root->left && !root->right) {
                auto p = root;
                root = p->left;
                delete p;
                return;
            }

            if (!root->left && root->right) {
                auto p = root;
                root = p->right;
                delete p;
                return;
            }

            Node* s = get_inorder_successor(root);
            Node* p = root;
            root = new Node(s->key, s->value, p->left, p->right);
            root->nE = p->nE;
            delete p;
            remove_by_key(root->left, key);
            root->nE--;
            return;
        }

        if (key < root->key)
            remove_by_key(root->left, key);
        else
            remove_by_key(root->right, key);
        root->nE--;
    }

    void clear(Node* root) {
        if (!root)
            return;
        
        clear(root->left);
        clear(root->right);
        delete root;
    }

public:
    AVLTree()
    : root(nullptr), nE(0) {
    }

    int order_of_key(const K& key) {
        return min(order_of_key(root, key), size());
    }

    Node* find_by_order(int order) {
        if (order < 0 || order >= size())
            throw "not in range";

        return find_by_order(root, order);
    }

    Node* find_by_key(const K& key) {
        return find_by_key(root, key);
    }

    int count(const K& key) {
        return find_by_key(key) != nullptr;
    }

    int size() {
        return nE;
    }

    bool empty() {
        return !nE;
    }

    void inorder_traverse(function<void(const K&, V&)> op) {
        inorder_traverse(root, op);
    }   

    Node* add(const K& key, const V& value) {
        Node* p = add(root, key, value);
        ++nE;
        return p;
    }

    void remove_by_order(int order) {
        Node* p = find_by_order(order);
        remove_by_key(p->key);
    }

    void remove_by_key(const K& key) {
        remove_by_key(root, key);
        --nE;
    }

    void clear() {
        clear(root);
        nE = 0;
        root = nullptr;
    }
};