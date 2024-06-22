#ifndef UI_H
#define UI_H
#include <iostream>

int map_func(int& e) {
    e *= 2;
    return e;
}

bool where_func(int& e) {
    return e % 2 == 0;
}

void printMenu() {
    std::cout << "Выберите операцию:\n";
    std::cout << "1. Вставить элемент\n";
    std::cout << "2. Удалить элемент\n";
    std::cout << "3. Сбалансировать дерево\n";
    std::cout << "4. Применить функцию 'where'\n";
    std::cout << "5. Создать подграф\n";
    std::cout << "6. Скопировать в строку\n";
    std::cout << "7. Показать дерево\n";
    std::cout << "8. Запустить тесты\n";
    std::cout << "0. Выход\n";
}



#endif 