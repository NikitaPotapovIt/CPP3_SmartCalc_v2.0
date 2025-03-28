#ifndef SMARTCALC_MODEL_H_
#define SMARTCALC_MODEL_H_

#include <cmath>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>

namespace s21 {

enum class Type {
    NUMBER,       // Число
    X,            // Переменная x
    PLUS,         // Оператор +
    MINUS,        // Оператор -
    MULT,         // Оператор *
    DIV,          // Оператор /
    POW,          // Оператор ^
    MOD,          // Оператор mod
    SIN,          // Функция sin
    COS,          // Функция cos
    COTAN,        // Функция cot
    TAN,          // Функция tan
    ASIN,         // Функция asin
    ACOS,         // Функция acos
    ATAN,         // Функция atan
    SQRT,         // Функция sqrt
    LN,           // Функция ln
    LOG,          // Функция log
    UNARY_MINUS,    // Унарный минус
    ROUNDBRACKET_L, // Открывающая скобка
    ROUNDBRACKET_R  // Закрывающая скобка
};

enum class Priority {
    SHORT = 0,      // +, -
    MIDDLE = 1,     // *, /, mod
    HIGH = 2,       // ^
    UNARY = 3,      // unary_minus
    FUNCTION = 3,   // sin, cos, sqrt, log, ln
    ROUNDBRACKET = 4 // ()
};

struct Node {
    double value;          // Значение числа или оператора
    Priority priority;     // Приоритет оператора
    Type type;             // Тип элемента (число, оператор, функция и т.д.)
    std::shared_ptr<Node> next; // Указатель на следующий узел

    Node(double val, Priority prio, Type typ)
        : value(val), priority(prio), type(typ), next(nullptr) {}
};

class SmartCalcModel {
public:
    bool isOperator(char ch);
    double parse(const std::string& expression, double x_value);

private:
    std::shared_ptr<Node> delimiter(std::shared_ptr<Node> end);
    std::shared_ptr<Node> RPN(std::shared_ptr<Node> end);
    double arithmetic(double a, double b, Type sym);
    double trigonometry(double a, Type sym);
    double calcExpression(std::shared_ptr<Node> rpn);
    void pushBack(std::shared_ptr<Node>& end, double value, Priority priority, Type type);
    bool checkBrackets(const std::string& expression);
    void lineBreak(std::shared_ptr<Node>& calc, std::string& tmp_str);
};

} // namespace s21

#endif  // SMARTCALC_MODEL_H_
