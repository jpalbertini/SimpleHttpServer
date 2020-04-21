#ifndef SIMPLEHTTPSERVER_REQUEST_HANDLER
#define SIMPLEHTTPSERVER_REQUEST_HANDLER

#include <QByteArray>

#include "headershelper.hpp"

class QAbstractSocket;
namespace shs
{
    class RequestHandler
    {
    public:
        RequestHandler();
        bool parseRequest(QAbstractSocket* device);

        const HeadersHelper& getHeaders() const;

    private:
        HeadersHelper helper_;
    };
}

#endif //SIMPLEHTTPSERVER_REQUEST_HANDLER