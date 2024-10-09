#include "smartcalc_model.h"
#include "smartcalc_controller.h"
#include "smartcalc_view.h"

int main() {
    SmartCalcModel model;  // Модель
    SmartCalcController controller(&model);  // Контроллер
    SmartCalcView view;  // Представление

    std::string expression;
    double x_value;

    view.getUserInput(expression, x_value);

    double result = controller.calculateExpression(expression, x_value);

    view.showResult(result);

    return 0;
}
