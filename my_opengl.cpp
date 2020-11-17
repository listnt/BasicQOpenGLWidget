#include "my_opengl.h"

my_opengl::my_opengl(QWidget *parent):QOpenGLWidget(parent){}

void my_opengl::setVector(QVector<Particle> *vec)
{
    this->ptc=vec;
}

void my_opengl::initializeGL()
{
    f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0f,0.0f,0.0f,1);
    f->glEnable(GL_POINT_SMOOTH);
    glPointSize(2.f);
    glMatrixMode(GL_PROJECTION);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(25);


}
void my_opengl::resizeGL(int w, int h)
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
}
void my_opengl::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glOrtho(0, width(), 0, height(), 0, 1);


    glBegin(GL_POINTS);
    glColor4f(0.2f, 0.6f, 1.0f, 1);
        glBegin(GL_POINTS);
        for (auto &p : *ptc)
            glVertex3f(p.x.x(), p.x.y(),0.0f);
        glEnd();
    glEnd();

    alpha++;
    glFlush();
}
