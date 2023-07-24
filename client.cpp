#include "client.h"



Client::Client(QObject *parent, QString addr, unsigned short port,QString name)
    : QObject(parent),
      m_name(name),
      m_addr(addr),
      m_port(port),
      m_tcpSocket(new QTcpSocket(this)),
      m_msg(Message())
{
    connect(m_tcpSocket,&QTcpSocket::connected,this,&Client::setId);
    connect(m_tcpSocket,&QTcpSocket::readyRead,this,&Client::receivedData);
    connect(m_tcpSocket, &QTcpSocket::disconnected, this, &Client::disconnectedFromServer);
}

void Client::connectToHost()
{
    m_tcpSocket->connectToHost(m_addr, m_port);
    if(m_tcpSocket->waitForConnected(3000))
    {
        QMessageBox::information(qobject_cast<QWidget*>(parent()), "提示", "连接成功", QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(qobject_cast<QWidget*>(parent()), "错误", "连接失败", QMessageBox::Ok);
    }
}

void Client::sendPub(const QString &msg)
{
    m_msg.flag = 1;
    m_msg.name = m_name.toStdString();
    m_msg.msg = msg.toStdString();
    m_tcpSocket->write(m_msg.toJsonStr().c_str());
}

void Client::sendPri(const QString &msg, const QString name)
{
    m_msg.flag = 2;
    m_msg.name = m_name.toStdString();
    m_msg.msg = msg.toStdString();
    m_msg.target = name.toStdString();
    m_tcpSocket->write(m_msg.toJsonStr().c_str());
}

void Client::stopTcp()
{
    m_tcpSocket->disconnectFromHost();
}

void Client::setId()
{
    m_msg.name = m_name.toStdString();
    m_msg.flag = 0;
    m_tcpSocket->write(m_msg.toJsonStr().c_str());
}

void Client::receivedData()
{
    QByteArray data = m_tcpSocket->readAll();
    m_msg.fromStr(data);
    handleMsg();
}

void Client::disconnectedFromServer()
{

}

unsigned short Client::port() const
{
    return m_port;
}

void Client::setPort(unsigned short newPort)
{
    m_port = newPort;
}

void Client::handleMsg()
{
    switch (m_msg.flag)
    {
    case 0:
        break;

    case 1://群发
    {
        QString message;
        message = message + "昵称:" + QString::fromStdString(m_msg.name) +"\n"
                +QString::fromStdString(m_msg.msg);
        emit messageReceived(message);
        break;
    }

    case 2://私聊
    {
        QString message;
        message = message + "[私聊消息]昵称:" + QString::fromStdString(m_msg.name) +"\n"
                +QString::fromStdString(m_msg.msg);
        emit messageReceived(message);
        break;
    }

    case 3:
    {
        break;
    }

    case 4:
    {
        QStringList memberList;
        for(auto &it:m_msg.names)
        {
            memberList<<QString::fromStdString(it);
        }
        emit roomInfoReceived(memberList,m_msg.count);
        break;
    }

    default:
        break;
    }
}

QString Client::addr() const
{
    return m_addr;
}

void Client::setAddr(const QString &newAddr)
{
    m_addr = newAddr;
}

QString Client::name() const
{
    return m_name;
}

void Client::setName(const QString &newName)
{
    m_name = newName;
}
