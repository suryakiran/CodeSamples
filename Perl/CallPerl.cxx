#include "Perl.h"
#include <std.h>

void
call_PerlSubs (void)
{
  dSP;

  ENTER;
  SAVETMPS;
  PUSHMARK (SP);

  XPUSHs (sv_2mortal(newSVpv("Surya.Kiran.Gullapalli", 0)));
  PUTBACK;

  int count = call_pv ("func_return_array", G_SCALAR);

  SPAGAIN;

  cout << "Number of items returned: " << count << endl;
  
  for (int i = 0; i < count; ++i) {
    cout << '\t' << POPp << endl;
  }

  PUTBACK;
  FREETMPS;
  LEAVE;
}

int main (int argc, char** argv)
{
  char* command_line[2] = {"", "/home/suki/Projects/SourceArea/CodeSamples/Perl/CallPerl_files/CallPerl.pl"};
  
  perlInterp = perl_alloc();
  perl_construct (perlInterp);
  perl_parse (perlInterp, NULL, 3, command_line, (char **)NULL);
  call_PerlSubs ();

  perl_destruct(perlInterp);
  perl_free(perlInterp);
  
}
