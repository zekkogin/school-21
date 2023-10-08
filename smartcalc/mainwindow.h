/**
 * @file mainwindow.h
 *
 * All the includes needed for the main.cpp and mainwindow.cpp
 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleValidator>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QVector>
#include <cstdio>
#include <iostream>
#include <limits.h>
#include <math.h>
#include <qcustomplot.h>

extern "C" {
#include "s21_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  double sum = 0;
  double months = 0;
  double interest = 0;
  QVector<double> X_void, Y_void;

private slots:
  /**
   * @brief Add buttons to LABEL
   */
  void add_char();
  /**
   * @brief If clicked clear all data
   */
  void on_pushButton_clear_clicked();
  /**
   * @brief If clicked clear one char in QLineEdit (Label in Calculator)
   */
  void on_pushButton_del_clicked();
  /**
   * @brief If clicked calculate and out result in doulbe data (.6lf)
   */
  void on_pushButton_enter_clicked();
  void on_label_editingFinished();
  void on_lineEdit_start_editingFinished();
  void on_lineEdit_end_editingFinished();
  void on_lineEdit_step_editingFinished();
  void on_pushButton_graph_dot_clicked();
  void on_pushButton_graph_line_clicked();
  void on_lineEdit_sum_editingFinished();
  void on_lineEdit_months_editingFinished();
  void on_lineEdit_interest_editingFinished();
  void on_pushButton_credit_clicked();
};
#endif // SRC_MAINWINDOW_H
