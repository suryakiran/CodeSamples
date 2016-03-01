#ifndef stream_hxx_INCLUDED
#define stream_hxx_INCLUDED

#include <sstream>
#include <string>
#include <utility>

template <typename Type>
struct Stream
{
    Stream (const Type& streamable)
        : mObj(streamable){}

    operator std::string () const {
        std::ostringstream os ;
        os << mObj;
        return os.str();
    }

private:
    const Type& mObj;
};

namespace StreamUtils {
    template <typename Type>
    std::string stream (const Type& val)
    {
        Stream<Type> strm(val);
        return strm;
    }
}


#endif /* stream_hxx_INCLUDED */
