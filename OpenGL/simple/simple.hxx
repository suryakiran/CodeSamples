#ifndef SIMPLE_HXX_INCLUDED
#define SIMPLE_HXX_INCLUDED

#include <openglwindow.hpp>

class SimpleWindow : public OpenGLWindow
{
    Q_OBJECT

public:
    SimpleWindow ();
    ~SimpleWindow();

    void initialize() override;
    void render() override;
};

#endif
