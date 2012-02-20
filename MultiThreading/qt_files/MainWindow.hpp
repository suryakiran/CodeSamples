#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ui_MainWindow.h"
#include <boost/lexical_cast.hpp> 
#include <boost/signals2.hpp>
#include <boost/phoenix.hpp>
#include <boost/thread.hpp>
#include "std.hxx"
namespace phx = boost::phoenix;
namespace pha = boost::phoenix::arg_names ;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
  Q_OBJECT

  public:
    MainWindow (QWidget* p_parent = 0);
    ~MainWindow();

Q_SIGNALS:
    void updateProgressBar();

  private Q_SLOTS:
    void buttonClick();
    void updateProgress();

  private:
    void createThread();

  private:
    boost::thread m_thread;
    boost::signals2::signal <void()> m_sig;
    bool m_endThread ;
};

#endif
