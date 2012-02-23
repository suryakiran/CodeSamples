#include "MainWindow.hpp"
#include "std.hxx"

int main (int argc, char** argv)
{
  QApplication::setAttribute (Qt::AA_X11InitThreads);
  QApplication app (argc, argv);
  MainWindow *mainw = new MainWindow;
  mainw->show();
  app.exec();
}
