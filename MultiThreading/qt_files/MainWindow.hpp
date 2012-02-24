#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ui_MainWindow.h"
#include <boost/lexical_cast.hpp> 
#include <boost/signals2.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
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
    void servicePost();

  private:
    boost::thread m_thread;
    boost::signals2::signal <void()> m_sig;
    boost::shared_ptr<boost::asio::io_service> m_service;
    boost::shared_ptr<boost::asio::io_service::work> m_work;
    bool m_endThread ;
    bool m_serviceStarted ;
};

#endif
