#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

QString const_expr;
x_x x_info[1] = {{-10, 10, 0.001}};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(add_char()));
  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(add_char()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(add_char()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_label_editingFinished() { const_expr = ui->label->text(); }

void MainWindow::add_char() {
  QPushButton *button = (QPushButton *)sender();

  ui->label->setText((ui->label->text()) + button->text());
}

void MainWindow::on_pushButton_clear_clicked() {
  x_info->start = -10;
  x_info->end = 10;
  x_info->step = 0.001;
  ui->label->setText("");
  ui->graph->clearGraphs();
  ui->label_month->setText("nan");
  ui->label_over->setText("nan");
  ui->label_total->setText("nan");
  ui->graph->addGraph();
  ui->graph->graph(0)->setData(X_void, Y_void);
  ui->graph->xAxis->setRange(0, 5);
  ui->graph->yAxis->setRange(0, 5);
  ui->graph->replot();
  ui->lineEdit_start->setText("-10");
  ui->lineEdit_end->setText("10");
  ui->lineEdit_step->setText("0.001");
  ui->lineEdit_sum->setText("0.0");
  ui->lineEdit_interest->setText("0.0");
  ui->lineEdit_months->setText("0.0");
}

void MainWindow::on_lineEdit_start_editingFinished() {
  x_info->start = ui->lineEdit_start->text().toDouble();
}

void MainWindow::on_lineEdit_end_editingFinished() {
  x_info->end = ui->lineEdit_end->text().toDouble();
}

void MainWindow::on_lineEdit_step_editingFinished() {
  x_info->step = ui->lineEdit_step->text().toDouble();
}

void MainWindow::on_lineEdit_sum_editingFinished() {
  sum = ui->lineEdit_sum->text().toDouble();
}

void MainWindow::on_lineEdit_months_editingFinished() {
  months = ui->lineEdit_months->text().toDouble();
}

void MainWindow::on_lineEdit_interest_editingFinished() {
  interest = ui->lineEdit_interest->text().toDouble();
}

void MainWindow::on_pushButton_del_clicked() {
  QString temp = ui->label->text();
  temp.chop(1);
  ui->label->setText(temp);
}

void MainWindow::on_pushButton_enter_clicked() {
  int flag = 0;
  QString expr = const_expr;
  if (expr.isEmpty()) {
    ui->label->setText("0");
  } else {
    QByteArray ba = expr.toLocal8Bit();
    double result_double = 0;
    char *c_string = ba.data();
    flag = process(c_string, &result_double);
    if (flag == 0) {
      QString result_string = QString::number(result_double, 'f');
      ui->label->setText(result_string);
      expr.clear();
    } else if (flag == -1) {
      ui->label->setText("Error in calculation, wrong postfix string");
      const_expr.clear();
    } else if (flag == 1) {
      ui->label->setText("Input null");
      const_expr.clear();
    } else if (flag == 2) {
      ui->label->setText("Something wrong with string");
      const_expr.clear();
    } else if (flag == 3) {
      ui->label->setText("Something wrong then string build lexems");
      const_expr.clear();
    } else if (flag == 17) {
      ui->label->setText("Error : Sqrt(x) and x < 0.0");
      const_expr.clear();
    } else if (flag == 18) {
      ui->label->setText("Error : LOG(x) or LN(x) and x < 0.0");
      const_expr.clear();
    } else if (flag == 24) {
      ui->label->setText("Error : Division by zero");
      const_expr.clear();
    }
  }
}

void MainWindow::on_pushButton_graph_dot_clicked() {
  double start = x_info->start;
  double end = x_info->end;
  double step = x_info->step;
  QString temp_expr = const_expr;
  int flag = 0;
  double starting_point = x_info->start;
  QVector<double> X, Y;
  ui->graph->addGraph();
  ui->graph->graph(0)->setPen(QPen(Qt::blue));
  ui->graph->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
  for (double i = start; i <= end && step > 0; i += step) {
    temp_expr = const_expr;
    temp_expr.replace("x", QString::number(i));
    QByteArray ba_for_graph = temp_expr.toLocal8Bit();
    char *c_string = ba_for_graph.data();
    double res = 0;
    flag = calc_cpp(c_string, &res);
    if (i == start && flag != 0)
      return;
    if (fabs(res) > 1000000)
      continue;
    if (fabs(res) - 0.0 < 0.000001)
      res = 0;
    if (flag == 0) {
      X.push_back(i);
      Y.push_back(res);
    }
  }
  x_info->start = starting_point;
  ui->graph->graph(0)->setData(X, Y);
  ui->graph->graph(0)->setPen(QColor(50, 50, 50, 255));
  ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->graph->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
  ui->graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);
  ui->graph->replot();
  X.clear();
  Y.clear();
}

void MainWindow::on_pushButton_credit_clicked() {
  if (months == 0.0 || sum == 0.0 || interest == 0.0) {
    ui->label->setText("Недостаточно данных");
  } else if (interest < 4.0) {
    ui->label->setText(
        "Мы живем в эпоху больших кредитных ставок, введите больше 4.0% ");
  } else if (sum < 100000) {
    ui->label->setText(
        "Банку не выгодно давать маленькие кредиты, введите больше 100000 ");
  } else if (months < 3) {
    ui->label->setText("Минимальный срок кредита 3 месяца, вам в МФО ");
  } else {
    QString text_in_box = ui->comboBox_type->currentText();
    if (text_in_box.compare("Annuity") == 0) {
      double month_pay =
          sum * ((interest / 1200.0) /
                 (1.0 - pow((1.0 + interest / 1200.0), (-(months)))));
      double common_sum = month_pay * months;
      double over_pay = common_sum - sum;
      QString str_month = QString(tr("Ежемесячный платеж: %1")).arg(month_pay);
      QString str_over = QString(tr("Переплата по кредиту: %1")).arg(over_pay);
      QString str_total = QString(tr("Общая выплата: %1")).arg(common_sum);
      ui->label_month->setText(str_month);
      ui->label_over->setText(str_over);
      ui->label_total->setText(str_total);
      str_month.clear();
      str_over.clear();
      str_total.clear();
    } else {
      double monthly = sum / months;
      double payment = 0;
      double payment_first = 0;
      double payment_last = 0;
      double total = 0;
      for (int i = 0; i < months; i++) {
        payment = monthly + (sum - monthly * i) * interest / 1200;
        if (i == 0)
          payment_first = payment;
        if (i == months - 1)
          payment_last = payment;
        total += payment;
      }
      double over_pay = total - sum;
      QString str_month = QString(tr("Ежемесячный платеж: от %1 до %2"))
                              .arg(payment_first)
                              .arg(payment_last);
      QString str_over = QString(tr("Переплата по кредиту: %1")).arg(over_pay);
      QString str_total = QString(tr("Общая выплата: %1")).arg(total);
      ui->label_month->setText(str_month);
      ui->label_over->setText(str_over);
      ui->label_total->setText(str_total);
    }
  }
}

void MainWindow::on_pushButton_graph_line_clicked() {
  QString temp_expr = const_expr;
  int flag = 0;
  double a = x_info->start;
  double b = x_info->end;
  double h = x_info->step;
  int N = (b - a) / h + 2;
  int i = 0;
  QVector<double> x(N), y(N);
  for (double X = a; X <= b; X += h) {
    if (X > 0.0 && X < 0.000001)
      continue;
    temp_expr = const_expr;
    temp_expr.replace("x", QString::number(X));
    QByteArray ba_for_graph = temp_expr.toLocal8Bit();
    char *c_string = ba_for_graph.data();
    double res = 0;
    flag = calc_cpp(c_string, &res);
    if (X == a && flag != 0)
      return;
    if (flag == 0) {
      if (fabs(res) > 1000000 || (fabs(res) - 0.0 < 0.000001))
        continue;
      if (const_expr.contains("tan") && res == 0.0)
        continue;
      x[i] = X;
      y[i] = res;
    }
    i++;
  }
  ui->graph->clearGraphs();
  ui->graph->addGraph();
  ui->graph->graph(0)->setData(x, y);
  ui->graph->xAxis->setLabel("x");
  ui->graph->yAxis->setLabel("y");
  ui->graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                             QCP::iSelectPlottables);
  if (temp_expr.contains("tan")) {
    ui->graph->xAxis->setRange(-10, 10);
    ui->graph->yAxis->setRange(-10, 10);
  } else {
    ui->graph->xAxis->setRange(a * 1.1, b * 1.1);
    double minY = y[0], maxY = y[0];
    for (int i = 1; i < N; i++) {
      if (y[i] < minY)
        minY = y[i];
      if (y[i] > maxY)
        maxY = y[i];
    }
    ui->graph->yAxis->setRange(minY * 1.1, maxY * 1.1);
  }
  ui->graph->replot();
  x.clear();
  y.clear();
}

