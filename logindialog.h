#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QAbstractButton>
#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();

private slots:
    void on_cancelBtn_clicked();

    void on_confirmBtn_clicked();

private:
    Ui::loginDialog *ui;
};

#endif // LOGINDIALOG_H
