#ifndef QTHTTPSERVER_SERVER_P
#define QTHTTPSERVER_SERVER_P

#include <memory>
#include <QTcpServer>
#include <QThread>
#include <QSslConfiguration>

#include "QtHttpServer/defines.hpp"

namespace qhs
{
    struct ServerImpl
    {
        std::unique_ptr<QTcpServer> currentServer_;
        QThread currentThread_;
        QSslConfiguration sslConfiguration_;
        int port_{ 0 };
    };
}

#endif //QTHTTPSERVER_SERVER_P