#ifndef SIMPLEHTTPSERVER_HEADERS_HELPER
#define SIMPLEHTTPSERVER_HEADERS_HELPER

#include <QByteArray>
#include <QVersionNumber>

#include "SimpleHttpServer/enums.hpp"
#include "SimpleHttpServer/queryinformations.hpp"

namespace shs
{
    using HeaderName = QByteArray;
    class HeadersHelper
    {
    public:
        HeadersHelper(const QByteArray& rawData = QByteArray());

        void parse(const QByteArray& rawData);

        Enums::RequestVerb getVerb() const;

        void setCode(Enums::ResponseCode verb);

        const QueryInformations& getQueryInformations() const;
        void setQueryInformations(const QueryInformations& queryInformations);

        const QByteArray& getProtocol() const;
        void setProtocol(const QByteArray& protocol);

        const QVersionNumber& getProtocolVersion() const;
        void setProtocolVersion(const QVersionNumber& protocolVersion);

        const QVector<QByteArray>& getHeaders() const;

        QByteArray generateRawData(std::uint64_t contentSize) const;

    private:
        Enums::RequestVerb verb_ = Enums::RequestVerb::Unknown;
        Enums::ResponseCode code_ = Enums::ResponseCode::Unknown;
        QueryInformations query_;
        QByteArray protocol_;
        QVersionNumber protocolVersion_;
    };
}

#endif //SIMPLEHTTPSERVER_HEADERS_HELPER