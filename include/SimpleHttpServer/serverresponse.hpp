#ifndef SIMPLEHTTPSERVER_SERVER_RESPONSE
#define SIMPLEHTTPSERVER_SERVER_RESPONSE

#include <QByteArray>

#include "SimpleHttpServer/enums.hpp"

namespace shs
{
    struct ServerResponse
    {
        ServerResponse(const char* const data) : ServerResponse(QByteArray(data)) {}
        ServerResponse(const QByteArray& data = QByteArray())
            : ServerResponse(data.isEmpty() ? Enums::ResponseCode::NotFound : Enums::ResponseCode::OK, data)
        {}

        ServerResponse(Enums::ResponseCode responseCode, const QByteArray& data = QByteArray())
            : responseCode(responseCode)
            , responseData(data)
        {}

        Enums::ResponseCode responseCode = Enums::ResponseCode::InternalServerError;
        QByteArray responseData;
    };
}

#endif //SIMPLEHTTPSERVER_SERVER_RESPONSE