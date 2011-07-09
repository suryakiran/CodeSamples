#include <CommandLineArgs.hxx>
#include <cstdlib>
#include <cstring>

CommandLineArgs::CommandLineArgs()
{
}

CommandLineArgs::~CommandLineArgs()
{
  if (m_argv) {
    for (int i = 0; i < count()+1; ++i) {
      free(m_argv[i]);
    }

    free(m_argv);
  }
}

int
CommandLineArgs::count() const
{
  return static_cast<int>(m_args.size());
}

char**
CommandLineArgs::operator()()
{
  if (m_args.empty()) {
    return (char**)NULL;
  }

  int numArgs (count() + 1);

  m_argv = (char**)malloc (numArgs * sizeof(char*));

  m_argv[0] = (char*) malloc (sizeof(char));
  strncpy (m_argv[0], "\0", 1);

  for (int i = 1; i < numArgs; ++i) {
    const string& s (m_args[i-1]);
    m_argv[i] = (char*)malloc ((s.length() + 1)*sizeof(char));
    strncpy (m_argv[i], s.c_str(), s.length());
    m_argv[i][s.length()] = '\0';
  }

  return m_argv;
}
