#ifndef SPLAY_TREE
#define SPLAY_TREE

#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

template <class K, class V>
class splay_tree {
public:
    class Node {
    protected:
        Node* parent;
        Node* left;
        Node* right;
    public:
        const K key;
        V value;

    private:
        Node(K _key, V _value, Node* _parent = nullptr, Node* _left = nullptr, Node* _right = nullptr)
        : parent(_parent), left(_left), right(_right), key(_key), value(_value) {
        }

    protected:
        void update() {
            if (left) 
                left->parent = this;
            if (right)
                right->parent = this;
        }

        friend class splay_tree;
    };

protected:
    Node* root;
    int nE;

protected:
    void rotate_left(Node*& root) {
        auto p = root->right;
        root->right = p->left;
        p->left = root;
        root = p;

        root->parent = root->left->parent;
        root->left->update();
        root->update();
    }

    void rotate_right(Node*& root) {
        auto p = root->left;
        root->left = p->right;
        p->right = root;
        root = p;

        root->parent = root->right->parent;
        root->right->update();
        root->update();
    }

    Node*& get_true_node(Node* p) {
        if (!p->parent)
            return root;
        else 
            if (p == p->parent->left)
                return p->parent->left;
            else
                return p->parent->right;
    }

    void splay(Node*& p) {
        if (p->parent->parent) {

            if (p->parent == p->parent->parent->left && p == p->parent->left) {
                Node*& root = get_true_node(p->parent->parent);
                rotate_right(root);
                rotate_right(root);
                p = root;
            }
            else if (p->parent == p->parent->parent->right && p == p->parent->right) {
                Node*& root = get_true_node(p->parent->parent);
                rotate_left(root);
                rotate_left(root);
                p = root;
            }
            else if (p->parent == p->parent->parent->left && p == p->parent->right) {
                rotate_left(get_true_node(p->parent));
                Node*& root = get_true_node(p->parent);
                rotate_right(root);
                p = root;
            }
            else if (p->parent == p->parent->parent->right && p == p->parent->left) {
                rotate_right(get_true_node(p->parent));
                Node*& root = get_true_node(p->parent);
                rotate_left(root);
                p = root;
            }
        }
        else {
            Node*& root = get_true_node(p->parent);
            if (p == root->left)
                rotate_right(root);
            else 
                rotate_left(root);

            p = root;
        }
    }

    Node* find(Node* root, const K& key) {
        if (!root)
            return nullptr;

        if (key == root->key)
            return root;

        if (key < root->key)
            return find(root->left, key);
        else
            return find(root->right, key);

    }

    Node* get_right_most(Node* root) {
        while (root->right)
            root = root->right;
        return root;
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

        root->update();
        return p;
    }

    void clear(Node* root) {
        if (!root)
            return;
        
        clear(root->left);
        clear(root->right);
        delete root;
    }

public:
    splay_tree()
    : root(nullptr), nE(0) {
    }

    ~splay_tree() {
        clear();
    }

    Node* find(const K& key) {
        Node* p = find(root, key);
        
        if (!p)
            return p;

        while (p->parent)
            splay(p);

        return p;
    }

    int count(const K& key) {
        return find(key) != nullptr;
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
        while (p->parent)   
            splay(p);
    
        ++nE;
        return p;
    }

    void remove(const K& key) {
        Node* p = find(key);
        if (!p)
            throw "not Found";

        while (p->parent)
            splay(p);

        Node* left = p->left;
        Node* right = p->right;
        if (left)
            left->parent = nullptr;
        if (right)
            right->parent = nullptr;
        delete p;

        if (!left)
            root = right;
        else if (!right)
            root = left;
        else {
            root = left;
            left = get_right_most(left);
            while (left->parent)
                splay(left);

            left->right = right;
            right->parent = left;
            root = left;
        }

        --nE;
    }

    void clear() {
        clear(root);
        nE = 0;
        root = nullptr;
    }

    void print_tree(Node* root) {
        if (!root)
            return;

        cout << (root->parent ? root->parent->key : -1) << ":" << root->key << " ";
        print_tree(root->left);
        print_tree(root->right);
    }

    void print_tree() {
        cout << "\n---------------------------------SPLAY TREE-----------------------------------\n";
        print_tree(root);
        cout << "\n---------------------------------SPLAY TREE-----------------------------------\n";
    }
};

#endif // SPLAY_TREE
