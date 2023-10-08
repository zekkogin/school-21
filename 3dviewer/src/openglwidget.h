#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#define GL_SILENCE_DEPRECATION
#include <QKeyEvent>
#include <QtOpenGLWidgets/QtOpenGLWidgets>

extern "C" {
#include "s21_parser.h"
};

class OpenGLWidget : public QOpenGLWidget {
  Q_OBJECT
public:
  OpenGLWidget(QWidget *parent = nullptr);

  double scale = 1;
  // move
  double x_move = 0;
  double y_move = 0;
  double z_move = 0;
  // rotate
  double x_rotate = 0;
  double y_rotate = 0;
  double z_rotate = 0;

  // all data object file
  struct data *data_object;

  // temp structures for opengl
  double *vertex_opengl;
  unsigned int *facets_opengl;

  bool file_opened = false;

protected:
  /**
   * @brief Initiliaze window
   */
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  /**
   * @brief Draw lines, first: set points with glVertexPointer, after
   * glDrawElements. this function use (double*) array vertex_opengl and (uns
   * int*) array facets_opengl
   */
  void paintGL() override;
};

#endif // OPENGLWIDGET_H