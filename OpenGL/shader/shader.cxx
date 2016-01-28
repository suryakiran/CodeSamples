#include "shader.hxx"
#include <QtGui/QMatrix4x4>
#include <iostream>
using namespace std;

ShaderWindow::ShaderWindow (QWindow* parent)
    :OpenGLWindow(parent)
{
}

ShaderWindow::~ShaderWindow ()
{
    teardownGL();
}


void
ShaderWindow::initializeGL()
{
    OpenGLWindow::initializeGL();
    shaderProgram()->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    shaderProgram()->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
}

void
ShaderWindow::paintGL()
{
    cout << BOOST_CURRENT_FUNCTION << endl;
    OpenGLWindow::paintGL();
    static const GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};
    gl->glClearBufferfv(GL_COLOR, 0, red);
}

void
ShaderWindow::timedEventImp(QTimer* timer)
{
    cout << BOOST_CURRENT_FUNCTION << endl;
}
