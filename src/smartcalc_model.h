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
    ROUNDBRACKET_L, // Открывающая скобка
    ROUNDBRACKET_R  // Закрывающая скобка
};

enum class Priority {
    SHORT = 1,  // Низкий приоритет (например, +, -)
    MIDDLE = 2, // Средний приоритет (например, *, /)
    HIGH = 3,   // Высокий приоритет (например, ^, функции)
    UNARY = 4, // Для унарных операторов (функций)
    ROUNDBRACKET = -1    // Приоритет скобок
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
    double parse(const std::string& expression, double x_value);

private:
    std::shared_ptr<Node> delimiter(std::shared_ptr<Node> end);
    std::shared_ptr<Node> RPN(std::shared_ptr<Node> end);
    double arithmetic(double a, double b, Type sym);
    double trigonometry(double a, Type sym);
    double calcExpression(std::shared_ptr<Node> end, double x_value);
    void pushBack(std::shared_ptr<Node>& end, double value, Priority priority, Type type);
    bool checkBrackets(const std::string& expression);
    void lineBreak(std::shared_ptr<Node>& calc, std::string& tmp_str);
};

} // namespace s21

#endif  // SMARTCALC_MODEL_H_
