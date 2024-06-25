#ifndef Graph_h
#define Graph_h
#include <vector>
#include "Dynamic Array.h"
template<typename T>
class Tree{
private:
    struct Node {
        Node* left;
        Node* right;
        Node* parent;
        int height;
        T key;
        Node* next;
        Node* prev;

        Node(T el) {key = el; left = NULL; right = NULL; parent = NULL; height = 0; next = NULL; prev = NULL;};
    };
    Node* root;
    Node* last;

    void clear() {
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
                        lastVisited = dim->getLast();
                        dim->deLete(dim->getLength());
                        delete lastVisited;
                    }
                }
            }
            root = NULL;
            last = NULL;
            
        }

public:
    Tree() {root = new Node(NULL);}
    ~Tree() { clear(root); }

    void copy(Node* x) {
        if (x != NULL) {
            insert(x->key);
            copy(x->right);
            copy(x->left);
        }
    }
    
    // было
    void preorderTravelsar(Node* x) { // корень: левая ветвь, правая ветвь
        if (x != NULL) {
            std::cout << x->key << " ";
            if (x->left != NULL) {
                std::cout << "l: " << x->left->key << " ";
            }
            if (x->right != NULL) {
                std::cout << "r: " << x->right->key << " ";
            }
            std::cout << "\n";
            preorderTravelsar(x->right);
            preorderTravelsar(x->left);
        }
    }
    

    // стало
    // корень-лево-право
    void KLP() {
        if (root == NULL) return;
        DynamicArray<Node*>* dim = new DynamicArray<Node*>;
        dim->append(root);
        while (dim->getLength() != 0) {
            Node* node = dim->getLast();
            dim->deLete(dim->getLength());
            std::cout << node->key << " ";
            if (node->right) dim->append(node->right);
            if (node->left) dim->append(node->left);
        }
        std::cout << "\n";
    }

    // лево-корень-право
    void LKP() {
        DynamicArray<Node*>* dim = new DynamicArray<Node*>;
        Node* node = root;
        while (node != NULL || dim->getLength() != 0) {
            while (node != NULL) {
                dim->append(node);
                node = node->left;
            }
            node = dim->getLast();
            dim->deLete(dim->getLength());
            std::cout << node->key << " ";
            node = node->right;
        }
        std::cout << "\n";
    }

    // лево-право-корень
    void LPK() {
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
                    std::cout << peekNode->key << " ";
                    lastVisited = dim->getLast();
                    dim->deLete(dim->getLength());
                }
            }
        }
        std::cout << "\n";
    }

    void firmware(Node* x) { // корень: левая ветвь, правая ветвь

    }
    
    Node* rooT() {
        return root;
    }
    
    Node* search(T k) {
        Node* cur = new Node(k);
        cur = root;
        while (cur != NULL) {
            if (k > cur->key) {
                if (cur->right != NULL) {
                    cur = cur->right;
                } else {

                    return cur;
                }
            } else if (k < cur->key) {
                if (cur->left != NULL) {
                    cur = cur->left;
                } else {
    
                    return cur;
                }
            } else {
                
                return cur;
            }
        }
        
        return cur;
    }
    
    void insert(T val) {
        if (root->key == NULL) {
            root->key = val;
            last = root;
        } else {
            Node* neW = new Node(val);
            Node* cur = root;
            while (cur != NULL) {
                if (neW->key > cur->key) {
                    if (cur->right != NULL) {
                        cur = cur->right;
                    } else {
                        neW->parent = cur;
                        cur->right = neW;
                        last->next = neW;
                        neW->prev = last;
                        last = neW;
                        break;
                    }
                } else if (neW->key < cur->key) {
                    if (cur->left != NULL) {
                        cur = cur->left;
                    } else {
                        neW->parent = cur;
                        cur->left = neW;
                        last->next = neW;
                        neW->prev = last;
                        last = neW;
                        break;
                    }
                }
            }
        }
    }
    
    void deleteElement(T val) {
        Tree* t = this;
        Node* cur = t->search(val);
        if (cur->parent == NULL) {
            if (cur->left == NULL && cur->right == NULL) {
                delete cur;
            } else if (cur->left == NULL || cur->right == NULL) {
                if (cur->left == NULL) {
                    root = cur->right;
                    root->parent = NULL;
                } else {
                    root = cur->left;
                    root->parent = NULL;
                }
            } else {
                Node* next = cur->left;
                cur->key = next->key;
                if (next->parent->left == next) {
                    next->parent->left = next->right;
                    if (next->right != NULL) {
                        next->right->parent = next->parent;
                    } else {
                        next->right = root->right;
                    }
                } else {
                    next->parent->right = next->right;
                    if (next->right != NULL) {
                        next->right->parent = next->parent;
                    } else {
                        next->left = root->left;
                    }
                }
                root = next;
                next->parent = NULL;
            }
        } else {
            Node* par = cur->parent;
            if (cur->prev == NULL) {
                cur->next->prev = NULL;
            } else  if (cur->next == NULL) {
                last = cur->prev;
            } else {
                cur->prev->next = cur->next; // проверить крайние случаи удаление сначала и с конца
            }
            
            if (cur->left == NULL && cur->right == NULL) {
                if (par->left == cur) {
                    par->left = NULL;
                }
                if (par->right == cur) {
                    par->right = NULL;
                }
            } else if (cur->left == NULL || cur->right == NULL) {
                if (cur->left == NULL) {
                    if (par->left == cur) {
                        par->left = cur->right;
                    } else {
                        par->right = cur->right;
                        cur->right->parent = par;
                    }
                } else {
                    if (par->left == cur) {
                        par->left = cur->left;
                    } else {
                        par->right = cur->left;
                        par->left->parent = par;
                    }
                }
            } else {
                Node* next = cur->left;
                cur->key = next->key;
                if (next->parent->left == next) {
                    next->parent->left = next->right;
                    if (next->right != NULL) {
                        next->right->parent = next->parent;
                    }
                } else {
                    next->parent->right = next->right;
                    if (next->right != NULL) {
                        next->right->parent = next->parent;
                    }
                }
            }
        }
    }
    
    int bfactor(Node* p)
    {
        return height(p->right) - height(p->left);
    }
    
    unsigned char height(Node*p) {
        return (p!=NULL)?p->height:0;
    }
    
    void fixheight(Node* p)
    {
        int hl = height(p->left);
        int hr = height(p->right);
        p->height = (hl>hr?hl:hr)+1; // тернарный оператор
    }
    
    Node* rotableLeft(Node* q) {
        Node* p = q->right;
        if (p != NULL) {
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
        if (q != NULL) {
            p->left = q->right;
            q->right = p;
            fixheight(p);
            fixheight(q);
            return q;
        }
        return p;
    }
    
    Node* balance(Node* q) {
        fixheight(q);
        if (bfactor(q) == 3) {
            if (bfactor(q->right) < 0) {
                q->right = rotableRight(q->right);
            }
            return rotableLeft(q);
        }
        if(bfactor(q) == -3) {
            if(bfactor(q->left) > 0) {
                q->left = rotableLeft(q->left);
            }
            return rotableRight(q);
        }
        return q;
    }
    
    
    
    void Balance(Node* x) { // корень: левая ветвь, правая ветвь
        if (x != NULL) {
            Balance(x->right);
            fixheight(x);
            Balance(x->left);
            fixheight(x);
        }
    }
    
    void B(Node* x) {
        if (x != NULL) {
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
    
    void map(T func(T&), Node* x) {
        if (x != NULL) {
            func(x->key);
            map(func, x->right);
            map(func, x->left);
        }
    }
    
    void where(bool func(T&), Tree* nTree, Node* x) {
        if (x != NULL) {
            if (func(x->key)) {
                nTree->insert(x->key);
            }
            where(func, nTree, x->right);
            where(func, nTree, x->left);
        }
    }
    
    Tree<T>* budding(T val) {
        Node*q = search(val);
        Tree<T>* tr = new Tree();
        tr->copy(q);
        return tr;
    }
    
    void copyStr(Node* x, std::vector<T> q) { // корень: левая ветвь, правая ветвь
        if (x != NULL) {
            q.push_back(x->key);
            copyStr(x->right, q);
            copyStr(x->left, q);
        }
    }
    
    std::vector<T> copyAsString() {
        std::vector<T> q;
        copyStr(root, q);
        return q;
    }
    // прошивка
};

#endif /* Graph_h */
