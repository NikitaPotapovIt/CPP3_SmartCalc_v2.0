#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "credit.h"
#include "deposit.h"
#include "../smartcalc_model.h"
#include "../smartcalc_controller.h"

double num_first;
int flag = 0;
int dot = 0;
int count = 0;
int min_flag = 0;
int pl_falg = 0;
int is_digit = 1;
int is_r_bracket = 1;
int is_sign = 0;
int is_x = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller_(&model_) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(ariph_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(ariph_numbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(ariph_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(ariph_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *) sender();
  QString all_numbers;
  if (ui->result->text() == '0') {
    ui->result->setText("");
  }
  all_numbers = (ui->result->text() + button->text());
  ui->result->setText(all_numbers);

  flag = 0;
  min_flag = 0;
  pl_falg = 0;
  is_digit = 0;
  is_r_bracket = 1;
  is_sign = 1;
  is_x = 1;
}

void MainWindow::ariph_numbers() {
  QPushButton *button = (QPushButton *) sender();
  if (ui->result->text() == '0') flag = 1;
  if (flag == 0) {
    ui->result->setText(ui->result->text() + button->text());
    flag = 1;
    dot = 0;
    is_digit = 1;
    is_r_bracket = 1;
    is_sign = 0;
    is_x = 1;
  }
}

void MainWindow::trigon_numbers() {
  QPushButton *button = (QPushButton *) sender();
  int loc_falg = 1;
  if (dot == 0) {
    if (ui->result->text() == '0') {
      ui->result->setText("");
      loc_falg = 0;
    }
    if ((is_digit == 0 || is_r_bracket == 0) && loc_falg == 1) {
      ui->result->setText(ui->result->text() + "*" + button->text() + "(");
    } else {
      ui->result->setText(ui->result->text() + button->text() + "(");
    }
    flag = 1;
    dot = 0;
    count += 1;
    min_flag = 0;
    pl_falg = 0;
    is_digit = 1;
    is_r_bracket = 1;
    is_sign = 0;
    is_x = 1;
  }
}

void MainWindow::on_pushButton_dot_clicked() {
  if (flag == 0 && dot == 0) {
    ui->result->setText(ui->result->text() + ".");
    flag = 1;
    dot = 1;
    is_digit = 1;
    is_r_bracket = 1;
    is_sign = 1;
    is_x = 1;
  }
}

void MainWindow::on_pushButton_clear_clicked() {
  ui->pushButton_plus->setChecked(false);
  ui->pushButton_minus->setChecked(false);
  ui->pushButton_mul->setChecked(false);
  ui->pushButton_div->setChecked(false);
  ui->result->setText("0");
  flag = 0;
  dot = 0;
  count = 0;
  min_flag = 0;
  pl_falg = 0;
  is_digit = 1;
  is_r_bracket = 1;
  is_sign = 0;
  is_x = 1;
}

void MainWindow::on_pushButton_equals_clicked() {
  double x = 0;
  QPushButton *button = (QPushButton *) sender();
  button->setChecked(true);
  // QString send = ui->result->text();
  // QByteArray ba = send.toLocal8Bit();
  // char *buf = ba.data();

  if (!ui->x_value->text().isEmpty()) {
        x = ui->x_value->text().toDouble();
    }

    QString expression = ui->result->text();
    double result = controller_.calculateExpression(expression.toStdString(), x);  // Use controller

    QString resultStr = QString::number(result, 'g', 15);
    ui->result->setText(resultStr);
}

void MainWindow::on_pushButton_round_bracket_L_clicked() {
  QString all_numbers;
  if (ui->result->text() == '0') {
    ui->result->setText("");
    is_sign = 0;
  }
  if (is_sign == 0) {
    all_numbers = (ui->result->text() + "(");
    ui->result->setText(all_numbers);
    count += 1;
  }
  is_x = 1;
}

void MainWindow::on_pushButton_round_bracket_R_clicked() {
  QString all_numbers;
  if (count > 0 && flag == 0) {
    all_numbers = (ui->result->text() + ")");
    ui->result->setText(all_numbers);
    flag = 0;
    count -= 1;
    min_flag = 0;
    pl_falg = 0;
    is_digit = 1;
    is_r_bracket = 0;
    is_sign = 1;
    is_x = 1;
  }
}

void MainWindow::on_pushButton_minus_clicked() {
  if (min_flag == 0) {
    if (ui->result->text() == '0') ui->result->setText("");
    ui->result->setText(ui->result->text() + "-");
    flag = 1;
    dot = 0;
    min_flag = 1;
    pl_falg = 1;
    is_digit = 1;
    is_r_bracket = 1;
    is_sign = 0;
    is_x = 1;
  }
}

void MainWindow::on_pushButton_plus_clicked() {
  if (pl_falg == 0) {
    if (ui->result->text() == '0') ui->result->setText("");
    ui->result->setText(ui->result->text() + "+");
    flag = 1;
    dot = 0;
    min_flag = 1;
    pl_falg = 1;
    is_digit = 1;
    is_r_bracket = 1;
    is_sign = 0;
    is_x = 1;
  }
}

void MainWindow::on_pushButton_graph_clicked() {
    QString expression = ui->result->text();

    ui->widget->clearGraphs();
    x.clear();
    y.clear();
    result_1 = 0;
    result_2 = 0;
    h = 0.1;

    double Y = ui->x_value->text().toDouble();
    if (Y == 0) Y = 1;

    xy_1 = ui->x1->text().toDouble();
    xy_2 = ui->x2->text().toDouble();
    result_1 = ui->y1->text().toInt();
    result_2 = ui->y2->text().toInt();

    xBegin = result_2;
    xEnd = result_1 + h;

    ui->widget->xAxis->setRange(xy_2, xy_1);
    ui->widget->yAxis->setRange(result_2, result_1);
    N = (xEnd - xBegin) / h + 2;

    for (double X = xBegin; X <= xEnd; X += h) {
        x.push_back(X);
        
        double yValue = controller_.calculateExpression(expression.toStdString(), Y * X);
        y.push_back(yValue);
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
}


void MainWindow::on_pushButton_x_clicked() {
  int loc_falg = 1;
  if (ui->result->text() == '0') {
    ui->result->setText("");
    loc_falg = 0;
  }
  if ((is_digit == 0 || is_r_bracket == 0 || is_x == 0) && loc_falg == 1) {
    ui->result->setText(ui->result->text() + "*x");
  } else {
    ui->result->setText(ui->result->text() + "x");
  }
  flag = 0;
  min_flag = 0;
  pl_falg = 0;
  is_digit = 0;
  is_r_bracket = 1;
  is_sign = 1;
  is_x = 0;
}

void MainWindow::on_pushButton_clicked() {
  credit window;
  window.setModal(true);
  window.exec();
}

void MainWindow::on_pushButton_10_clicked() {
  deposit window;
  window.setModal(true);
  window.exec();
}
