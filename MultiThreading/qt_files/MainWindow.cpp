#include "MainWindow.hpp"

boost::mutex mutex;
int fraction (0);

MainWindow::MainWindow (QWidget* p_parent)
  : QMainWindow (p_parent), m_endThread (false)
{
  setupUi (this);
  resize (200, 100);
  connect (pushButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
  m_sig.connect (phx::bind (&MainWindow::updateProgress, this));
  connect(this, SIGNAL(updateProgressBar()), this, SLOT(updateProgress()));
  m_thread = boost::thread (phx::bind (&MainWindow::createThread, this));
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
MainWindow::createThread ()
{
  while(1) 
  { 
    boost::system_time timeout (boost::get_system_time() + boost::posix_time::milliseconds (800));
    boost::thread::sleep (timeout);
    Q_EMIT updateProgressBar();
    //m_sig();
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
  if (++fraction >= 100) {
    boost::mutex::scoped_lock lock (mutex);
    m_endThread = true;
  }
  progressBar->setValue (fraction);
}

void
MainWindow::buttonClick()
{
  label->setText (QString ("Value: %1").arg(progressBar->value()));
}
