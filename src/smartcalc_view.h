#ifndef SMARTCALC_VIEW_H_
#define SMARTCALC_VIEW_H_

#include <iostream>
#include <string>

class SmartCalcView {
public:
    void getUserInput(std::string& expression, double& x_value) {
        std::cout << "Введите математическое выражение: ";
        std::getline(std::cin, expression);
        std::cout << "Введите значение переменной x: ";
        std::cin >> x_value;
    }

    void showResult(double result) {
        std::cout << "Результат: " << result << std::endl;
    }
};

#endif  // SMARTCALC_VIEW_H_
