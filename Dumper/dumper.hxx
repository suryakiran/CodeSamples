#ifndef dumper_hxx_INCLUDED
#define dumper_hxx_INCLUDED

#include <ostream>
#include <string>
#include <typeinfo>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/eval_if.hpp>

namespace mpl = boost::mpl;

#include "writer.hxx"
template <typename T>
class Dumper
{
public:
    Dumper (const T& var)
        :mVar(var)
    {
    }

    void dump (std::ostream& os = std::cout)
    {
        JsonWriter jd;
        // jd.write (mVar, os);
    }

private:
    const T& mVar;
};

namespace DumpUtils {
    template <typename T>
    void dump (const T& var, std::ostream& os = std::cout)
    {
        typedef typename GetVarType<T>::type VarType;
        Writer <VarType>::writeJson(var, os);
        // typedef typename mpl::eval_if <
        //     std::is_convertible<T, QVariant>,
        //     mpl::identity<VariantType>,
        //     mpl::identity<SequenceType>
        //     >::type VarType;
        // Writer <VarType>::writeJson(var, os);
    }
}

#endif /* dumper_hxx_INCLUDED */
