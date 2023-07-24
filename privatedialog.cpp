#include "privatedialog.h"
#include "ui_privatedialog.h"

PrivateDialog::PrivateDialog(QString name,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrivateDialog),
    m_name(name)
{
    ui->setupUi(this);
}

PrivateDialog::~PrivateDialog()
{
    delete ui;
}

void PrivateDialog::on_sendBtn_clicked()
{
    emit privateMessage(ui->inputEdit->toPlainText(),m_name);
    close();
}


void PrivateDialog::on_cancelBtn_clicked()
{
    close();
}

