#ifndef GUARD_WINDOW_HPP_INCLUDED 
#define GUARD_WINDOW_HPP_INCLUDED 1 

#include <boost/noncopyable.hpp> 
#include <boost/thread.hpp>
#include <boost/signals2.hpp>
#include <gtkmm.h> 
#include "std.hxx"

class Window : public Gtk::Window, boost::noncopyable 
{ 
  public: 
    Window(); 
    virtual ~Window(); 
    void on_button_click(); 
    void thread_worker(); 
    void update_progress();

  private: 
    bool             m_end_thread; 
    Gtk::VBox        m_vbox; 
    Gtk::Button      m_button; 
    Gtk::Label       m_label; 
    Gtk::ProgressBar m_pbar; 
    Glib::Dispatcher m_dispatcher; 
    boost::thread m_thread;
    boost::signals2::signal <void()> m_sig;
}; 

#endif
