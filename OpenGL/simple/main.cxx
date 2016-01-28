#include <QtGui/QGuiApplication>
#include "simple.hxx"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    SimpleWindow window;

    window.show();

    return app.exec();
}
