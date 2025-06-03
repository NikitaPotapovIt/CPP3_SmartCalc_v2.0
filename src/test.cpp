#include <gtest/gtest.h>
#include <cmath>
#include "smartcalc_model.h"

TEST(BaseTests, Test0) {
  char str[64] = "2+2*2";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 6);
}

TEST(BaseTests, Test1) {
  char str[64] = "5-2+3+4/2*3";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 12);
}

TEST(BaseTests, Test2) {
  char str[64] = "8*4+1+2+1+1";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 37);
}

TEST(BaseTests, Test3) {
  char str[64] = "8*4+1+2";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 35);
}

TEST(BaseTests, Test4) {
  char str[64] = "5+3*4+2*2*3+2";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 31);
}

TEST(ParenthesesTests, Test0) {
  char str[64] = "(2+2)*2";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 8);
}

TEST(ParenthesesTests, Test1) {
  char str[64] = "(3+1)*4+((2+2)*((2+2)*2))/8";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 20);
}

TEST(ParenthesesTests, Test2) {
  char str[64] = "255-(177+58-200)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 220);
}

TEST(ParenthesesTests, Test3) {
  char str[64] = "(930-480)*16+(2004-999)*17-18*101";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 22467);
}

TEST(ParenthesesTests, Test4) {
  char str[64] = "(2+2)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 4);
}

TEST(ParenthesesTests, Test5) {
  char str[64] = "15/(7-(1+1))*3-(2+(1+1))+15";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 20);
}

TEST(TrigonometricTests, Test0) {
  char str[64] = "sin(3.141592/2)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 1, 1e-6);
}

TEST(TrigonometricTests, Test1) {
  char str[64] = "cos(3.141592/2)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 0, 1e-6);
}

TEST(TrigonometricTests, Test2) {
  char str[64] = "tan(0)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 0, 1e-6);
}

TEST(TrigonometricTests, Test3) {
  char str[64] = "cot(3.141592/2)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 0, 1e-6);
}

TEST(TrigonometricTests, Test4) {
  char str[64] = "sin(3.141592/2)+cos(3.141592/2)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 1, 1e-6);
}

TEST(TrigonometricTests, Test5) {
  char str[64] = "asin(sin(3.141592/2))";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 1.570796, 1e-6);
}

TEST(TrigonometricTests, Test6) {
  char str[64] = "acos(cos(0.7))";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 0.7, 1e-6);
}

TEST(TrigonometricTests, Test7) {
  char str[64] = "atan(tan(0.3))";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 0.3, 1e-6);
}

TEST(SqrtTests, Test0) {
  char str[64] = "sqrt(4)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 2);
}

TEST(SqrtTests, Test1) {
  char str[64] = "sqrt(2)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 1.414213, 1e-6);
}

TEST(SqrtTests, Test2) {
  char str[64] = "sqrt(3)/2";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 0.8660254, 1e-6);
}

TEST(SqrtTests, Test3) {
  char str[64] = "sqrt(3)+sqrt(1/2)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 2.4391575, 1e-6);
}

TEST(SqrtTests, Test4) {
  char str[64] = "sqrt(4)/1+sqrt(3)/2+sqrt(2)/4";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 3.2195787, 1e-6);
}

TEST(SqrtTests, Test5) {
  char str[64] = "sqrt(((2+2)*4)*4)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 8);
}

TEST(ModTests, Test0) {
  char str[64] = "4mod2";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 0);
}

TEST(ModTests, Test1) {
  char str[64] = "5mod2";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 1);
}

TEST(ModTests, Test2) {
  char str[64] = "7mod5+3.6mod1.8";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 2);
}

TEST(ModTests, Test3) {
  char str[64] = "3.6mod1.5";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 0.6, 1e-6);
}

TEST(LogTests, Test0) {
  char str[64] = "log(10)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 1);
}

TEST(LnTests, Test0) {
  char str[64] = "ln(2.718281)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_NEAR(res, 1, 1e-6);
}

TEST(LogTests, Test1) {
  char str[64] = "log(100)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 2);
}

TEST(LnTests, Test1) {
  char str[64] = "ln(1)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 0);
}

TEST(VarTests, Test0) {
  char str[64] = "2*x+1";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0); // x = 0
  EXPECT_DOUBLE_EQ(res, 1);
}

TEST(VarTests, Test1) {
  char str[64] = "2*x+1";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 2); // x = 2
  EXPECT_DOUBLE_EQ(res, 5);
}

TEST(VarTests, Test2) {
  char str[64] = "x^0+x^2+x^3";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 2); // x = 2
  EXPECT_DOUBLE_EQ(res, 13);
}

TEST(VarTests, Test3) {
  char str[64] = "sin(x)";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 3.141592 / 2); // x = π/2
  EXPECT_NEAR(res, 1, 1e-6);
}

TEST(ErrorTests, DivisionByZero) {
  char str[64] = "2 + 3 / 0";
  s21::SmartCalcModel calc;
  EXPECT_THROW(calc.parse(str, 0), std::invalid_argument);
}

TEST(ErrorTests, NegativeSqrt) {
  char str[64] = "sqrt(-1)";
  s21::SmartCalcModel calc;
  EXPECT_THROW(calc.parse(str, 0), std::invalid_argument);
}

TEST(ErrorTests, LogOfZero) {
  char str[64] = "log(0)";
  s21::SmartCalcModel calc;
  EXPECT_THROW(calc.parse(str, 0), std::invalid_argument);
}

TEST(ErrorTests, LnOfZero) {
  char str[64] = "ln(0)";
  s21::SmartCalcModel calc;
  EXPECT_THROW(calc.parse(str, 0), std::invalid_argument);
}

TEST(ErrorTests, EmptyExpression) {
  char str[64] = "";
  s21::SmartCalcModel calc;
  EXPECT_THROW(calc.parse(str, 0), std::invalid_argument);
}

TEST(ErrorTests, InvalidExpression) {
  char str[64] = "2 + * 3";
  s21::SmartCalcModel calc;
  EXPECT_THROW(calc.parse(str, 0), std::invalid_argument);
}

TEST(ErrorTests, UnbalancedBrackets) {
  char str[64] = "(2+2";
  s21::SmartCalcModel calc;
  EXPECT_THROW(calc.parse(str, 0), std::invalid_argument);
}

TEST(EdgeTests, Test0) {
  char str[64] = "0";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 0);
}

TEST(EdgeTests, Test1) {
  char str[64] = "-5";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, -5);
}

TEST(EdgeTests, Test2) {
  char str[64] = "+5";
  double res;
  s21::SmartCalcModel calc;
  res = calc.parse(str, 0);
  EXPECT_DOUBLE_EQ(res, 5);
}
