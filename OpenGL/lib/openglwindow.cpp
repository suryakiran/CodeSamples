#include "openglwindow.hpp"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QTimer>

#include <QtGui/QOpenGLShader>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <iostream>
using namespace std;

//! [1]
OpenGLWindow::OpenGLWindow(QWindow *parent)
    : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate, parent)
{
    setSurfaceType(QWindow::OpenGLSurface);
    gl.reset(new QOpenGLFunctions_4_5_Core);
    
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(4,5);
 
    // Set the window up
    setFormat(format);
    resize(QSize(800, 600));

    m_timer = new QTimer(this);
    connect (m_timer, SIGNAL (timeout()), this, SLOT(timedEvent()));

    m_shaderProgram = new QOpenGLShaderProgram(this);
}

OpenGLWindow::~OpenGLWindow()
{
    m_timer->stop();
}

void
OpenGLWindow::timedEvent()
{
    timedEventImp(m_timer);
}

void
OpenGLWindow::timedEventImp(QTimer* timer)
{
}

void
OpenGLWindow::initializeGL()
{
    
    initializeOpenGLFunctions();
    printContextInformation();
    gl->initializeOpenGLFunctions();
}

void
OpenGLWindow::paintGL()
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    if (hasShaders()) {
        m_shaderProgram->bind();
    }
    m_timer->start(1000);
}

void
OpenGLWindow::resizeGL(int width, int height)
{
    
    (void)width;
    (void)height;
}

void
OpenGLWindow::teardownGL()
{
    
}

void
OpenGLWindow::printContextInformation()
{
    QString glType;
    QString glVersion;
    QString glProfile;
 
    // Get Version Information
    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

 
    // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch (format().profile())
    {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
    }
#undef CASE
 
    // qPrintable() will print our QString w/o quotes around it.
    qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}

void
OpenGLWindow::addShaderToProgram(QOpenGLShader* shader)
{
    m_shaderProgram->addShader(shader);
}
