// множество 
#ifndef sEt_h
#define sEt_h
#include "binary heap.h"
template<typename T>
class set: public binHeap<T> {
public:
    set(): binHeap<T>(*new binHeap<T>) {};
    set<T>* append(T el) {
        if (this->search(el) == -1){
            this->insert(el);
            this->sort();
        }
        return this;
    }
    
    set<T>* map(T func(T el)) {
        return map(func);
    }
    T reduce(T func(T el1, T el2), T el) {
        return reduce(func, el);
    }
    set<T>* where(T func(T el)) {
        return where(func);
    }
    set<T>* unification(set<T> s2) {
        for (size_t i = 0; i < s2.size(); i++) {
            this->append(s2.get(i));
        }
        return this;
    }
    set<T>* intersection(set<T> s1, set<T> s2) {
        for (size_t i = 0; i < s1.size(); i++) {
            for (size_t j = 0; j < s2.size(); j++) {
                if (s1.get(i) == s2.get(j)) {
                    this->append(s1.get(i));
                    break;
                } else if (s1.get(i) < s2.get(j)) {
                    break;
                }
            }
        }
        return this;
    }
    set<T>* subtraction(set<T> s2) { 
        for (size_t i = 0; i < this->size(); i++) {
            for (size_t j = 0; j < s2.size(); j++) {
                if (this->get(i) == s2.get(j)) {
                    this->deLete(i);
                    i--;
                }
            }
        }
        return this;
    }
    
    int inclusion(set<T> s) {
        int count = 0;
        for (size_t i = 0; i < this->size(); i++) {
            for (size_t j = 0; j < s.size(); j++) {
                if (this->get(i) == s.get(j)) {
                    count+=1;
                    break;
                } else if (this->get(i) < s.get(j)) {
                    break;
                }
            }
        }
        if (count == s.size() && s.size() == this->size()) {
            return 2;
        } else if (count == s.size) {
            return 1;
        } else {
            return 0;
        }
    }
    
};

#endif /* sEt_h */
