#ifndef json_writer_hxx_INCLUDED
#define json_writer_hxx_INCLUDED

#include <json/value.h>
#include <QtCore/QVariant>
#include <iostream>
#include "stream.hxx"

struct JsonWriter
{
public:
    JsonWriter (){}

    void writeVariant (const QVariant& data, std::ostream& os);

    template <typename Sequence>
    void writeSequence (const Sequence& data, std::ostream& os) {
        Json::Value root;
        for (auto i: data) {
            root.append(Json::Value(i));
        }
        writeJsonRoot(os, root);
    }

    template <typename MapType>
    void
    writeMap (const MapType& data, std::ostream& os) {
        Json::Value root;
        for (auto i: data) {
            root [StreamUtils::stream(i.first)] = Json::Value(i.second) ;
        }
        writeJsonRoot(os, root);
    }
    
private:
    void writeJsonRoot(std::ostream& os, const Json::Value& root);
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
