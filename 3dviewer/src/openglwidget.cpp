#include "openglwidget.h"
#include <cmath>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void OpenGLWidget::initializeGL() {

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void OpenGLWidget::paintGL() {

  if (file_opened) {
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(Qt::black));
    setAutoFillBackground(true);
    setPalette(pal);

    glOrtho(-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertex_opengl);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(x_move, y_move, z_move);
    glRotated(x_rotate, 1.0, 0.0, 0.0);
    glRotated(y_rotate, 0.0, 1.0, 0.0);
    glRotated(z_rotate, 0.0, 0.0, 1.0);
    glScaled(scale, scale, scale);

    glDrawElements(GL_LINES, data_object->counter_index * 2, GL_UNSIGNED_INT,
                   facets_opengl);

    update();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}
