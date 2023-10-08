#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define GL_SILENCE_DEPRECATION
#include <QtOpenGL>

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <vector>

#include "openglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_browse_clicked();
    void on_doubleSpinBox_move_x_valueChanged(double arg1);
    void on_doubleSpinBox_move_y_valueChanged(double arg1);
    void on_doubleSpinBox_move_z_valueChanged(double arg1);
    void on_doubleSpinBox_rotate_y_valueChanged(double arg1);
    void on_doubleSpinBox_rotate_x_valueChanged(double arg1);
    void on_doubleSpinBox_rotate_z_valueChanged(double arg1);
    void on_doubleSpinBox_scale_valueChanged(double arg1);
private:
    Ui::MainWindow *ui;
    OpenGLWidget *openglwidget;
};
#endif // MAINWINDOW_H
