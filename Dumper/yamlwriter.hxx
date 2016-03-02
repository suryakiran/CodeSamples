#ifndef yamlwriter_hxx_INCLUDED
#define yamlwriter_hxx_INCLUDED

#include <QtCore/QVariant>
#include <ostream>
#include <yaml-cpp/emitter.h>

struct YamlWriter
{
public:
    YamlWriter () {}
    
    void writeVariant (const QVariant& data, std::ostream& os);

    template <typename Sequence>
    void writeSequence (const Sequence& data, std::ostream& os) {
        YAML::Emitter emitter (os);
        emitter << YAML::Flow << YAML::BeginSeq;
        for (auto i: data) {
            emitter << i;
        }
        emitter << YAML::EndSeq << YAML::Newline;
    }

    template <typename MapType>
    void writeMap (const MapType& data, std::ostream& os) {
        YAML::Emitter emitter (os);
        emitter << YAML::Flow << YAML::BeginMap;
        for (auto i: data) {
            emitter << YAML::Key << i.first;
            emitter << YAML::Value << i.second;
        }
        emitter << YAML::EndMap << YAML::Newline ;
    }
};


#endif /* yamlwriter_hxx_INCLUDED */
