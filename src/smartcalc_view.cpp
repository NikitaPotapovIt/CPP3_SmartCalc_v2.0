#include "smartcalc_view.h"

#include <iostream>

// Метод для получения пользовательского ввода
void SmartCalcView::getUserInput(std::string& expression, double& x_value) {
    std::cout << "Введите математическое выражение: ";
    std::getline(std::cin, expression);
    std::cout << "Введите значение переменной x: ";
    std::cin >> x_value;
}

// Метод для вывода результата
void SmartCalcView::showResult(double result) {
    std::cout << "Результат: " << result << std::endl;
}
