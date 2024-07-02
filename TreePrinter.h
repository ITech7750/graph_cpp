#ifndef TREE_PRINTER_H
#define TREE_PRINTER_H

template <typename T>
class TreePrinter
{
public:
    virtual void printNode(const T& key) const = 0;
    virtual ~TreePrinter() = default;
};

#endif // TREE_PRINTER_H
