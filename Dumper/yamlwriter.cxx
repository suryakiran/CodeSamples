#include "yamlwriter.hxx"
#include <iostream>

YAML::Emitter& operator<< (YAML::Emitter& emitter, const QString& str)
{
    emitter << str.toStdString();
    return emitter;
}

template <typename Type>
YAML::Emitter& operator<< (YAML::Emitter& emitter, const QList<Type>& list)
{
    emitter << YAML::BeginSeq;
    for (auto i: list) {
        emitter << i;
    }
    emitter << YAML::EndSeq;
    return emitter;
}

template <typename KeyType, typename ValueType>
YAML::Emitter& operator<< (YAML::Emitter& emitter, const QMap<KeyType, ValueType>& map)
{
    emitter << YAML::BeginMap;
    for (auto iter = map.begin(); iter != map.end(); ++iter) {
        emitter << YAML::Key << iter.key() ;
        emitter << YAML::Value << iter.value();
    }
    emitter << YAML::EndMap;
    return emitter;
}

YAML::Emitter& operator<< (YAML::Emitter& emitter, const QVariant& variant)
{
    switch (variant.type()) {
    case QVariant::StringList:
        emitter << variant.toStringList();
        break;
    case QVariant::List:
        emitter << variant.toList();
        break;
    case QVariant::Map:
        emitter << variant.toMap();
        break;
    case QVariant::Double:
        emitter << variant.toDouble();
        break;
    case QVariant::String:
        emitter << variant.toString();
        break;
    case QVariant::Int:
        emitter << variant.toInt();
        break;
    case QVariant::UserType:
        break;
    default:
        break;
    }
    return emitter;
}

void
YamlWriter::writeVariant (const QVariant& var, std::ostream& os)
{
    YAML::Emitter emitter (os);
    emitter << var;
    emitter << YAML::Newline;
}
