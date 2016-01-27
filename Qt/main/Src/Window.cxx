#include <Window.hxx>
#include <QScrollBar>
Window::Window (QWidget* p_parent)
  : QMainWindow (p_parent)
{
  setupUi (this);
  QScrollBar* sb = new QScrollBar (Qt::Vertical, this);
  Ui::MainWindow::treeWidget->addScrollBarWidget(sb,Qt::AlignBottom);
}
