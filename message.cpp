#include "message.h"

Message::Message():
    flag(10),
    msg("NULL"),
    name("NULL"),
    target("NULL"),
    count(0),
    names{}
{

}

void Message::fromStr(const char *str)
{
    QJsonDocument parsedJson = QJsonDocument::fromJson(str);

    if (!parsedJson.isNull() && parsedJson.isObject())
    {
        QJsonObject jsonObject = parsedJson.object();

        flag = jsonObject["flag"].toInt();

        msg = jsonObject["msg"].toString().toStdString();
        name = jsonObject["name"].toString().toStdString();
        target = jsonObject["target"].toString().toStdString();

        QJsonObject chatInfoObject = jsonObject["ChatInfo"].toObject();
        count = chatInfoObject["total"].toInt();

        QJsonArray namesArray = chatInfoObject["names"].toArray();
        names.clear();
        for (const QJsonValue &nameValue : namesArray)
        {
            names.push_back(nameValue.toString().toStdString());
        }

//
//        qDebug() << "flag:" << flag;
//        qDebug() << "msg:" << msg.c_str();
//        qDebug() << "name:" << name.c_str();
//        qDebug() << "target:" << target.c_str();
//        qDebug() << "count:" << count;
//        for(auto &it:names)
//            qDebug() << it.c_str();
    }
}

string Message::toJsonStr()
{
    QJsonObject chatInfoObj;
    chatInfoObj["total"] = count;

    QJsonArray namesArray;
    for (auto &name: names) {
        namesArray.append(name.c_str());
    }
    chatInfoObj["names"] = namesArray;

    QJsonObject jsonObj;
    jsonObj["flag"] = flag;
    jsonObj["msg"] = msg.c_str();
    jsonObj["name"] = name.c_str();
    jsonObj["target"] = target.c_str();
    jsonObj["ChatInfo"] = chatInfoObj;

    QJsonDocument jsonDoc(jsonObj);

    string str = jsonDoc.toJson(QJsonDocument::Compact).toStdString();
    fromStr(str.c_str());
    return str;
}
