#include <QtGui/QOpenGLWindow>
#include <QtGui/QOpenGLFunctions>
#include <boost/current_function.hpp>
#include <QtGui/QOpenGLFunctions_4_3_Core>
#include <QtGui/QOpenGLShaderProgram>
#include <memory>

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
class QTimer;
class QOpenGLShader;
QT_END_NAMESPACE

//! [1]
class OpenGLWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWindow(QWindow *parent = 0);
    ~OpenGLWindow();

    void addShaderToProgram(QOpenGLShader* shader);

    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();
    virtual void teardownGL();

    bool hasShaders() {
        return m_shaderProgram != nullptr;
    }

protected:
    QOpenGLShaderProgram* shaderProgram() {
        return m_shaderProgram;
    }

    const QOpenGLShaderProgram* shaderProgram() const {
        return m_shaderProgram;
    }
            

protected:
    std::unique_ptr<QOpenGLFunctions_4_3_Core> gl;
    void printContextInformation();
    QTimer* m_timer;
    QOpenGLShaderProgram* m_shaderProgram = nullptr;

protected:
    virtual void timedEventImp(QTimer* timer);

private Q_SLOTS:
    void timedEvent();

private:
    bool m_shaderAdded = false;
    
};
//! [1]

