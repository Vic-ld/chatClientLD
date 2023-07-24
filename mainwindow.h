#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QDialog>
#include <QHostAddress>
#include "client.h"
#include "message.h"
#include "privatedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTCPConfig(QString addr, unsigned short port, QString id);

private slots:
    void appendMessage(const QString &message);
    void updateRoomInfo(QStringList  &memberList,int count);
    void on_exitBtn_clicked();
    void on_sendBtn_clicked();
    void onMemListContextMenu(const QPoint&);
private:
    Ui::MainWindow *ui;
    QString m_sUserName;
    QHostAddress m_ServerAddr;
    unsigned short m_ServerPort;
    Client *m_Client;
};
#endif // MAINWINDOW_H
