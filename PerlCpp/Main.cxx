#include <iostream>
#include <Derived.h>
#include <CommandLineArgs.hxx>
using namespace std;

#include<vector>
#include<string>
#include <boost/program_options.hpp>
namespace po = boost::program_options;
using namespace po;

#include <EXTERN.h>
#include <perl.h>

#include <SV2Obj.hxx>

EXTERN_C void xs_init (pTHX);

static PerlInterpreter* my_perl;
string srcDir, binDir;

void init_perl()
{
}

void clean_perl()
{
  if (my_perl) {
    perl_destruct(my_perl);
    perl_free(my_perl);
    PERL_SYS_TERM();
  }
}

void
call_Perl_Base_Argument (Base* b)
{

  cout << "----- Perl Base Argument Test Begin -----" << endl;

  dSP;

  ENTER;
  SAVETMPS;
  PUSHMARK (SP);

  SV* sv = newSV(0);
  XPUSHs (sv_setref_pv(sv, "Test::Base", (void*)b));
  PUTBACK;

  int count = call_pv ("print_base", G_VOID);

  SPAGAIN;
  FREETMPS;
  LEAVE;
  PUTBACK;

  cout << "----- Perl Base Argument Test End -----" << endl;
  cout << endl;
}

void Test_Interface(void)
{
  cout << "----- Perl Interface Test Begin -----" << endl;

  dSP;

  ENTER;
  SAVETMPS;

  PUSHMARK(SP);
  PUTBACK;

  int count = call_pv ("test_interface", G_VOID);

  FREETMPS;
  LEAVE;

  cout << "----- Perl Interface Test End -----" << endl;
  cout << endl;
}

void
call_PerlSubs (void)
{
  vector<string> vs;
  vs.push_back ("Surya");
  vs.push_back ("Kiran");
  vs.push_back ("Gullapalli");

  dSP;

  ENTER;
  SAVETMPS;
  PUSHMARK (SP);

  AV* av = newAV();
  for (unsigned int i = 0; i < vs.size(); ++i) {
    av_push(av, newSVpv(vs[i].c_str(), 0));
  }

  XPUSHs (sv_2mortal(newRV_noinc((SV*)av)));
  PUTBACK;

  int count = call_pv ("array_fun", G_SCALAR);

#if 0
  if (count == 1) {
    SV* sv = POPs;
    Base* d(0);
    d = sv_object_cast<Base> (sv)();

    if (d) {
      cout << "-- ";
      d->virtualFun();
    }

    cout << "-- Returning a scalar" << endl;
  }
#endif

  SPAGAIN;

  PUTBACK;
  FREETMPS;
  LEAVE;
}

void parse_args (int argc, char** argv)
{
  options_description desc ("Allowed Options") ;
  desc.add_options()
    ("source-dir",  value <string>(), "Source Directory")
    ("binary-dir",  value <string>(), "Binary Directory")
    ;

  variables_map vm ;
  try
  {
    store (parse_command_line (argc, argv, desc), vm) ;
    notify (vm) ;
  }
  catch( std::exception& e)
  {
    cout << "Exception in reading command line variables: " << e.what() << endl ;
  }

  if (vm.count("source-dir")) {
    srcDir = vm["source-dir"].as<string>();
  }

  if (vm.count("binary-dir")) {
    binDir = vm["binary-dir"].as<string>();
  }
}

int main (int argc, char** argv, char** env)
{
  parse_args (argc, argv);
  PERL_SYS_INIT3(&argc, &argv, &env);
  my_perl = perl_alloc();
  perl_construct (my_perl);
  PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

  CommandLineArgs cla;
  fs::path p (binDir);
  p /= "test";
  cla.add(p);

  boost::shared_ptr<Base> b(new Derived);
  perl_parse (my_perl, xs_init, cla.count(), cla(), NULL); 
  //call_PerlSubs();
  call_Perl_Base_Argument(b->clone());
  Test_Interface();

  //Derived* d = new Derived();
  //cout << d->getDouble() << endl;
  //delete d;
  //

  clean_perl();
}
