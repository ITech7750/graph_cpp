#ifndef Graph_h
#define Graph_h
#include <vector>
#include "Dynamic Array.h"

template<typename T>
class SimpleTreePrinter : public TreePrinter<T> {
public:
    void printNode(const T& key) const override {
        std::cout << key << " ";
    }
};

template<typename T>
class Tree {
private:
    struct Node {
        Node* left;
        Node* right;
        Node* parent;
        int height;
        T key;
        Node* next;
        Node* prev;

        Node(T el) : key(el), left(nullptr), right(nullptr), parent(nullptr), height(0), next(nullptr), prev(nullptr) {}
    };
    Node* root;
    Node* last;

    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void copy(Node* x) {
        if (x != nullptr) {
            insert(x->key);
            copy(x->left);
            copy(x->right);
        }
    }

    void copyStr(Node* x, std::vector<T>& q) const {
        if (x != nullptr) {
            q.push_back(x->key);
            copyStr(x->left, q);
            copyStr(x->right, q);
        }
    }

public:
    class TreePrinter {
    public:
        virtual void printNode(const T& key) const = 0;
    };
    Tree() : root(nullptr), last(nullptr) {}
    ~Tree() { clear(root); }

    Node* getRoot() const { return root; }

    void insert(T val) {
        if (root == nullptr) {
            root = new Node(val);
            last = root;
        } else {
            Node* newNode = new Node(val);
            Node* cur = root;
            while (cur != nullptr) {
                if (newNode->key > cur->key) {
                    if (cur->right != nullptr) {
                        cur = cur->right;
                    } else {
                        newNode->parent = cur;
                        cur->right = newNode;
                        last->next = newNode;
                        newNode->prev = last;
                        last = newNode;
                        break;
                    }
                } else if (newNode->key < cur->key) {
                    if (cur->left != nullptr) {
                        cur = cur->left;
                    } else {
                        newNode->parent = cur;
                        cur->left = newNode;
                        last->next = newNode;
                        newNode->prev = last;
                        last = newNode;
                        break;
                    }
                }
            }
        }
    }

    void deleteElement(T val) {
        Node* node = search(val);
        if (node == nullptr) return;

        if (node->left == nullptr && node->right == nullptr) {
            if (node->parent == nullptr) {
                root = nullptr;
            } else {
                if (node->parent->left == node) {
                    node->parent->left = nullptr;
                } else {
                    node->parent->right = nullptr;
                }
            }
            delete node;
        } else if (node->left == nullptr || node->right == nullptr) {
            Node* child = (node->left != nullptr) ? node->left : node->right;
            if (node->parent == nullptr) {
                root = child;
            } else {
                if (node->parent->left == node) {
                    node->parent->left = child;
                } else {
                    node->parent->right = child;
                }
                child->parent = node->parent;
            }
            delete node;
        } else {
            Node* successor = node->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            node->key = successor->key;
            if (successor->parent->left == successor) {
                successor->parent->left = successor->right;
            } else {
                successor->parent->right = successor->right;
            }
            if (successor->right != nullptr) {
                successor->right->parent = successor->parent;
            }
            delete successor;
        }
    }

    Node* search(T key) const {
        Node* cur = root;
        while (cur != nullptr) {
            if (key > cur->key) {
                cur = cur->right;
            } else if (key < cur->key) {
                cur = cur->left;
            } else {
                return cur;
            }
        }
        return nullptr;
    }

    void preorderTraversal(Node* x, const TreePrinter<T>& printer) const {
        if (x != nullptr) {
            printer.printNode(x->key);
            preorderTraversal(x->left, printer);
            preorderTraversal(x->right, printer);
        }
    }

    // Pre-order traversal (root-left-right)
    void KLP(std::vector<T>& result) {
        if (root == NULL) return;
        DynamicArray<Node*>* dim = new DynamicArray<Node*>;
        dim->append(root);
        while (dim->getLength() != 0) {
            Node* node = dim->getLast();
            dim->deLete(dim->getLength());
            result.push_back(node->key);
            if (node->right) dim->append(node->right);
            if (node->left) dim->append(node->left);
        }
    }

    // In-order traversal (left-root-right)
    void LKP(std::vector<T>& result) {
        DynamicArray<Node*>* dim = new DynamicArray<Node*>;
        Node* node = root;
        while (node != NULL || dim->getLength() != 0) {
            while (node != NULL) {
                dim->append(node);
                node = node->left;
            }
            node = dim->getLast();
            dim->deLete(dim->getLength());
            result.push_back(node->key);
            node = node->right;
        }
    }

    // Post-order traversal (left-right-root)
    void LPK(std::vector<T>& result) {
        if (root == NULL) return;
        DynamicArray<Node*>* dim = new DynamicArray<Node*>;
        Node* lastVisited = NULL;
        Node* node = root;
        
        while (dim->getLength() != 0 || node != NULL) {
            if (node != NULL) {
                dim->append(node);
                node = node->left;
            } else {
                Node* peekNode = dim->getLast();
                if (peekNode->right != NULL && lastVisited != peekNode->right) {
                    node = peekNode->right;
                } else {
                    result.push_back(peekNode->key);
                    lastVisited = dim->getLast();
                    dim->deLete(dim->getLength());
                }
            }
        }
    }


    void B(Node* x) {
        if (x != nullptr) {
            B(x->right);
            if (root == x) {
                x = balance(x);
                root = x;
            } else {
                x = balance(x);
            }
            B(x->left);
        }
    }

    void where(bool (*func)(T&), Tree* nTree, Node* x) {
        if (x != nullptr) {
            if (func(x->key)) {
                nTree->insert(x->key);
            }
            where(func, nTree, x->left);
            where(func, nTree, x->right);
        }
    }

    Tree<T>* budding(T val) {
        Node* q = search(val);
        Tree<T>* tr = new Tree();
        tr->copy(q);
        return tr;
    }

    void copyStr(Node* x, std::vector<T>& q) {
        copyStr(x, q);
    }

private:
    Node* balance(Node* q) {
        fixheight(q);
        if (bfactor(q) == 2) {
            if (bfactor(q->right) < 0) {
                q->right = rotableRight(q->right);
            }
            return rotableLeft(q);
        }
        if (bfactor(q) == -2) {
            if (bfactor(q->left) > 0) {
                q->left = rotableLeft(q->left);
            }
            return rotableRight(q);
        }
        return q;
    }

    unsigned char height(Node* p) {
        return (p != nullptr) ? p->height : 0;
    }

    void fixheight(Node* p) {
        int hl = height(p->left);
        int hr = height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    int bfactor(Node* p) {
        return height(p->right) - height(p->left);
    }

    Node* rotableLeft(Node* q) {
        Node* p = q->right;
        if (p != nullptr) {
            q->right = p->left;
            p->left = q;
            fixheight(q);
            fixheight(p);
            return p;
        }
        return q;
    }

    Node* rotableRight(Node* p) {
        Node* q = p->left;
        if (q != nullptr) {
            p->left = q->right;
            q->right = p;
            fixheight(p);
            fixheight(q);
            return q;
        }
        return p;
    }
};

#endif /* Graph_h */
