#include "Window.hpp"
#include "std.hxx"

int main(int argc, char**argv) 
{ 
  Gtk::Main main_obj(argc,argv); 
  Window window_obj; 
  main_obj.run(window_obj); 
  return EXIT_SUCCESS;   
}
