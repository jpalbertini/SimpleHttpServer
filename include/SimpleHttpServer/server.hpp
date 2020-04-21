#ifndef SIMPLEHTTPSERVER_SERVER
#define SIMPLEHTTPSERVER_SERVER

#include <memory>
#include <functional>
#include <optional>
#include <QSslConfiguration>

#include "SimpleHttpServer/defines.hpp"
#include "SimpleHttpServer/types.hpp"

class QAbstractSocket;
class QueryInformations;
namespace shs
{
    struct ServerImpl;
    class SIMPLEHTTPSERVER_EXPORT Server
    {
    public:
        Server();
        ~Server();
        void setBinding(int port, const QSslConfiguration& sslConfiguration = QSslConfiguration());

        bool start();
        bool stop();

        void attachOnGet(GetFuntion getCallback);

    private:
        void onStarted();
        void onStopped();
        void onNewConnection();
        void handleRequest(QAbstractSocket* device);

    private:
        QObject object_;
        std::unique_ptr<ServerImpl> pImpl;
    };
}

#endif //SIMPLEHTTPSERVER_SERVER