#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject *parent = nullptr,QString addr = "127.0.0.1",
           unsigned short port = 9527,QString id = "test");
    void connectToHost();

protected slots:
    void setId();

private:
    QString m_name;
    QString m_addr;
    unsigned short m_port;
    QTcpSocket *m_tcpSocket;
    QJsonObject m_jsObject;
};

#endif // CLIENT_H
