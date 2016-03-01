#ifndef pretty_print_hxx_INCLUDED
#define pretty_print_hxx_INCLUDED

#include <ostream>
#include <string>
#include <typeinfo>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/eval_if.hpp>

namespace mpl = boost::mpl;

#include "writer.hxx"

namespace PrettyPrint {
    template <typename T>
    void print (const T& var, std::ostream& os = std::cout)
    {
        typedef typename GetVarType<T>::type VarType;
        Writer <VarType>::writeJson(var, os);
    }
}

#endif /* dumper_hxx_INCLUDED */
