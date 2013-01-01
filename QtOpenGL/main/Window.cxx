#include <Window.hxx>

Window::Window (QWidget* p_parent)
  : QMainWindow (p_parent)
{
  setupUi (this);
}
