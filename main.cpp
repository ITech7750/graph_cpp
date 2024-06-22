#include <iostream>
#include "Graph.h"  
#include "tests.h"  
#include "ui.h"

int main(int argc, const char * argv[]) {
    Tree<int>* tree = new Tree<int>;
    std::vector<int> tr;
    Tree<int>* ntree = new Tree<int>;
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
                tree->B(tree->rooT());
                break;
            case 4:
                std::cout << "Применение функции 'where'\n";
                tree->where(where_func, ntree, tree->rooT());
                break;
            case 5:
                std::cout << "Создание подграфа\nВведите число: ";
                std::cin >> value;
                tree->budding(value);
                break;
            case 6:
                std::cout << "Копирование в строку\n";
                tree->copyStr(tree->rooT(), tr);
                break;
            case 7:
                std::cout << "Отображение дерева\n";
                tree->preorderTravelsar(tree->rooT());
                break;
            case 8:
                std::cout << "Запуск тестов...\n";
                runTests();
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
