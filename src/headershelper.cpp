#include "headershelper.hpp"

#include <QString>

namespace shs
{
    HeadersHelper::HeadersHelper(const QByteArray& rawData)
    {
        parse(rawData);
    }

    void HeadersHelper::parse(const QByteArray& rawData)
    {
        int previous = 0;
        for (int i = 0; i < rawData.size() - 2; i++)
        {
            if (rawData[i] == '\r' && rawData[i + 1] == '\n')
            {
                query_.headers.append(QByteArray(rawData.constData() + previous, i - previous));
                i++;
                previous = i + 1;
            }
        }

        if (query_.headers.isEmpty())
            return;

        auto first = query_.headers.takeFirst();
        auto splits = first.split(' ');
        if (splits.size() > 0)
        {
            verb_ = Enums::stringToRequestVerb(splits[0].constData());
            if (splits.size() > 1)
            {
                query_.request = splits[1];

                if (splits.size() > 2)
                {
                    auto protocols = splits[2].split('/');
                    if (protocols.size() == 2)
                    {
                        protocol_ = protocols[0];
                        protocolVersion_ = QVersionNumber::fromString(protocols[1]);
                    }
                }
            }
        }
    }

    Enums::RequestVerb HeadersHelper::getVerb() const
    {
        return verb_;
    }

    void HeadersHelper::setCode(Enums::ResponseCode code)
    {
        code_ = code;
    }

    const QueryInformations& HeadersHelper::getQueryInformations() const
    {
        return query_;
    }

    void HeadersHelper::setQueryInformations(const QueryInformations& query)
    {
        query_ = query;
    }

    const QByteArray& HeadersHelper::getProtocol() const
    {
        return protocol_;
    }

    void HeadersHelper::setProtocol(const QByteArray& protocol)
    {
        protocol_ = protocol;
    }

    const QVersionNumber& HeadersHelper::getProtocolVersion() const
    {
        return protocolVersion_;
    }

    void HeadersHelper::setProtocolVersion(const QVersionNumber& protocolVersion)
    {
        protocolVersion_ = protocolVersion;
    }

    const QVector<QByteArray>& HeadersHelper::getHeaders() const
    {
        return query_.headers;
    }

    QByteArray HeadersHelper::generateRawData(std::uint64_t contentSize) const
    {
        QByteArray result;
        result += protocol_ + "/" + protocolVersion_.toString() + " " + QByteArray::number(int(code_)) + " " + Enums::responseCodeToString(code_) + "\r\n";
        for (const auto& header : query_.headers)
            result += header + "\r\n";
        return result;
    }
}