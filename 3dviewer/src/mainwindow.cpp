#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

extern "C" {
#include "Logic/matrix_t.c"
#include "Logic/parser.c"
#include "s21_parser.h"
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("Crush me");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_browse_clicked() {
  QString fileName = QFileDialog::getOpenFileName(this, "Select a file",
                                                  QDir::homePath(), "*.obj");
  if (!fileName.isEmpty()) {
    QByteArray ba = fileName.toLocal8Bit();
    char *c_string = ba.data();
    ui->widget->data_object = (struct data *)malloc(sizeof(struct data));
    parser(ui->widget->data_object, c_string);
    ui->label_filename->setText(fileName);
    ui->label_facets->setText(
        QString::number(ui->widget->data_object->counter_facets));
    ui->label_vertexes->setText(
        QString::number(ui->widget->data_object->counter_index));
    ui->widget->vertex_opengl = (double *)calloc(
        (ui->widget->data_object->counter_vertexes * 3), sizeof(double));
    ui->widget->facets_opengl = (unsigned int *)calloc(
        (ui->widget->data_object->counter_index * 2 + 1), sizeof(unsigned int));
    to_vertex_opengl(ui->widget->data_object, ui->widget->vertex_opengl);
    to_facets_opengl(ui->widget->data_object, ui->widget->facets_opengl);

    ui->widget->file_opened = true;
  } else {
    fprintf(stderr, "\n Filename doesn`t exists.");
  }
}

void MainWindow::on_doubleSpinBox_move_x_valueChanged(double arg1) {
  ui->widget->x_move = arg1;
}

void MainWindow::on_doubleSpinBox_move_y_valueChanged(double arg1) {
  ui->widget->y_move = arg1;
}

void MainWindow::on_doubleSpinBox_move_z_valueChanged(double arg1) {
  ui->widget->z_move = arg1;
}

void MainWindow::on_doubleSpinBox_rotate_x_valueChanged(double arg1) {
  ui->widget->x_rotate = arg1;
}

void MainWindow::on_doubleSpinBox_rotate_y_valueChanged(double arg1) {
  ui->widget->y_rotate = arg1;
}

void MainWindow::on_doubleSpinBox_rotate_z_valueChanged(double arg1) {
  ui->widget->z_rotate = arg1;
}

void MainWindow::on_doubleSpinBox_scale_valueChanged(double arg1) {
  ui->widget->scale = arg1;
}

// fprintf(stderr, "\n");
// for(unsigned int i = 0; i < ui->widget->data_object->counter_vertexes*3; i++)
// {
//     fprintf(stderr, "%lf ", ui->widget->vertex_opengl[i]);
// }

// fprintf(stderr, "\n");
// for(unsigned int i = 0; i < ui->widget->data_object->counter_index*2; i++) {
//     fprintf(stderr, "%u ", ui->widget->facets_opengl[i]);
// }
