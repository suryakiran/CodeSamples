#include <RestSampleWindow.hxx>
#include <SearchWidget.hxx>

RestSampleWindow::RestSampleWindow(QWidget* parent)
  :Window(parent)
{
  widget = new SearchWidget(this);
  setCentralWidget(widget);
}

bool
RestSampleWindow::eventFilter(QObject* object, QEvent* event)
{
  return Window::eventFilter(object, event);
}
