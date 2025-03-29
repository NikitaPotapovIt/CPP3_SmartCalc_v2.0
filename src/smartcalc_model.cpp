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

    std::shared_ptr<Node> calc = nullptr;
    double result = 0;
    std::string tmp_str;

    for (size_t i = 0; i < expression.length(); ++i) {
        if (expression[i] == ' ') continue;
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
                if (i == 0 || expression[i - 1] == '(' || isOperator(expression[i - 1])) {
                    continue; // Унарный плюс игнорируется
                } else {
                    pushBack(calc, 0, Priority::SHORT, Type::PLUS);
                }
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
            } else if (expression.substr(i, 3) == "cot") {
                pushBack(calc, 0, Priority::UNARY, Type::COT);
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
            } else {
                throw std::invalid_argument("Invalid character in expression.");
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
        if (!calc) throw std::invalid_argument("Invalid RPN transformation.");
        result = calcExpression(calc);
    }
    
    if (std::isnan(result) || std::isinf(result)) {
        throw std::invalid_argument("Invalid expression result.");
    }
    return result;
}

// Преобразование в RPN
std::shared_ptr<Node> SmartCalcModel::RPN(std::shared_ptr<Node> end) {
    std::stack<std::shared_ptr<Node>> opStack;
    std::shared_ptr<Node> output = nullptr;
    
    while (end) {
        switch (end->type) {
            case Type::NUMBER:
            case Type::X:
                pushBack(output, end->value, Priority::SHORT, end->type);
                break;
                
            case Type::ROUNDBRACKET_L:
                opStack.push(std::make_shared<Node>(*end));
                break;
                
            case Type::ROUNDBRACKET_R:
                while (!opStack.empty() && opStack.top()->type != Type::ROUNDBRACKET_L) {
                    pushBack(output, 0, opStack.top()->priority, opStack.top()->type);
                    opStack.pop();
                }
                if (!opStack.empty()) opStack.pop();
                else throw std::invalid_argument("Mismatched parentheses");
                break;
                
            case Type::UNARY_MINUS:
            case Type::SIN:
            case Type::COS:
            case Type::TAN:
            case Type::ASIN:
            case Type::ACOS:
            case Type::ATAN:
            case Type::SQRT:
            case Type::LOG:
            case Type::LN:
                opStack.push(std::make_shared<Node>(*end));
                break;
                
            default:
                while (!opStack.empty() && 
                       opStack.top()->type != Type::ROUNDBRACKET_L &&
                       (opStack.top()->priority >= end->priority &&
                        end->type != Type::POW)) {
                    pushBack(output, 0, opStack.top()->priority, opStack.top()->type);
                    opStack.pop();
                }
                opStack.push(std::make_shared<Node>(*end));
                break;
        }
        end = end->next;
    }
    
    while (!opStack.empty()) {
        if (opStack.top()->type == Type::ROUNDBRACKET_L) {
            throw std::invalid_argument("Mismatched parentheses");
        }
        pushBack(output, 0, opStack.top()->priority, opStack.top()->type);
        opStack.pop();
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

            case Type::COT: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                double tan_a = std::tan(a);
                if (tan_a == 0) throw std::invalid_argument("Cotangent undefined at this point.");
                stack.push(1.0 / tan_a);
                break;
            }

            case Type::ASIN: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                if (a < -1 || a > 1) throw std::invalid_argument("Argument out of range for asin.");
                stack.push(std::asin(a));
                break;
            }
            case Type::ACOS: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                if (a < -1 || a > 1) throw std::invalid_argument("Argument out of range for acos.");
                stack.push(std::acos(a));
                break;
            }
            case Type::ATAN: {
                if (stack.empty()) throw std::invalid_argument("Invalid expression.");
                double a = stack.top(); stack.pop();
                stack.push(std::atan(a));
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
        if (balance < 0) return false;
    }
    return balance == 0;
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
