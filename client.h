#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QMessageBox>
#include <QJsonArray>
#include <QMenu>

#include "message.h"

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject *parent = nullptr,QString addr = "127.0.0.1",
           unsigned short port = 9527,QString id = "test111");
    void connectToHost();

    void sendPub(const QString &msg);
    void sendPri(const QString &msg,const QString name);

    void stopTcp();
    QString name() const;
    void setName(const QString &newName);

    QString addr() const;
    void setAddr(const QString &newAddr);

    unsigned short port() const;
    void setPort(unsigned short newPort);

    void handleMsg();

protected slots:
    void setId();
    void receivedData();
    void disconnectedFromServer();

signals:
    void messageReceived(const QString &message);
    void roomInfoReceived(QStringList &strList,int count);

private:
    QString m_name;
    QString m_addr;
    unsigned short m_port;
    QTcpSocket *m_tcpSocket;
    QJsonObject m_jsObject;
    Message m_msg;
};

#endif // CLIENT_H
