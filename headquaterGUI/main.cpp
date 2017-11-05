 #include "headquater.h"

#include <../Netzwerk/server/server.h>
#include <../Netzwerk/User/User.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    headquater *Leitstelle = new headquater;

    std::vector<user> xyz;
    Server abc(&xyz,Leitstelle);

    return a.exec();
}
