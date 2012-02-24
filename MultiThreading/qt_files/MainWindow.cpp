#include "MainWindow.hpp"

boost::mutex mutex;
int fraction (0);

MainWindow::MainWindow (QWidget* p_parent)
  : QMainWindow (p_parent), m_endThread (false), m_serviceStarted (false)
{
  setupUi (this);
  m_service.reset (new boost::asio::io_service);
  m_work.reset (new boost::asio::io_service::work(*m_service));
  resize (200, 100);
  connect (pushButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
  m_sig.connect (phx::bind (&MainWindow::servicePost, this));
  connect(this, SIGNAL(updateProgressBar()), this, SLOT(updateProgress()));
}

MainWindow::~MainWindow() 
{ 
  { 
    boost::mutex::scoped_lock lock (mutex);
    m_endThread = true;
  } 

  if(m_thread.joinable()) 
    m_thread.join(); 
} 

void
MainWindow::servicePost ()
{
  m_service->post(phx::bind(&MainWindow::updateProgress, this));
}

void 
MainWindow::createThread ()
{
  while(1) 
  { 
    boost::system_time timeout (boost::get_system_time() + boost::posix_time::milliseconds (80));
    boost::thread::sleep (timeout);
    //Q_EMIT updateProgressBar();
    m_sig();
    { 
      boost::mutex::scoped_lock lock (mutex);
      if(m_endThread)  
        return; 
    }
  } 
}

void 
MainWindow::updateProgress()
{
  boost::mutex::scoped_lock lock (mutex);
  ++fraction;
  cout << fmt("[%1%] Progress Fraction: %2%") % boost::this_thread::get_id() % fraction << endl;
  if (m_serviceStarted && (fraction >= 100)) {
    m_service->stop();
    m_endThread = true;
    m_serviceStarted = false;
  }
  progressBar->setValue (fraction);
}

void
MainWindow::buttonClick()
{
  m_thread = boost::thread (phx::bind (&MainWindow::createThread, this));
  m_serviceStarted = true;
  m_service->run();
  //label->setText (QString ("Value: %1").arg(progressBar->value()));
}
