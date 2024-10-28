#ifndef SMARTCALC_VIEW_H_
#define SMARTCALC_VIEW_H_

#include <string>

// Класс представления для работы с пользовательским интерфейсом
class SmartCalcView {
public:
    // Метод для получения пользовательского ввода
    void getUserInput(std::string& expression, double& x_value);

    // Метод для отображения результата
    void showResult(double result);
};

#endif  // SMARTCALC_VIEW_H_
