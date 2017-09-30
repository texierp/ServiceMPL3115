#include <QCoreApplication>
#include <QDebug>
#include "CServiceMPL3115.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    new CServiceMPL3115;

    return a.exec();
}
