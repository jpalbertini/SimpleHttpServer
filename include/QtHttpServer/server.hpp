#ifndef QTHTTPSERVER_SERVER
#define QTHTTPSERVER_SERVER

#include <memory>
#include <QSslConfiguration>

#include "QtHttpServer/defines.hpp"

namespace qhs
{
    struct ServerImpl;
    class QTHTTPSERVER_EXPORT Server
    {
    public:
        Server();
        ~Server();
        void setBinding(int port, const QSslConfiguration& sslConfiguration = QSslConfiguration());

        bool start();
        bool stop();

    private:
        void onStarted();
        void onStopped();
        void onNewConnection();

    private:
        QObject object_;
        std::unique_ptr<ServerImpl> pImpl;
    };
}

#endif //QTHTTPSERVER_SERVER