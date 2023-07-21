#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginDialog lg;
    lg.show();
    return a.exec();
}
