#include <QCoreApplication>
#include <QDebug>

#include <signal.h>

#include "SimpleHttpServer/server.hpp"
#include "SimpleHttpServer/queryinformations.hpp"


void myInterruptHandler(int signum) {
    qApp->exit();
}

int main(int argc, char* argv[])
{
    auto oldHandler = signal(SIGINT, myInterruptHandler);
    QCoreApplication a(argc, argv);

    shs::Server server;
    server.setBinding(80);
    server.attachOnGet([](const shs::QueryInformations& query) -> shs::CallbackResponse {
        if (query.request == "/")
            return "<html><h1>Good</h1></html>";
        return shs::CallbackResponse();
    });

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