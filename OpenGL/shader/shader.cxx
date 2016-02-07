#include "shader.hxx"
#include <QtGui/QMatrix4x4>
#include <boost/assign.hpp>
#include <iostream>
using namespace std;
using namespace boost::assign;

ShaderWindow::ShaderWindow (QWindow* parent)
    :OpenGLWindow(parent)
{
    mBackground += 0.2f;
    mBackground += 0.2f;
    mBackground += 0.25f;
    mBackground += 0.8f;
    mElapsedTimer.start();
}

ShaderWindow::~ShaderWindow ()
{
    gl->glDeleteVertexArrays(1, &mVao);
    teardownGL();
}


void
ShaderWindow::initializeGL()
{
    OpenGLWindow::initializeGL();
    shaderProgram()->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    shaderProgram()->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    gl->glCreateVertexArrays(1, &mVao);
    gl->glBindVertexArray(mVao);
}

void
ShaderWindow::paintGL()
{
    cout << BOOST_CURRENT_FUNCTION << endl;
    OpenGLWindow::paintGL();
    context()->swapBuffers(context()->surface());
    // gl->glClearBufferfv(GL_COLOR, 0, &mBackground[0]);

    // shaderProgram()->bind();
    // gl->glPointSize(0.0001);
    // gl->glDrawArrays(GL_POINTS, 0, 1);
}

void
ShaderWindow::timedEventImp(QTimer* timer)
{
    size_t t = mElapsedTimer.elapsed();
    float ps = 0.0001 * t;

    const GLfloat color[] = { (float)sin (t) * 0.5f + 0.5f,
                              (float)cos (t) * 0.5f + 0.5f,
                              0.0f, 1.0f};
    
    gl->glClearBufferfv(GL_COLOR, 0, color);

    // cout << "Setting point size to " << ps << endl;
    update();
    // shaderProgram()->bind();
    // gl->glPointSize(ps);
    // gl->glDrawArrays(GL_POINTS, 0, 1);

    // cout << BOOST_CURRENT_FUNCTION << endl;
}
