#ifndef SIMPLE_HXX_INCLUDED
#define SIMPLE_HXX_INCLUDED

#include <openglwindow.hpp>

class SimpleWindow : public OpenGLWindow
{
    Q_OBJECT

public:
    SimpleWindow (QWindow* parent = nullptr);
    ~SimpleWindow();

    virtual void initializeGL() override;
    virtual void paintGL() override;
};

#endif
