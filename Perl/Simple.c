#include <stdio.h>
#include <EXTERN.h>
#include <perl.h>

static PerlInterpreter *my_perl;

int main (int argc, char** argv, char** env)
{
  char* command_line [] = {"", "-e", "print \"Hello From C!\n\";"};
  PERL_SYS_INIT3(&argc, &argv, &env);
  my_perl = perl_alloc();
  perl_construct (my_perl);
  PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
  perl_parse (my_perl, NULL, 3, command_line, (char **)NULL);
  perl_run (my_perl);
  perl_destruct (my_perl);
  perl_free (my_perl);
  return 0;
}
