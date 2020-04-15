#include <QCoreApplication>
#include <QDebug>

#include <signal.h>

#include "QtHttpServer/server.hpp"


void myInterruptHandler(int signum) {
    qApp->exit();
}

int main(int argc, char* argv[])
{
    auto oldHandler = signal(SIGINT, myInterruptHandler);
    QCoreApplication a(argc, argv);

    qhs::Server server;
    server.setBinding(80);
    qInfo() << "Starting";
    server.start();
    qInfo() << "Ready";

    auto ret = a.exec();
    signal(SIGINT, oldHandler);

    qInfo() << "Stopping";
    server.stop();
    qInfo() << "Stopped";

    return ret;
}