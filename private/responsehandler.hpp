#ifndef SIMPLEHTTPSERVER_RESPONSE_HANDLER
#define SIMPLEHTTPSERVER_RESPONSE_HANDLER

#include <QByteArray>

#include "headershelper.hpp"

namespace shs
{
    class RequestHandler;
    class ResponseHandler
    {
    public:
        ResponseHandler();

        void importRequest(const RequestHandler& request);

        HeadersHelper& getHeaders();

        QByteArray generateRawData(const QByteArray& content) const;

    private:
        HeadersHelper helper_;
    };
}

#endif //SIMPLEHTTPSERVER_RESPONSE_HANDLER