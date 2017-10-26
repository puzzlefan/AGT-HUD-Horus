#include "headgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HeadGUI *Person = new HeadGUI();

    return a.exec();// what does it do?!%
}
