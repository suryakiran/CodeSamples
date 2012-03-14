#include <boost/lexical_cast.hpp> 
#include <boost/phoenix.hpp>
#include "Window.hpp" 

namespace phx = boost::phoenix;
namespace pha = boost::phoenix::arg_names ;

boost::mutex mutex;
int fraction (0);

Window::Window() 
  : m_end_thread(false), m_vbox(false,10),    
  m_button(Glib::locale_to_utf8("Click to count"))
{ 
  add(m_vbox); 

  cout << fmt("Main Thread: %1%") % boost::this_thread::get_id() << endl;
  m_vbox.set_border_width(10); 

  m_vbox.pack_start(m_label);  
  m_vbox.pack_start(m_pbar);   
  m_vbox.pack_start(m_button); 

  m_pbar.set_pulse_step(0.01f); 
  m_pbar.set_show_text();
  m_button.signal_clicked().connect(sigc::mem_fun(*this,&Window::on_button_click)); 
  m_sig.connect (phx::bind (&Window::update_progress, this));
  m_thread = boost::thread (phx::bind (&Window::thread_worker, this));
  show_all(); 
} 

void Window::update_progress()
{
  double frac ((++fraction)/100.0);
  if (frac >= 1.0) {
    boost::mutex::scoped_lock lock (mutex);
    m_end_thread = true;
  }
  m_pbar.set_fraction(frac);
}

Window::~Window() 
{ 
  { 
    boost::mutex::scoped_lock lock (mutex);
    if(m_end_thread)       
      m_end_thread = true;
  } 
  if(m_thread.joinable()) 
    m_thread.join(); 
} 

void Window::on_button_click() 
{ 
  static unsigned long count_clicked = 0; 
  m_label.set_text(boost::lexical_cast<Glib::ustring>(count_clicked++)); 
} 

void Window::thread_worker() 
{ 
  cout << fmt("Worker Thread: %1%") % boost::this_thread::get_id() << endl;
  while(1) 
  { 
    Glib::usleep(50000);  
    m_sig();
    //m_dispatcher();       
    { 
      boost::mutex::scoped_lock lock (mutex);
      if(m_end_thread)  
        return; 
    }
  } 
}
