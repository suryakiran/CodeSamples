#include "json_writer.hxx"
#include <json/writer.h>
#include <iostream>
#include <typeinfo>

void
JsonWriter::writeJsonRoot(std::ostream& os, const Json::Value& root)
{
    Json::StyledStreamWriter writer;
    writer.write(os, root);
}

void
JsonWriter::toJson(const QString& var, Json::Value& root)
{
    root = var.toStdString();
}

void
JsonWriter::writeVariant (const QVariant& var, std::ostream& os)
{
    Json::Value root;
    toJson(var, root);
    writeJsonRoot(os, root);
}

void
JsonWriter::toJson (const QVariant& var, Json::Value& root)
{
    switch (var.type()) {
    case QVariant::StringList:
        for (auto i: var.toStringList()) {
            Json::Value item;
            toJson(i, item);
        }
    case QVariant::List:
        for (auto i: var.toList()) {
            Json::Value item;
            toJson(i, item);
            root.append(item);
        }
        break;
    case QVariant::Map:
        {
            QVariantMap map = var.toMap();
            for (auto iter = map.begin(); iter != map.end(); ++iter) {
                iter.value();
                Json::Value item;
                toJson(iter.value(), item);
                root[iter.key().toStdString()] = item;
            }
        }
        break;
    case QVariant::Double:
        root = Json::Value(var.toDouble());
        break;
    case QVariant::String:
        root = Json::Value(var.toString().toStdString());
        break;
    case QVariant::Int:
        root = Json::Value(var.toInt());
        break;
    default:
        break;
    }
}
