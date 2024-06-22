#ifndef binary_heap_h
#define binary_heap_h
#include "Dynamic Array.h"

template<typename T>
class binHeap {
private:
    DynamicArray<T>* q;
public:
    binHeap(): q(new DynamicArray<T>) {};
    binHeap(DynamicArray<T>* p): q(p){};
    
    binHeap<T>* insert(T val) {
        q->append(val);
        size_t i = q->getLength();
        while (val < (*q)[i/2+i%2+1]) {
            q[i] = q[i/2+i%2+1];
            (*q)[i/2+i%2+1] = val;
            i = i/2+i%2+1;
        }
        return this;
    }
    binHeap<T>* sort() {
        q->sort();
        return this;
    }
    void show() {
        q->show();
    }
    T& get(size_t index) {
        return q->get(index);
    }
    
    size_t size() {
        return q->cnt();
    }
    
    int search(T val) {
        for (size_t i = 0; i < q->getLength(); i++) {
            if (q->get(i) == val) {
                return i;
            }
        }
        return -1;
    }
    
    binHeap<T> deLete(size_t ind) {
        q->deLete(ind);
        return *this;
    }
    
    binHeap<T> budding(T val) {
        T* ind = search(val);
        DynamicArray<T> neW = DynamicArray<T>(ind);
        return neW;
    }
    
    binHeap<T> merge(binHeap<T>* a, binHeap<T>* b){
        binHeap<T>* neW = a;
        for (size_t i = 0; i < b->q->size; i++) {
            insert(b[i]);
        }
        return neW;
    }
    
    binHeap<T> map(T func(T el)) {
        q = q->map(func);
        return q;
    }
    T reduce(T func(T el1, T el2), T el) {
        return q->reduce(func, el);
    }
    binHeap<T> where(bool func(T el)) {
        return q->where(func);
    }
    
    T& operator[](size_t index) {
        return q[index];
    }
};

#endif /* binary_heap_h */
