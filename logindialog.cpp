#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
}

loginDialog::~loginDialog()
{
    delete ui;
}



void loginDialog::on_cancelBtn_clicked()
{
    qApp->exit();
}

void loginDialog::on_confirmBtn_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    this->hide();
    mainWindow->show();
}

