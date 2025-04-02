#ifndef SMARTCALC_CONTROLLER_H
#define SMARTCALC_CONTROLLER_H

#include <string>
#include "smartcalc_model.h"

// Контроллер для управления моделью
namespace s21 {
class SmartCalcController {
public:
    explicit SmartCalcController(SmartCalcModel* model);

    // Метод для вычисления выражения
    double calculateExpression(const std::string& expression, double x_value);

private:
    SmartCalcModel* model_;  // Указатель на модель
};

} // namespace s21

#endif  // SMARTCALC_CONTROLLER_H
