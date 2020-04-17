#ifndef SIMPLEHTTPSERVER_SERVER_P
#define SIMPLEHTTPSERVER_SERVER_P

#include <memory>

#include <QTcpServer>
#include <QThread>
#include <QSslConfiguration>

#include "SimpleHttpServer/types.hpp"

namespace shs
{
    struct ServerImpl
    {
        std::unique_ptr<QTcpServer> currentServer_;
        QThread currentThread_;
        QSslConfiguration sslConfiguration_;
        int port_{ 0 };

        GetFuntion getFuntion_;
    };
}

#endif //SIMPLEHTTPSERVER_SERVER_P