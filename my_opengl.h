#ifndef MY_OPENGL_H
#define MY_OPENGL_H
#include <QtOpenGL>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QOpenGLFunctions>

class my_opengl : public QOpenGLWidget
{
public:
    my_opengl(QWidget *parent);
protected:
    int alpha=0;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;

    QOpenGLShaderProgram *m_program = nullptr;
    QOpenGLFunctions *f;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


};

#endif // MY_OPENGL_H
