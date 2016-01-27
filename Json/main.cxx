#include <iostream>
#include <json/value.h>
#include <json/reader.h>
#include <boost/bind.hpp>
using namespace std;

template <class T> struct Is {};
template <class T> struct To {};

#define CHECK_TYPE_CONVERT(type, isTypeFunction, asTypeFunction)        \
    template <>                                                         \
    struct Is<type> {                                                   \
        Is (const Json::Value& value)                                   \
            : mValue(value) {}                                          \
                                                                        \
        bool operator ()()                                              \
        {                                                               \
            return mValue.isTypeFunction();                             \
        }                                                               \
                                                                        \
    private:                                                            \
    const Json::Value& mValue;                                          \
    };                                                                  \
                                                                        \
    template <>                                                         \
    struct To <type> {                                                  \
        To (const Json::Value& value)                                   \
            : mValue(value) {}                                          \
                                                                        \
        type operator ()()                                              \
        {                                                               \
            return mValue.asTypeFunction();                             \
        }                                                               \
                                                                        \
    private:                                                            \
    const Json::Value& mValue;                                          \
    }

CHECK_TYPE_CONVERT(int, isInt, asInt);
CHECK_TYPE_CONVERT(string, isString, asString);
CHECK_TYPE_CONVERT(double, isDouble, asDouble);
CHECK_TYPE_CONVERT(float, isDouble, asFloat);

class ValueVector
{
public:
    ValueVector (const Json::Value& value)
        : mValue(value) {}

    template <class T>
    operator std::vector<T> ()
    {
        using ReturnType = std::vector<T>;
        ReturnType rv;
        if (!mValue.isArray()) {
            return rv;
        }

        Json::Value::ArrayIndex numItems = mValue.size();
        for (Json::Value::ArrayIndex idx = 0; idx < numItems; ++idx) {
            Json::Value value = mValue[idx];
            if (!Is<T>(value)()) {
                return ReturnType();
            }
            rv.push_back (To<T>(value)());
        }

        return rv;
    }

private:
    const Json::Value& mValue;
};

int main (void)
{
    Json::Value root;
    Json::Reader reader;
    reader.parse ("[1.01,2.01,3.01,4.01,5.01]", root);
    std::vector<float> vi = ValueVector (root) ;
    for(auto i: vi) {
        cout << i << endl;
    }
    return 0;
}
