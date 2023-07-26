#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_Client(new Client())
{
    ui->setupUi(this);
    ui->outputEdit->setReadOnly(true);
    ui->memList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->memList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->memList->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->memList, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(onMemListContextMenu(const QPoint&)));

    connect(m_Client,&Client::messageReceived,this,&MainWindow::appendMessage);
    connect(m_Client,&Client::roomInfoReceived,this,&MainWindow::updateRoomInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTCPConfig(QString addr, unsigned short port, QString id)
{
    m_Client->setAddr(addr);
    m_Client->setPort(port);
    m_Client->setName(id);
    m_Client->connectToHost();
}

void MainWindow::appendMessage(const QString &message)
{
    ui->outputEdit->append(message);
}

void MainWindow::updateRoomInfo(QStringList &memberList,int count)
{
    QString str = QString("总人数: %1").arg(count);
    memberList.prepend(str);
    QStringListModel *model = new QStringListModel(memberList);
    ui->memList->setModel(model);
    ui->memList->repaint();
}

void MainWindow::on_exitBtn_clicked()
{
    //qApp->exit();
    this->close();
    m_Client->stopTcp();
}

void MainWindow::on_sendBtn_clicked()
{
    m_Client->sendPub(ui->inputEdit->toPlainText());
//    m_Client->sendPub(ui->inputEdit->toPlainText());
//    m_Client->sendPub(ui->inputEdit->toPlainText());

    ui->inputEdit->clear();
}

void MainWindow::onMemListContextMenu(const QPoint &pos)
{
    QModelIndex index = ui->memList->indexAt(pos);
    if(index.isValid()&& index.row() != 0)
    {
        QMenu *listMenu = new QMenu(this);
        QAction *privateAct = new QAction("私聊",this);
        listMenu->addAction(privateAct);
        QAction* selectedItem = listMenu->exec(ui->memList->mapToGlobal(pos));
        if (selectedItem == privateAct)
        {
            PrivateDialog * priDlg = new PrivateDialog(index.data().toString(),this);
            connect(priDlg,&PrivateDialog::privateMessage,m_Client,&Client::sendPri);
            priDlg->show();
            qDebug() <<"开启私聊窗口，对象" << index.data() << "  " <<index.row();
        }
    }
}

