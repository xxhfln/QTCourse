#include "texteditor.h"
#include "findtext.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TextEditor w;
    w.show();
//    FindText f;
//    f.show();
    return a.exec();
}
