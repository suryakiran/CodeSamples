#include <TabFocusWindow.hxx>

TabFocusWindow::TabFocusWindow (QWidget* parent)
  : Window (parent)
{
}

bool
TabFocusWindow::eventFilter(QObject* obj, QEvent* event)
{
  return Window::eventFilter(obj, event);
}
                           
