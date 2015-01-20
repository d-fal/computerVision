#ifndef GLWIDGET_H
#define GLWIDGET_H
#include "mainwindow.h"
#include <glwidget.h>
#include <QGLWidget>
#include <QTimer>
#include <QtOpenGL>


#include <iostream>
//#include "GL/glut.h"
using namespace std;
QT_FORWARD_DECLARE_CLASS(QGLShaderProgram);
class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();

    void resizeGL(int w , int h);
    static float width;
    void rePaint(float h, float dx, float dy, float dz, float r, float g, float b, QString txt);

    QGLShaderProgram *program;
private:
    QTimer timer;
     GLuint textures[6];

public slots:
    void paintGL();

private:
    QMatrix4x4 pMatrix;
    QGLShaderProgram shaderProgram;
    QVector<QVector3D> vertices;
};

#endif // GLWIDGET_H
