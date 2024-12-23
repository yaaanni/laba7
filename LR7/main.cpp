#include <iostream>
#include <limits>
#include "utils.h"

int menu() {
    std::cout << "Выберите интересующий пункт меню: \n";
    std::cout << "1. Кто выполнил задание\n";
    std::cout << "2. Результат программы\n";
    std::cout << "3. Суть задания\n";
    std::cout << "4. Выход из программы\n";
    std::cout << "5. Вариант\n";
    std::cout << ">>>\n";
    int n;
    while (!(std::cin >> n) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите значение повторно: ";
    }
    return n;
}

void program(int choice) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
        case 1: {
            Task Task1;
            Task1.task1();
            break;
        }
        case 2: {
            Task Task2;
            Task2.task2();
            break;
        }
        case 3: {
            Task Task3;
            Task3.task3();
            break;
        }
        case 4: {
            Task Task4;
            Task4.task4();
            break;
        }
        case 5: {
            Task Task5;
            Task5.task5();
            break;
        }
        default:
            std::cout << "Неверный выбор!" << std::endl;
            break;
    }
}

int main() {
    while (true) {
        int number = menu();
        if (number == 1) {
            std::cout << "Попова Яна\n";
        } else if (number == 2) {
            int choice;
            std::cout << "Выберите задание:\n";
            std::cout << "1. Перевод числа из двоичного в обратный код\n";
            std::cout << "2. Из естественной формы сделать сложение в доп коде\n";
            std::cout << "3. Перевод в системах счисления\n";
            std::cout << "4. Простое число\n";
            std::cout << "5. Бочки\n";
            std::cin >> choice;

            program(choice);
        } else if (number == 3) {
            std::cout << "Сделать 5 заданий\n";
        } else if (number == 4) {
            std::cout << "Выход выполнен успешно!\n";
            return 0;
        } else if (number == 5) {
            std::cout << "Вариант: 6\n";
        } else {
            std::cout << "Неверно ввели значение, попробуйте еще раз: \n";
            continue;
        }
        std::cout << ">>>\n";
    }
}
