#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGLWidget>
#include <QWidget>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
class GlWidget : public QGLWidget
{
Q_OBJECT
public:
GlWidget(QWidget *parent = 0);
~GlWidget();
QSize sizeHint() const;
protected:
void initializeGL();
void resizeGL(int width, int height);
void paintGL();
private:
QMatrix4x4 pMatrix;
QGLShaderProgram shaderProgram;
QVector<QVector3D> vertices;
};
#endif // MAINWINDOW_H
