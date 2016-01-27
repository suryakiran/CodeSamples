#include <std.hxx>
#include <qt.hxx>
// #include <QCleanlooksStyle>

#include <Window.hxx>

int main (int argc, char** argv)
{
  QApplication app (argc, argv);
  // app.setStyle(new QCleanlooksStyle);

  Window* w = new Window;
  w->show();
  // qApp->installEventFilter(w);

  app.exec();
}
