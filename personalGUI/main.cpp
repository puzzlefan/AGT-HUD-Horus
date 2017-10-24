#include "headgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HeadGUI Person;
    Person.show();

    return a.exec();
}
