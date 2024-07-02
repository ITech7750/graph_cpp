#include <iostream>
#include <vector>
#include "Graph.h"  
#include "tests.h"  
#include "ui.h"

int main(int argc, const char* argv[]) {
    Tree<int>* tree = new Tree<int>;
    std::vector<int> traversalResult;
    Tree<int>* ntree = new Tree<int>;
    SimpleTreePrinter<int> printer;
    int operation = 1;
    int value;

    while (operation) {
        printMenu();
        std::cin >> operation;
        switch (operation) {
            case 1:
                std::cout << "Введите число: ";
                std::cin >> value;
                tree->insert(value);
                break;
            case 2:
                std::cout << "Введите удаляемый элемент: ";
                std::cin >> value;
                tree->deleteElement(value);
                break;
            case 3:
                std::cout << "Дерево сбалансировано\n";
                tree->B(tree->getRoot());
                break;
            case 4:
                std::cout << "Применение функции 'where'\n";
                tree->where(where_func, ntree, tree->getRoot());
                break;
            case 5:
                std::cout << "Создание подграфа\nВведите число: ";
                std::cin >> value;
                ntree = tree->budding(value);
                break;
            case 6:
                std::cout << "Копирование в строку\n";
                traversalResult.clear();
                tree->copyStr(tree->getRoot(), traversalResult);
                std::cout << "Копия дерева: ";
                for (int val : traversalResult) {
                    std::cout << val << " ";
                }
                std::cout << std::endl;
                break;
            case 7:
                std::cout << "Отображение дерева\n";
                tree->preorderTraversal(tree->getRoot(), printer);
                std::cout << std::endl;
                break;
            case 8:
                std::cout << "Запуск тестов...\n";
                //runTests();
                break;
            case 0:
                std::cout << "Выход из программы\n";
                break;
            default:
                std::cout << "Неверный выбор\n";
                break;
        }
    }

    delete tree; // Освобождаем память, выделенную для дерева
    delete ntree; // Освобождаем память, выделенную для второго дерева

    return 0;
}
