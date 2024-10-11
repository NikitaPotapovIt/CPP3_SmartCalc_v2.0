#include "smartcalc_model.h"

double SmartCalcModel::parse(const std::string& expression, double x_value) {
    std::shared_ptr<Node> calc = nullptr;
    double result = 0;
    std::string tmp_str;
    for (size_t i = 0; i <= expression.length(); i++) {
        if (isdigit(expression[i]) || expression[i] == '.') {
            tmp_str += expression[i];
        } else {
            if (expression[i] == '+' || expression[i] == '-') {
                if (tmp_str.empty() && expression[i - 1] != ')') tmp_str = expression[i];
                else {
                    lineBreak(calc, tmp_str);
                    pushBack(calc, 0, Priority::SHORT, (expression[i] == '+') ? Type::PLUS : Type::MINUS);
                }
            } else if (expression[i] == '*' || expression[i] == '/') {
                lineBreak(calc, tmp_str);
                pushBack(calc, 0, Priority::MIDDLE, (expression[i] == '*') ? Type::MULT : Type::DIV);
            } else if (expression[i] == '^') {
                lineBreak(calc, tmp_str);
                pushBack(calc, 0, Priority::HIGH, Type::POW);
            } else if (expression[i] == 'x') {
                pushBack(calc, x_value, Priority::SHORT, Type::X);
            } else {
                lineBreak(calc, tmp_str);
            }
        }
    }

    if (!checkBrackets(expression)) {
        if (calc != nullptr) calc = RPN(calc);
        if (calc != nullptr) calc = delimiter(calc);
        if (calc != nullptr) result = this->calc(calc);
    }

    return result;
}

std::shared_ptr<Node> SmartCalcModel::delimiter(std::shared_ptr<Node> end) {
    std::shared_ptr<Node> res = nullptr;
    std::shared_ptr<Node> str = nullptr;
    while (end) {
        if (end->priority == Priority::SHORT) {
            pushBack(res, end->value, Priority::SHORT, Type::NUMBER);
        } else {
            if (str != nullptr) {
                if (end->priority > str->priority || end->type == Type::ROUNDBRACKET_L) {
                    pushBack(str, 0, end->priority, end->type);
                } else {
                    while (str && (str->type != Type::ROUNDBRACKET_L)) {
                        pushBack(res, 0, str->priority, str->type);
                        str = str->next;
                    }
                    pushBack(str, 0, end->priority, end->type);
                }
            } else {
                pushBack(str, 0, end->priority, end->type);
            }
        }
        end = end->next;
    }

    while (str) {
        if (str->type != Type::ROUNDBRACKET_L && str->type != Type::ROUNDBRACKET_R) {
            pushBack(res, 0, str->priority, str->type);
        }
        str = str->next;
    }

    return res;
}

double SmartCalcModel::calc(std::shared_ptr<Node> end) {
    std::shared_ptr<Node> str = nullptr;
    double result = 0, a = 0, b = 0;
    int cnt = 2;

    while (end) {
        if (end->priority == Priority::SHORT) {
            pushBack(str, end->value, Priority::SHORT, Type::NUMBER);
        } else if (end->priority > Priority::SHORT && end->type < Type::SIN) {
            while (cnt > 0 && str) {
                if (cnt == 2) b = str->value;
                else if (cnt == 1) a = str->value;
                cnt--;
                str = str->next;
            }
            pushBack(str, arithmetic(a, b, end->type), Priority::SHORT, Type::NUMBER);
            cnt = 2;
        } else if (end->priority > Priority::SHORT) {
            while (cnt == 2 && str) {
                b = str->value;
                cnt--;
                str = str->next;
            }
            pushBack(str, trigonometry(b, end->type), Priority::SHORT, Type::NUMBER);
            cnt = 2;
        }
        end = end->next;
    }

    if (str) result = str->value;
    return result;
}

double SmartCalcModel::arithmetic(double a, double b, Type sym) {
    switch (static_cast<int>(sym)) {
        case static_cast<int>(Type::PLUS): return a + b;
        case static_cast<int>(Type::MINUS): return a - b;
        case static_cast<int>(Type::DIV): return a / b;
        case static_cast<int>(Type::MULT): return a * b;
        case static_cast<int>(Type::POW): return std::pow(a, b);
        case static_cast<int>(Type::MOD): return std::fmod(a, b);
        default: return 0;
    }
}

double SmartCalcModel::trigonometry(double a, Type sym) {
    switch (static_cast<int>(sym)) {
        case static_cast<int>(Type::SIN): return std::sin(a);
        case static_cast<int>(Type::COS): return std::cos(a);
        case static_cast<int>(Type::TAN): return std::tan(a);
        case static_cast<int>(Type::ASIN): return std::asin(a);
        case static_cast<int>(Type::ACOS): return std::acos(a);
        case static_cast<int>(Type::ATAN): return std::atan(a);
        case static_cast<int>(Type::SQRT): return std::sqrt(a);
        case static_cast<int>(Type::LN): return std::log(a);
        case static_cast<int>(Type::LOG): return std::log10(a);
        default: return 0;
    }
}

void SmartCalcModel::pushBack(std::shared_ptr<Node>& end, double value, Priority priority, Type type) {
    auto newNode = std::make_shared<Node>(value, priority, type);
    newNode->next = end;
    end = newNode;
}

bool SmartCalcModel::checkBrackets(const std::string& expression) {
    int balance = 0;
    for (char ch : expression) {
        if (ch == '(') balance++;
        if (ch == ')') balance--;
    }
    return balance == 0;
}

void SmartCalcModel::lineBreak(std::shared_ptr<Node>& calc, std::string& tmp_str) {
    if (!tmp_str.empty()) {
        pushBack(calc, std::stod(tmp_str), Priority::SHORT, Type::NUMBER);
        tmp_str.clear();
    }
}

std::shared_ptr<Node> SmartCalcModel::RPN(std::shared_ptr<Node> end) {
    std::shared_ptr<Node> str = nullptr;
    while (end != nullptr) {
        pushBack(str, end->value, end->priority, end->type);
        end = end->next;
    }
    return str;
}
