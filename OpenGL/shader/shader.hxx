#ifndef SHADER_HXX_INCLUDED
#define SHADER_HXX_INCLUDED

#include <openglwindow.hpp>
#include <QElapsedTimer>

class ShaderWindow : public OpenGLWindow
{
    Q_OBJECT

public:
    ShaderWindow (QWindow* parent = nullptr);
    ~ShaderWindow();

    virtual void initializeGL() override;
    virtual void paintGL() override;

protected:
    virtual void timedEventImp(QTimer* timer) override;

private:
    GLuint mVao;
    std::vector<GLfloat> mBackground;
    QElapsedTimer mElapsedTimer;
};

#endif
