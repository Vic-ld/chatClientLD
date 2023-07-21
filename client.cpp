#include "client.h"

Client::Client(QObject *parent, QString addr, unsigned short port,QString name)
    : QObject(parent),
      m_name(name),
      m_addr(addr),
      m_port(port),
      m_tcpSocket(new QTcpSocket(this))
{
    connect(m_tcpSocket,&QTcpSocket::connected,this,&Client::setId);
}

void Client::connectToHost()
{
    m_tcpSocket->connectToHost(m_addr, m_port);
}

void Client::setId()
{
    m_tcpSocket->write("test");
    m_tcpSocket->flush();
}
