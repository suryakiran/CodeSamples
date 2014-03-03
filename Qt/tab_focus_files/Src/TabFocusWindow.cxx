#include <TabFocusWindow.hxx>
#include <TabWidget.hxx>

TabFocusWindow::TabFocusWindow (QWidget* parent)
  : Window (parent)
{
  TabWidget* tw = new TabWidget(this);
  setCentralWidget(tw);
}

bool
TabFocusWindow::eventFilter(QObject* obj, QEvent* event)
{
  return Window::eventFilter(obj, event);
}
                           
