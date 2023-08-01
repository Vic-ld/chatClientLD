#include "client.h"
#include "qapplication.h"
#include <winsock2.h>


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
        qApp->exit();
    }
}

void Client::sendPub(const QString &msg)
{
    m_msg.flag = 1;
    m_msg.name = m_name.toStdString();
    m_msg.msg = msg.toStdString();
    //m_tcpSocket->write(m_msg.toJsonStr().c_str());
    send(m_msg.toJsonStr().c_str());
}

void Client::sendPri(const QString &msg, const QString name)
{
    m_msg.flag = 2;
    m_msg.name = m_name.toStdString();
    m_msg.target = name.toStdString();
    m_msg.msg = msg.toStdString();

   // send(msg.toStdString().c_str());
    send(m_msg.toJsonStr().c_str());

}

void Client::send(const char *msg)
{
    int len = strlen(msg);
    char *buf = new char[len+sizeof(int)]();
    qDebug() << "send len:" << len;
    qDebug() << "send msg:" << msg;
    int netlen = htonl(len);
    memcpy(buf,&netlen,sizeof(int));
    memcpy(buf+sizeof(int),msg,len);
    qDebug() << "send buf:" << buf;
//    for(int i =0;i<len;i++)
//        qDebug() << "i = " << i << buf[i] ;
    m_tcpSocket->write(buf,len+sizeof(int));
   // m_tcpSocket->write(buf,len+sizeof(int));
    delete[] buf;
}

void Client::stopTcp()
{
    m_tcpSocket->disconnectFromHost();
}

void Client::setId()
{
    m_msg.name = m_name.toStdString();
    m_msg.flag = 0;
    send(m_msg.toJsonStr().c_str());
}

void Client::receivedData()
{
    while( m_tcpSocket->bytesAvailable())
    {
        int netlen;
        int ret = m_tcpSocket->read((char *)&netlen,sizeof(int));
        //qDebug() << __func__ << data;
        int len = ntohl(netlen);
        qDebug() << __func__ << len;

        char* data = new char[len+1];
        ret =  m_tcpSocket->read(data,len);
        data[len] = '\0';
        qDebug() << __func__ << data;
        m_msg.fromStr(data);
        handleMsg();
    }
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
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

        message = message + "昵称:" + QString::fromStdString(m_msg.name) + "   "
                + currentTimeStr +"\n"
                + QString::fromStdString(m_msg.msg);
        emit messageReceived(message);
        break;
    }

    case 2://私聊
    {
        QString message;
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString currentTimeStr = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
        message = message + "[私聊消息]昵称:" + QString::fromStdString(m_msg.name) + "   "
                + currentTimeStr+"\n"
                + QString::fromStdString(m_msg.msg);
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
