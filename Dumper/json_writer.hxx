#ifndef json_writer_hxx_INCLUDED
#define json_writer_hxx_INCLUDED

#include <json/value.h>
#include <QtCore/QVariant>
#include <iostream>
#include <sstream>

struct JsonWriter
{
public:
    JsonWriter (){}

    void write (const QVariant& data, std::ostream& os);
    void writeVariant (const QVariant& data, std::ostream& os);

    template <typename Sequence>
    void writeSequence (const Sequence& data, std::ostream& os) {
        std::cout << "Writing List" << std::endl;
    }
private:
    void toJson (const QVariant& var, Json::Value& root);
    void toJson (const QString& var, Json::Value& root);

    template <typename T>
    void toJson(const T& var, Json::Value& root) {
        std::ostringstream os;
        os << var;
        root = Json::Value(os.str());
    }
};


#endif /* json_writer_hxx_INCLUDED */
