#include "headgui.h"

#include <../Netzwerk/client/client.h>
#include <../Netzwerk/User/User.h>
#include <../I2C/DaTa/DaTa.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DaTa *sensorData = new DaTa();
    user *networkUser = new user();


    HeadGUI *Person= new HeadGUI(networkUser, sensorData);

    Client *networkClient = new Client(networkUser, Person);

    return a.exec();
}
