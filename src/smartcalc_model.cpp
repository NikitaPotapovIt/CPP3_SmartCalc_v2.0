#include "smartcalc_model.h"
#include <stdexcept>
#include <stack>
#include <cmath>

namespace s21 {

bool SmartCalcModel::isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == 'm'; // 'm' для "mod"
}

// Основная функция парсинга выражения
double SmartCalcModel::parse(const std::string& expression, double x_value) {
    if (expression.empty()) {
        throw std::invalid_argument("Empty expression.");
    }

    for (char ch : expression) {
        if (!isdigit(ch) && ch != '.' && ch != 'x' && ch != '(' && ch != ')' &&
            !isOperator(ch) && expression.find("sin") == std::string::npos &&
            expression.find("cos") == std::string::npos && expression.find("tan") == std::string::npos &&
            expression.find("mod") == std::string::npos && expression.find("sqrt") == std::string::npos &&
            expression.find("log") == std::string::npos && expression.find("ln") == std::string::npos) {
            throw std::invalid_argument("Invalid character in expression.");
        }
    }

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
                if (i == 0 || expression[i - 1] == '(' || isOperator(expression[i - 1])) {
                    pushBack(calc, 0, Priority::UNARY, Type::UNARY_MINUS);
                } else {
                    pushBack(calc, 0, Priority::SHORT, Type::MINUS);
                }
            } else if (expression[i] == '*') {
                pushBack(calc, 0, Priority::MIDDLE, Type::MULT);
            } else if (expression[i] == '/') {
                pushBack(calc, 0, Priority::MIDDLE, Type::DIV);
            } else if (expression[i] == '^') {
                pushBack(calc, 0, Priority::HIGH, Type::POW);
            } else if (expression.substr(i, 3) == "mod") {
                pushBack(calc, 0, Priority::MIDDLE, Type::MOD);
                i += 2;
            } else if (expression.substr(i, 3) == "sin") {
                pushBack(calc, 0, Priority::UNARY, Type::SIN);
                i += 2;
            } else if (expression.substr(i, 3) == "cos") {
                pushBack(calc, 0, Priority::UNARY, Type::COS);
                i += 2;
            } else if (expression.substr(i, 3) == "tan") {
                pushBack(calc, 0, Priority::UNARY, Type::TAN);
                i += 2;
            } else if (expression.substr(i, 4) == "asin") {
                pushBack(calc, 0, Priority::UNARY, Type::ASIN);
                i += 3;
            } else if (expression.substr(i, 4) == "acos") {
                pushBack(calc, 0, Priority::UNARY, Type::ACOS);
                i += 3;
            } else if (expression.substr(i, 4) == "atan") {
                pushBack(calc, 0, Priority::UNARY, Type::ATAN);
                i += 3;
            } else if (expression.substr(i, 4) == "sqrt") {
                pushBack(calc, 0, Priority::UNARY, Type::SQRT);
                i += 3;
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
        tmp_str.clear();
    }    
    
    if (!checkBrackets(expression)) {
        throw std::invalid_argument("Mismatched parentheses in expression.");
    }

    if (calc) {
        calc = RPN(calc);
        if (!calc) throw std::invalid_argument("Invalid RPN transformation.");
        calc = delimiter(calc);
        if (!calc) throw std::invalid_argument("Invalid delimiter transformation.");
        result = calcExpression(calc);
    }
    if (std::isnan(result) || std::isinf(result)) {
        throw std::invalid_argument("Invalid expression result.");
    }
    return result;
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
    while (!opStack.empty()) {
        if (!end) continue;
        
        if (opStack.top()->priority > end->priority || 
            (opStack.top()->priority == end->priority && end->type != Type::POW)) {
        } else {
            break;
        }
    }
    

    while (end) {
        switch (end->type) {
            case Type::NUMBER: {
                pushBack(output, end->value, Priority::SHORT, end->type);
                break;
            }
            case Type::ROUNDBRACKET_L: {
                opStack.push(std::make_shared<Node>(*end));
                break;
            }
            case Type::ROUNDBRACKET_R: {
                while (!opStack.empty() && opStack.top()->type != Type::ROUNDBRACKET_L) {
                    pushBack(output, 0, opStack.top()->priority, opStack.top()->type);
                    opStack.pop();
                }
                if (!opStack.empty()) opStack.pop(); // Удаляем открывающую скобку
                else throw std::invalid_argument("Mismatched parentheses in expression.");
                break;
            }
            default: { // Для остальных операторов
                while (!opStack.empty() && opStack.top()->priority >= end->priority) {
                    pushBack(output, 0, opStack.top()->priority, opStack.top()->type);
                    opStack.pop();
                }
                opStack.push(std::make_shared<Node>(*end));
                break;
            }
        }
        end = end->next;
    }
    return output;
}

double SmartCalcModel::calcExpression(std::shared_ptr<Node> rpn) {
    std::stack<double> stack;
    while (rpn) {
        switch (rpn->type) {
            case Type::NUMBER:
            case Type::X:
                stack.push(rpn->value);
                break;

            case Type::PLUS: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double b = stack.top(); stack.pop();
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                stack.push(a + b);
                break;
            }

            case Type::MINUS: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double b = stack.top(); stack.pop();
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                stack.push(a - b);
                break;
            }

            case Type::MULT: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double b = stack.top(); stack.pop();
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                stack.push(a * b);
                break;
            }

            case Type::DIV: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double b = stack.top(); stack.pop();
                if (b == 0) throw std::invalid_argument("Division by zero.");
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                stack.push(a / b);
                break;
            }

            case Type::POW: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double b = stack.top(); stack.pop();
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                stack.push(std::pow(a, b));
                break;
            }

            case Type::MOD: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double b = stack.top(); stack.pop();
                if (b == 0) throw std::invalid_argument("Modulo by zero.");
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                stack.push(std::fmod(a, b));
                break;
            }

            case Type::SIN: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                stack.push(std::sin(a));
                break;
            }

            case Type::COS: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                stack.push(std::cos(a));
                break;
            }

            case Type::TAN: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                stack.push(std::tan(a));
                break;
            }

            case Type::SQRT: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                if (a < 0) throw std::invalid_argument("Negative argument for sqrt.");
                stack.push(std::sqrt(a));
                break;
            }

            case Type::LOG: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                if (a <= 0) throw std::invalid_argument("Non-positive argument for log.");
                stack.push(std::log10(a));
                break;
            }

            case Type::LN: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                if (a <= 0) throw std::invalid_argument("Non-positive argument for ln.");
                stack.push(std::log(a));
                break;
            }

            case Type::UNARY_MINUS: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                stack.push(-a);
                break;
            }

            default:
                throw std::invalid_argument("Unknown operator type.");
        }
        rpn = rpn->next;
    }

    // Проверка результата
    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid expression.");
    }
    return stack.top();
}

// Проверка баланса скобок
bool SmartCalcModel::checkBrackets(const std::string& expression) {
    int balance = 0;
    for (char ch : expression) {
        if (ch == '(') balance++;
        if (ch == ')') balance--;
        if (balance < 0) return false; // Закрывающая скобка без открывающей
    }
    return balance == 0; // Баланс должен быть равен нулю
}


// Добавление элемента в связный список
void SmartCalcModel::pushBack(std::shared_ptr<Node>& end, double value, Priority priority, Type type) {
    auto newNode = std::make_shared<Node>(value, priority, type);
    if (!newNode) throw std::invalid_argument("Failed to create node.");
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
