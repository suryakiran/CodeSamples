#include <cstd.h>
#include"Perl.h"

int main (int argc, char** argv)
{
  char* command_line [] = {"", "-e", "print \"Hello From C!\n\";"};
  perlInterp = perl_alloc();
  perl_construct (perlInterp);
  perl_parse (perlInterp, NULL, 3, command_line, (char **)NULL);
  perl_run (perlInterp);
  perl_destruct (perlInterp);
  perl_free (perlInterp);
  return 0;
}
