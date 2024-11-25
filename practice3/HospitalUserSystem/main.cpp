#include "hospitalusersystem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HospitalUserSystem w;
    w.show();
    return a.exec();
}
