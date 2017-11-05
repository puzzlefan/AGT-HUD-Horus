 #include "headquater.h"

#include <../Netzwerk/server/server.h>
#include <../Netzwerk/User/User.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<user> xyz;

    headquater *Leitstelle = new headquater(&xyz);

    Server abc(&xyz,Leitstelle);

    return a.exec();
}
