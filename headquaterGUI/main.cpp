#include "headquater.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    headquater *Leitstelle = new headquater;

    return a.exec();
}
