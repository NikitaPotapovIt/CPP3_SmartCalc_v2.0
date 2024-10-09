#ifndef SMARTCALC_CONTROLLER_H_
#define SMARTCALC_CONTROLLER_H_

#include "smartcalc_model.h"

class SmartCalcController {
public:
    SmartCalcController(SmartCalcModel* model) : model_(model) {}

    double calculateExpression(const std::string& expression, double x_value) {
        return model_->parse(expression, x_value);
    }

private:
    SmartCalcModel* model_;
};

#endif  // SMARTCALC_CONTROLLER_H_
