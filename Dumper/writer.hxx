#ifndef writer_hxx_INCLUDED
#define writer_hxx_INCLUDED

#include <QtCore/QVariant>
#include <sstream>
#include "json_writer.hxx"
#include <boost/tti/has_type.hpp>
#include <boost/tti/has_member_function.hpp>
#include <boost/type_traits/has_operator.hpp>
#include <iostream>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/find_if.hpp>

namespace mpl = boost::mpl;

BOOST_TTI_HAS_TYPE(iterator)
BOOST_TTI_HAS_TYPE(const_iterator)
BOOST_TTI_HAS_MEMBER_FUNCTION(begin)
BOOST_TTI_HAS_MEMBER_FUNCTION(end)
BOOST_TTI_HAS_TYPE(mapped_type)

struct VariantType {};
struct SequenceType {};
struct MapType {};

template <typename Type>
struct Writer {};

template <>
struct Writer <VariantType>
{
    static void writeJson (const QVariant& var, std::ostream& os)
        {
            JsonWriter json;
            json.writeVariant(var, os);
        }

    static void writeYaml (const QVariant& var, std::ostream& os)
        {
        }
};

template <>
struct Writer <SequenceType>
{
    template <typename Sequence>
    static void writeJson (const Sequence& var, std::ostream& os)
        {
            JsonWriter json;
            json.writeSequence(var, os);
        }

    template <typename Sequence>
    static void writeYaml (const Sequence& var, std::ostream& os)
        {
        }
};

template <>
struct Writer <MapType>
{
    template <typename Sequence>
    static void writeJson (const Sequence& var, std::ostream& os)
        {
            JsonWriter json;
            json.writeMap(var, os);
        }

    template <typename Sequence>
    static void writeYaml (const Sequence& var, std::ostream& os)
        {
        }
};

template <typename Type>
struct CheckMap : public std::conditional<has_type_mapped_type<Type>::value,
                                          std::true_type,
                                          std::false_type>::type
{
    typedef MapType type;
};

template <typename Type>
struct CheckSequence
{
    static const bool value = has_type_const_iterator<Type>::value &&
        boost::mpl::and_<
        has_member_function_begin<typename Type::const_iterator (Type::*)() const>
        , has_member_function_end<typename Type::const_iterator (Type::*)() const>
        >::value;
    typedef SequenceType type;
};

template <typename Type>
struct CheckVariant
    : public std::conditional<std::is_convertible <Type, QVariant>::value,
                              std::true_type,
                              std::false_type>::type
{
    typedef VariantType type;
};

typedef boost::add_reference<std::ostream>::type StreamRef;

template <typename T>
struct IsStreamable : public std::integral_constant <bool, boost::has_left_shift<StreamRef, T, StreamRef>::value> {};

struct YamlWriter
{
public:
    YamlWriter () {}
    void write (const QVariant& data, std::ostream& os);
};

template <typename Type>
struct IfTrue
{
    static const bool value = Type::value;
};

template <typename Type>
struct GetVarType
{
    typedef mpl::vector<
        CheckVariant<Type>
        , CheckMap<Type>
        , CheckSequence<Type>
        > checks;

    typedef typename mpl::find_if <
        checks,
        IfTrue<mpl::_1>
        >::type iterator_type;

    typedef typename mpl::deref<iterator_type>::type FoundType;
    typedef typename FoundType::type type;
        
};
    
#endif /* writer_hxx_INCLUDED */
