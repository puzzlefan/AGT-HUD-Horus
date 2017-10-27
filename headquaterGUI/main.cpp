#include "headquater.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    headquater w;
    w.show();

    return a.exec();
}
