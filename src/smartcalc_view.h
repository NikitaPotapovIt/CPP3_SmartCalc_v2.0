#ifndef SMARTCALC_VIEW_H
#define SMARTCALC_VIEW_H

#include <string>

// Класс представления для работы с пользовательским интерфейсом
namespace s21 {
class SmartCalcView {
public:
    // Метод для получения пользовательского ввода
    void getUserInput(std::string& expression, double& x_value);

    // Метод для отображения результата
    void showResult(double result);
};

} // namespace s21

#endif  // SMARTCALC_VIEW_H
