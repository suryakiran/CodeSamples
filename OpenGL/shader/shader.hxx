#ifndef SHADER_HXX_INCLUDED
#define SHADER_HXX_INCLUDED

#include <openglwindow.hpp>

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
};

#endif
