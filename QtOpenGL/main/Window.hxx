#ifndef WINDOW_HXX
#define WINDOW_HXX

#include "ui_MainWindow.h"

class Window : public QMainWindow, Ui::MainWindow
{
  Q_OBJECT

  public:
    Window (QWidget* p_parent = 0);

  private:
};

#endif
