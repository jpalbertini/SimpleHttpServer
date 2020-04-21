#ifndef SIMPLEHTTPSERVER_QUERY_INFORMATIONS
#define SIMPLEHTTPSERVER_QUERY_INFORMATIONS

#include <QString>

namespace shs
{
    struct QueryInformations
    {
        QString request;
        QVector<QByteArray> headers;
    };
}

#endif //SIMPLEHTTPSERVER_QUERY_INFORMATIONS