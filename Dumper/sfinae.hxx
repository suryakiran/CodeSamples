#ifndef sfinae_hxx_INCLUDED
#define sfinae_hxx_INCLUDED

struct sfinae
{
    using yes = char; // sizeof(yes) == 1;
    using no = yes[2];// sizeof(no) == 2;
};

template <typename T>
struct has_const_iterator : public sfinae
{
private:
    template <typename C> static yes& test(typename C::const_iterator*);
    template <typename C> static no& test(...);
public:
    static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
    using type = T;
};

template <typename T>
struct has_begin : public sfinae
{
private:
    template <typename C> static yes& test(typename C::begin*);
    template <typename C> static no& test(...);
public:
    static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
    using type = T;
};

template <typename T>
struct has_end : public sfinae
{
private:
    template <typename C> static yes& test(typename C::end*);
    template <typename C> static no& test(...);
public:
    static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
    using type = T;
};

#endif /* sfinae_hxx_INCLUDED */
