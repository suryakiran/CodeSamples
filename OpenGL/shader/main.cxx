#include <QtGui/QGuiApplication>
#include "shader.hxx"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    ShaderWindow window;

    window.show();

    return app.exec();
}
