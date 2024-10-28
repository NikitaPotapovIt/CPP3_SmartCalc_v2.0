#include "smartcalc_controller.h"

// Конструктор контроллера принимает указатель на модель
SmartCalcController::SmartCalcController(SmartCalcModel* model) : model_(model) {}

// Метод контроллера для вычисления выражения
double SmartCalcController::calculateExpression(const std::string& expression, double x_value) {
    return model_->parse(expression, x_value);
}
