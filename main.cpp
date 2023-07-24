#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int total = 4;
    std::vector<loginDialog> lg(total);
    for (int i = 0; i < total; ++i)
    {
        lg.at(i).show();
    }
    return a.exec();
}
