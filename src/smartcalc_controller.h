#ifndef SMARTCALC_CONTROLLER_H_
#define SMARTCALC_CONTROLLER_H_

#include <string>
#include "smartcalc_model.h"

// Контроллер для управления моделью
class SmartCalcController {
public:
    explicit SmartCalcController(SmartCalcModel* model);

    // Метод для вычисления выражения
    double calculateExpression(const std::string& expression, double x_value);

private:
    SmartCalcModel* model_;  // Указатель на модель
};

#endif  // SMARTCALC_CONTROLLER_H_
