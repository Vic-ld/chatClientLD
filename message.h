#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>
#include <vector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QMessageBox>
#include <QJsonArray>

using std::string;
using std::vector;

class Message
{
public:
    Message();
    void fromStr(const char *);
    string toJsonStr();

    int flag;
    string msg;
    string name;
    string target;
    int count;
    vector<string> names;
};

#endif // MESSAGE_H
