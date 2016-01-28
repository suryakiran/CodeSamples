#include <QtGui/QOpenGLWindow>
#include <QtGui/QOpenGLFunctions>
#include <boost/current_function.hpp>
#include <QtGui/QOpenGLFunctions_4_3_Core>
#include <memory>

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

//! [1]
class OpenGLWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWindow(QWindow *parent = 0);
    ~OpenGLWindow();


    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();
    virtual void teardownGL();

protected:
    std::unique_ptr<QOpenGLFunctions_4_3_Core> gl;
    void printContextInformation();
};
//! [1]

