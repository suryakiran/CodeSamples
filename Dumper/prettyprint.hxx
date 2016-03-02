#ifndef pretty_print_hxx_INCLUDED
#define pretty_print_hxx_INCLUDED

#include <ostream>
#include "writer.hxx"

namespace PrettyPrint {
    template <typename T>
    void print (const T& var, std::ostream& os = std::cout)
    {
        typedef typename GetVarType<T>::type VarType;
        Writer <VarType>::writeYaml(var, os);
    }
}

#endif /* dumper_hxx_INCLUDED */
