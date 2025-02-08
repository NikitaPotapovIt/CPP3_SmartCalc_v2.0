#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <QtMath>
#include "ui_mainwindow.h"
#include "../smartcalc_controller.h"
#include "../smartcalc_model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  Ui::MainWindow *ui;
  s21::SmartCalcModel model_;
  s21::SmartCalcController controller_; 

 private:
  double xBegin, xEnd, h, X, xy_1, xy_2, result_1, result_2;
  int N;

  QVector<double> x, y;

 private
  slots:
      void digits_numbers();
  void ariph_numbers();
  void trigon_numbers();
  void on_pushButton_dot_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_equals_clicked();
  void on_pushButton_round_bracket_L_clicked();
  void on_pushButton_round_bracket_R_clicked();
  void on_pushButton_minus_clicked();
  void on_pushButton_plus_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_graph_clicked();
  void on_pushButton_clicked();
  void on_pushButton_10_clicked();
};
#endif // MAINWINDOW_H
