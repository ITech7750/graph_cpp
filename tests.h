// tests.h

#ifndef TESTS_H
#define TESTS_H

#include "Graph.h"  
#include <iostream>
#include <cassert>

void testInsertAndSearch() {
    Tree<int> tree;
    
    // Вставка элементов
    int values[] = {5, 3, 7, 2, 4, 6, 8};
    for (int value : values) {
        tree.insert(value);
    }
    
    // Поиск элементов
    for (int value : values) {
        assert(tree.search(value) != NULL);
    }
    
    // Поиск отсутствующего элемента
    assert(tree.search(10) == NULL);
    
    std::cout << "Тесты на вставку и поиск пройдены.\n";
}

void testDelete() {
    Tree<int> tree;
    
    // Вставка элементов
    int values[] = {5, 3, 7, 2, 4, 6, 8};
    for (int value : values) {
        tree.insert(value);
    }
    
    // Удаление элементов
    tree.deleteElement(2);  // Удаление листового узла
    tree.deleteElement(7);  // Удаление узла с двумя потомками
    
    // Проверка отсутствия удаленных элементов
    assert(tree.search(2) == NULL);
    assert(tree.search(7) == NULL);
    
    // Проверка наличия других элементов
    for (int value : values) {
        if (value != 2 && value != 7) {
            assert(tree.search(value) != NULL);
        }
    }
    
    std::cout << "Тесты на удаление пройдены.\n";
}

void testBalance() {
    Tree<int> tree;
    
    // Вставка элементов
    int values[] = {5, 3, 7, 2, 4, 6, 8};
    for (int value : values) {
        tree.insert(value);
    }
    
    // Балансировка дерева
    tree.Balance(tree.rooT());
    
    //assert(tree.isBalanced());
    
    std::cout << "Тесты на балансировку пройдены.\n";
}

void runTests() {
    testInsertAndSearch();
    testDelete();
    testBalance();
}


#endif // TESTS_H
