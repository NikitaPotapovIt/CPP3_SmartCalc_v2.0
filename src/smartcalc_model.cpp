#include "smartcalc_model.h"
#include <stdexcept>
#include <stack>
#include <cmath>

namespace s21 {

// Основная функция парсинга выражения
double SmartCalcModel::parse(const std::string& expression, double x_value) {
    if (expression.empty()) {
        throw std::invalid_argument("Empty expression.");
    }

    std::shared_ptr<Node> calc = nullptr;
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
                pushBack(calc, 0, Priority::UNARY, Type::SQRT);
                i += 3;
            } else if (expression.substr(i, 3) == "sin") {
                pushBack(calc, 0, Priority::UNARY, Type::SIN);
                i += 2;
            } else if (expression.substr(i, 3) == "cos") {
                pushBack(calc, 0, Priority::UNARY, Type::COS);
                i += 2;
            } else if (expression.substr(i, 3) == "tan") {
                pushBack(calc, 0, Priority::UNARY, Type::TAN);
                i += 2;
            } else if (expression.substr(i, 3) == "cot") {
                pushBack(calc, 0, Priority::UNARY, Type::COTAN);
                i += 2;
            } else if (expression.substr(i, 3) == "log") {
                pushBack(calc, 0, Priority::UNARY, Type::LOG);
                i += 2;
            } else if (expression.substr(i, 2) == "ln") {
                pushBack(calc, 0, Priority::UNARY, Type::LN);
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
        calc = delimiter(calc);
        return calcExpression(calc, x_value);
    }

    return 0;
}

// Преобразование в обратную польскую нотацию
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
            else throw std::invalid_argument("Mismatched parentheses in expression.");
        } else if (end->type == Type::SIN || end->type == Type::COS || end->type == Type::TAN ||
                   end->type == Type::ASIN || end->type == Type::ACOS || end->type == Type::ATAN ||
                   end->type == Type::SQRT || end->type == Type::LOG || end->type == Type::LN) {
            // Унарные операторы сразу помещаются в стек
            stack.push(std::make_shared<Node>(*end));
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

// Преобразование в RPN
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
            else throw std::invalid_argument("Mismatched parentheses in expression.");
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

double SmartCalcModel::calcExpression(std::shared_ptr<Node> end, double x_value) {
    std::stack<double> values;

    while (end) {
        if (end->type == Type::NUMBER) {
            values.push(end->value);
        } else if (end->type == Type::X) {
            values.push(x_value);
        } else {
            double b = values.top(); values.pop();
            double a = (values.empty() ? 0 : values.top());
            if (!values.empty()) values.pop();

            switch (end->type) {
                case Type::PLUS: values.push(a + b); break;
                case Type::MINUS: values.push(a - b); break;
                case Type::MULT: values.push(a * b); break;
                case Type::DIV: if (b == 0) throw std::invalid_argument("Division by zero."); values.push(a / b); break;
                case Type::POW: values.push(std::pow(a, b)); break;
                case Type::MOD: if (b == 0) throw std::invalid_argument("Modulo by zero."); values.push(std::fmod(a, b)); break;
                case Type::SIN: values.push(std::sin(b)); break;
                case Type::COS: values.push(std::cos(b)); break;
                case Type::TAN: values.push(std::tan(b)); break;
                case Type::COTAN: if (std::tan(b) == 0) throw std::invalid_argument("Cotangent undefined."); values.push(1 / std::tan(b)); break;
                case Type::SQRT: if (b < 0) throw std::invalid_argument("Negative argument for sqrt."); values.push(std::sqrt(b)); break;
                case Type::LOG: if (b <= 0) throw std::invalid_argument("Non-positive argument for log."); values.push(std::log10(b)); break;
                case Type::LN: if (b <= 0) throw std::invalid_argument("Non-positive argument for ln."); values.push(std::log(b)); break;
                default: throw std::invalid_argument("Unknown operator.");
            }
        }
        end = end->next;
    }

    return values.top();
}

// Проверка баланса скобок
bool SmartCalcModel::checkBrackets(const std::string& expression) {
    int balance = 0;
    for (char ch : expression) {
        if (ch == '(') balance++;
        if (ch == ')') balance--;
        if (balance < 0) return false;
    }
    return balance == 0;
}

// Добавление элемента в связный список
void SmartCalcModel::pushBack(std::shared_ptr<Node>& end, double value, Priority priority, Type type) {
    auto newNode = std::make_shared<Node>(value, priority, type);
    if (!newNode) return;

    if (!end) {
        end = newNode;
    } else {
        auto temp = end;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

}  // namespace s21
