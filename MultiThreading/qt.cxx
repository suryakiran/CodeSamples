#include "MainWindow.hpp"
#include "std.hxx"

int main (int argc, char** argv)
{
  QApplication app (argc, argv);
  MainWindow *mainw = new MainWindow;
  mainw->show();
  app.exec();
}
