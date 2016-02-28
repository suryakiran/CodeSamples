#ifndef writer_hxx_INCLUDED
#define writer_hxx_INCLUDED

#include <QtCore/QVariant>
#include <sstream>
#include "json_writer.hxx"
#include <boost/tti/has_type.hpp>
#include <boost/tti/has_member_function.hpp>
#include <boost/type_traits/has_operator.hpp>
#include <iostream>

BOOST_TTI_HAS_TYPE(iterator)
BOOST_TTI_HAS_TYPE(const_iterator)
BOOST_TTI_HAS_MEMBER_FUNCTION(begin)
BOOST_TTI_HAS_MEMBER_FUNCTION(end)

struct VariantType {};
struct SequenceType {};

#define DEFINE_CONTAINER(name) \
    template <typename Type, typename Alloc> struct IsContainer <name<Type, Alloc>> : public std::true_type {}

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

template <typename Type>
struct IsContainer : public std::false_type {};

DEFINE_CONTAINER(std::vector);
DEFINE_CONTAINER(std::list);
DEFINE_CONTAINER(std::map);
DEFINE_CONTAINER(std::deque);
DEFINE_CONTAINER(std::set);
DEFINE_CONTAINER(std::multimap);
DEFINE_CONTAINER(std::multiset);
// DEFINE_CONTAINER(std::unordered_map);

template <typename Type>
struct IsSequence
{
    static const bool value = has_type_const_iterator<Type>::value &&
        boost::mpl::and_<
        has_member_function_begin<typename Type::const_iterator (Type::*)() const>
        , has_member_function_end<typename Type::const_iterator (Type::*)() const>
        >::value;
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
    
#endif /* writer_hxx_INCLUDED */
