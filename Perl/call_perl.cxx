#include "std.hxx"
#include <ParseArgs.hxx>
#include <boost/filesystem/path.hpp>

#include <EXTERN.h>
#include <perl.h>

typedef char* charp;
static PerlInterpreter* my_perl;

void
call_PerlSubs (void)
{
  dSP;

  ENTER;
  SAVETMPS;
  PUSHMARK (SP);

  XPUSHs (sv_2mortal(newSVpv("Surya.Kiran.Gullapalli", 0)));
  PUTBACK;

  int count = call_pv ("func_return_array", G_ARRAY);

  SPAGAIN;

  cout << "Number of items returned: " << count << endl;
  
  for (int i = 0; i < count; ++i) {
    cout << '\t' << POPp << endl;
  }

  PUTBACK;
  FREETMPS;
  LEAVE;
}

int main (int argc, char** argv, char** env)
{
  Args args = ParseArgs (argc, argv)();
  boost::filesystem::path p (args["cur_src_dir"]);
  p /= "call_perl_files/call_perl.pl";
  charp command_line[2] = {strdup(""), strdup("")};
  command_line[1] = strdup(p.make_preferred().string().c_str());
  
  PERL_SYS_INIT3(&argc, &argv, &env);
  my_perl = perl_alloc();
  perl_construct (my_perl);
  perl_parse (my_perl, NULL, 2, command_line, (char **)NULL);
  PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
  call_PerlSubs ();

  perl_destruct(my_perl);
  perl_free(my_perl);
  PERL_SYS_TERM();
  
}
