#ifndef SMARTCALC_MODEL_H_
#define SMARTCALC_MODEL_H_

#include <cmath>
#include <memory>
#include <string>

// Определение типов данных и приоритетов
enum class Type {
    NUMBER = 1, X = 2, PLUS = 3, MINUS = 4, MULT = 5, DIV = 6, POW = 7, MOD = 9,
    SIN = 10, COS = 11, TAN = 12, ASIN = 13, ACOS = 14, ATAN = 15, SQRT = 16,
    LN = 17, LOG = 18, ROUNDBRACKET_L = 19, ROUNDBRACKET_R = 20
};

enum class Priority {
    SHORT = 1, MIDDLE = 2, HIGH = 3, ROUNDBRACKET = -1
};

// Структура узла
struct Node {
    double value;
    Priority priority;
    Type type;
    std::shared_ptr<Node> next;

    Node(double val, Priority prio, Type typ)
        : value(val), priority(prio), type(typ), next(nullptr) {}
};

// Модель калькулятора
class SmartCalcModel {
public:
    double parse(const std::string& expression, double x_value);

private:
    std::shared_ptr<Node> delimiter(std::shared_ptr<Node> end);
    double calc(std::shared_ptr<Node> end);
    double arithmetic(double a, double b, Type sym);
    double trigonometry(double a, Type sym);
    std::shared_ptr<Node> RPN(std::shared_ptr<Node> end);
    void pushBack(std::shared_ptr<Node>& end, double value, Priority priority, Type type);
    bool checkBrackets(const std::string& expression);
    void lineBreak(std::shared_ptr<Node>& calc, std::string& tmp_str);
};

#endif  // SMARTCALC_MODEL_H_
