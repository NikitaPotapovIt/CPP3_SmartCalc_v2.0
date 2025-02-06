#ifndef SMARTCALC_MODEL_H_
#define SMARTCALC_MODEL_H_

#include <cmath>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>

/**
 * @namespace s21
 * @brief Пространство имён для проекта S21.
 */
namespace s21 {

/**
 * @enum Type
 * @brief Типы элементов в выражении.
 */
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

/**
 * @enum Priority
 * @brief Приоритеты операторов.
 */
enum class Priority {
    SHORT = 1,    // Низкий приоритет (например, +, -)
    MIDDLE = 2,   // Средний приоритет (например, *, /)
    HIGH = 3,     // Высокий приоритет (например, ^, функции)
    ROUNDBRACKET = -1  // Приоритет скобок
};

/**
 * @struct Node
 * @brief Структура узла для хранения элементов выражения.
 */
struct Node {
    double value;          // Значение числа или оператора
    Priority priority;     // Приоритет оператора
    Type type;             // Тип элемента (число, оператор, функция и т.д.)
    std::shared_ptr<Node> next; // Указатель на следующий узел

    Node(double val, Priority prio, Type typ)
        : value(val), priority(prio), type(typ), next(nullptr) {}
};

/**
 * @class SmartCalcModel
 * @brief Модель для работы с математическими выражениями.
 */
class SmartCalcModel {
public:
    /**
     * @brief Парсит математическое выражение и вычисляет результат.
     * @param expression Строка с математическим выражением.
     * @param x_value Значение переменной x.
     * @return Результат вычисления.
     */
    double parse(const std::string& expression, double x_value);

private:
    /**
     * @brief Преобразует выражение в обратную польскую запись.
     * @param end Указатель на начальный узел.
     * @return Указатель на преобразованное выражение.
     */
    std::shared_ptr<Node> delimiter(std::shared_ptr<Node> end);

    /**
     * @brief Выполняет арифметические операции.
     * @param a Первое число.
     * @param b Второе число.
     * @param sym Тип операции.
     * @return Результат операции.
     */
    double arithmetic(double a, double b, Type sym);

    /**
     * @brief Выполняет тригонометрические операции.
     * @param a Число.
     * @param sym Тип операции.
     * @return Результат операции.
     */
    double trigonometry(double a, Type sym);

    /**
     * @brief Преобразует инфиксное выражение в обратную польскую запись.
     * @param end Указатель на начальный узел.
     * @return Указатель на преобразованное выражение.
     */
    std::shared_ptr<Node> RPN(std::shared_ptr<Node> end);

    /**
     * @brief Вычисляет значение выражения в обратной польской записи.
     * @param end Указатель на начальный узел.
     * @return Результат вычисления.
     */
    double calcExpression(std::shared_ptr<Node> end);

    /**
     * @brief Добавляет новый узел в список.
     * @param end Указатель на текущий конец списка.
     * @param value Значение нового узла.
     * @param priority Приоритет нового узла.
     * @param type Тип нового узла.
     */
    void pushBack(std::shared_ptr<Node>& end, double value, Priority priority, Type type);

    /**
     * @brief Проверяет правильность расстановки скобок.
     * @param expression Строка с математическим выражением.
     * @return true, если скобки расставлены корректно, иначе false.
     */
    bool checkBrackets(const std::string& expression);

    /**
     * @brief Обрабатывает разделители в выражении.
     * @param calc Указатель на текущий конец списка.
     * @param tmp_str Временная строка для обработки чисел.
     */
    void lineBreak(std::shared_ptr<Node>& calc, std::string& tmp_str);
};

} // namespace s21

#endif  // SMARTCALC_MODEL_H_
