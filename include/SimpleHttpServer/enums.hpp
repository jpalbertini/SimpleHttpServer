#ifndef SIMPLEHTTPSERVER_ENUMS
#define SIMPLEHTTPSERVER_ENUMS

#include <QMetaEnum>

namespace shs
{
    class Enums
    {
        Q_GADGET
    public:
        enum class RequestVerb
        {
            Unknown,
            GET,
            HEAD,
            POST,
            OPTIONS,
            CONNECT,
            TRACE,
            PUT,
            PATCH,
            DELETE,
        };
        Q_ENUM(RequestVerb)

        static QString requestVerbToString(RequestVerb verb)
        {
            return QString(QMetaEnum::fromType<RequestVerb>().valueToKey(int(verb)));
        }

        static RequestVerb stringToRequestVerb(const char* key)
        {
            return RequestVerb(QMetaEnum::fromType<RequestVerb>().keyToValue(key));
        }

        enum class ResponseCode
        {
            Unknown,

            OK = 200,
            
            BadRequest = 400,
            Unauthorized = 401,
            NotFound = 404,

            InternalServerError = 500,
            NotImplemented = 501,
            BadGateway = 502,
            ServiceUnavailable = 503,
            GatewayTimeout = 504,
            HTTPVersionNotSupported = 505,
        };
        Q_ENUM(ResponseCode)

        static QString responseCodeToString(ResponseCode code)
        {
            return QString(QMetaEnum::fromType<ResponseCode>().valueToKey(int(code)));
        }

        static ResponseCode stringToResponseCode(const char* key)
        {
            return ResponseCode(QMetaEnum::fromType<ResponseCode>().keyToValue(key));
        }
    };
}

#endif //SIMPLEHTTPSERVER_ENUMS