#ifndef SIMPLE_TREE_PRINTER_H
#define SIMPLE_TREE_PRINTER_H

#include <iostream>
#include "TreePrinter.h"

template <typename T>
class SimpleTreePrinter : public TreePrinter<T>
{
public:
    void printNode(const T& key) const override {
        std::cout << key << " ";
    }
};

#endif // SIMPLE_TREE_PRINTER_H
