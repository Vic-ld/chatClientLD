#ifndef PRIVATEDIALOG_H
#define PRIVATEDIALOG_H

#include <QDialog>

namespace Ui {
class PrivateDialog;
}

class PrivateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrivateDialog(QString name, QWidget *parent = nullptr);
    ~PrivateDialog();
signals:
    void privateMessage(QString msg,QString name);

private slots:
    void on_sendBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::PrivateDialog *ui;
    QString m_name;
};

#endif // PRIVATEDIALOG_H
