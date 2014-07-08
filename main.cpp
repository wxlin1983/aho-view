#include "ahoview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ahoview w;
    w.show();

    return a.exec();
}
