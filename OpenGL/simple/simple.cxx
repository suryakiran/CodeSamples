#include "simple.hxx"
#include <QtGui/QMatrix4x4>
#include <iostream>
using namespace std;

SimpleWindow::SimpleWindow (QWindow* parent)
    :OpenGLWindow(parent)
{
}

SimpleWindow::~SimpleWindow ()
{
    teardownGL();
}


void
SimpleWindow::initializeGL()
{
    OpenGLWindow::initializeGL();
}

void
SimpleWindow::paintGL()
{
    OpenGLWindow::paintGL();
    static const GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};
    gl->glClearBufferfv(GL_COLOR, 0, red);
}
