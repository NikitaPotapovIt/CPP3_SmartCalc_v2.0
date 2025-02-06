#include "smartcalc_model.h"
#include <cmath>
#include <stdexcept>

namespace s21 {

double SmartCalcModel::parse(const std::string& expression, double x_value) {
    std::shared_ptr<Node> calc = nullptr;
    double result = 0;
    std::string tmp_str;

    for (size_t i = 0; i < expression.length(); ++i) {
        if (isdigit(expression[i]) || expression[i] == '.') {
            tmp_str += expression[i];
        } else {
            if (!tmp_str.empty()) {
                pushBack(calc, std::stod(tmp_str), Priority::SHORT, Type::NUMBER);
                tmp_str.clear();
            }

            if (expression[i] == 'x') {
                pushBack(calc, x_value, Priority::SHORT, Type::X);
            } else if (expression[i] == '+') {
                pushBack(calc, 0, Priority::SHORT, Type::PLUS);
            } else if (expression[i] == '-') {
                pushBack(calc, 0, Priority::SHORT, Type::MINUS);
            } else if (expression[i] == '*') {
                pushBack(calc, 0, Priority::MIDDLE, Type::MULT);
            } else if (expression[i] == '/') {
                pushBack(calc, 0, Priority::MIDDLE, Type::DIV);
            } else if (expression[i] == '^') {
                pushBack(calc, 0, Priority::HIGH, Type::POW);
            } else if (expression.substr(i, 3) == "mod") {
                pushBack(calc, 0, Priority::MIDDLE, Type::MOD);
                i += 2;
            } else if (expression.substr(i, 4) == "sqrt") {
                pushBack(calc, 0, Priority::HIGH, Type::SQRT);
                i += 3;
            } else if (expression.substr(i, 3) == "sin") {
                pushBack(calc, 0, Priority::HIGH, Type::SIN);
                i += 2;
            } else if (expression.substr(i, 3) == "cos") {
                pushBack(calc, 0, Priority::HIGH, Type::COS);
                i += 2;
            } else if (expression.substr(i, 3) == "log") {
                pushBack(calc, 0, Priority::HIGH, Type::LOG);
                i += 2;
            } else if (expression.substr(i, 2) == "ln") {
                pushBack(calc, 0, Priority::HIGH, Type::LN);
                i += 1;
            } else if (expression[i] == '(') {
                pushBack(calc, 0, Priority::ROUNDBRACKET, Type::ROUNDBRACKET_L);
            } else if (expression[i] == ')') {
                pushBack(calc, 0, Priority::ROUNDBRACKET, Type::ROUNDBRACKET_R);
            }
        }
    }

    if (!tmp_str.empty()) {
        pushBack(calc, std::stod(tmp_str), Priority::SHORT, Type::NUMBER);
    }

    if (!checkBrackets(expression)) {
        throw std::invalid_argument("Mismatched parentheses in expression.");
    }

    if (calc) {
        calc = RPN(calc);
        if (calc) calc = delimiter(calc);
        if (calc) result = calcExpression(calc);
    }

    return result;
}

std::shared_ptr<Node> SmartCalcModel::delimiter(std::shared_ptr<Node> end) {
    std::shared_ptr<Node> res = nullptr;
    std::stack<std::shared_ptr<Node>> stack;

    while (end) {
        if (end->type == Type::NUMBER || end->type == Type::X) {
            pushBack(res, end->value, Priority::SHORT, end->type);
        } else if (end->type == Type::ROUNDBRACKET_R) {
            while (!stack.empty() && stack.top()->type != Type::ROUNDBRACKET_L) {
                pushBack(res, 0, stack.top()->priority, stack.top()->type);
                stack.pop();
            }
            if (!stack.empty()) stack.pop(); // Удаляем открывающую скобку
        } else {
            while (!stack.empty() && stack.top()->priority >= end->priority) {
                pushBack(res, 0, stack.top()->priority, stack.top()->type);
                stack.pop();
            }
            stack.push(std::make_shared<Node>(*end));
        }
        end = end->next;
    }

    while (!stack.empty()) {
        pushBack(res, 0, stack.top()->priority, stack.top()->type);
        stack.pop();
    }

    return res;
}

std::shared_ptr<Node> SmartCalcModel::RPN(std::shared_ptr<Node> end) {
    std::stack<std::shared_ptr<Node>> opStack;
    std::shared_ptr<Node> output = nullptr;

    while (end) {
        if (end->type == Type::NUMBER || end->type == Type::X) {
            pushBack(output, end->value, Priority::SHORT, end->type);
        } else if (end->type == Type::ROUNDBRACKET_L) {
            opStack.push(std::make_shared<Node>(*end));
        } else if (end->type == Type::ROUNDBRACKET_R) {
            while (!opStack.empty() && opStack.top()->type != Type::ROUNDBRACKET_L) {
                pushBack(output, 0, opStack.top()->priority, opStack.top()->type);
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop(); // Удаляем открывающую скобку
        } else {
            while (!opStack.empty() && opStack.top()->priority >= end->priority) {
                pushBack(output, 0, opStack.top()->priority, opStack.top()->type);
                opStack.pop();
            }
            opStack.push(std::make_shared<Node>(*end));
        }
        end = end->next;
    }

    while (!opStack.empty()) {
        pushBack(output, 0, opStack.top()->priority, opStack.top()->type);
        opStack.pop();
    }

    return output;
}

double SmartCalcModel::calcExpression(std::shared_ptr<Node> end) {
    std::stack<double> values;

    while (end) {
        if (end->type == Type::NUMBER || end->type == Type::X) {
            values.push(end->value);
        } else {
            if (values.size() < 2 && end->type != Type::SQRT && end->type != Type::SIN && end->type != Type::COS && end->type != Type::LOG && end->type != Type::LN) {
                throw std::invalid_argument("Not enough operands for operation.");
            }

            double b = values.top();
            values.pop();

            double a = (end->type == Type::SQRT || end->type == Type::SIN || end->type == Type::COS || end->type == Type::LOG || end->type == Type::LN) ? 0 : values.top();
            if (end->type != Type::SQRT && end->type != Type::SIN && end->type != Type::COS && end->type != Type::LOG && end->type != Type::LN) {
                values.pop();
            }

            switch (end->type) {
                case Type::PLUS: values.push(a + b); break;
                case Type::MINUS: values.push(a - b); break;
                case Type::MULT: values.push(a * b); break;
                case Type::DIV: values.push(b != 0 ? a / b : NAN); break;
                case Type::POW: values.push(std::pow(a, b)); break;
                case Type::MOD: values.push(b != 0 ? std::fmod(a, b) : NAN); break;
                case Type::SIN: values.push(std::sin(b)); break;
                case Type::COS: values.push(std::cos(b)); break;
                case Type::SQRT: values.push(b >= 0 ? std::sqrt(b) : NAN); break;
                case Type::LOG: values.push(b > 0 ? std::log10(b) : NAN); break;
                case Type::LN: values.push(b > 0 ? std::log(b) : NAN); break;
                default: throw std::invalid_argument("Unknown operator.");
            }
        }
        end = end->next;
    }

    return values.empty() ? NAN : values.top();
}

bool SmartCalcModel::checkBrackets(const std::string& expression) {
    int balance = 0;

    for (char ch : expression) {
        if (ch == '(') balance++;
        if (ch == ')') balance--;

        if (balance < 0) return false;
    }

    return balance == 0;
}

void SmartCalcModel::pushBack(std::shared_ptr<Node>& end, double value, Priority priority, Type type) {
    auto newNode = std::make_shared<Node>(value, priority, type);
    if (!newNode) return;

    newNode->next = end;
    end = newNode;
}

}  // namespace s21
