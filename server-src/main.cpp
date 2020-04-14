#include <QCoreApplication>
#include <QDebug>

#include "QtHttpServer/server.hpp"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    qhs::Server server;

    qDebug() << "Hello World";

    return a.exec();
}