#include "requesthandler.hpp"
#include "headershelper.hpp"

#include <QAbstractSocket>
#include <QDebug>

namespace shs
{
    RequestHandler::RequestHandler()
    {
    }

    bool RequestHandler::parseRequest(QAbstractSocket* device)
    {
        if (device->bytesAvailable() == 0)
            return false;

        auto bytes = device->bytesAvailable();
        auto data = device->peek(bytes);
        if (!data.endsWith("\r\n\r\n"))
            return false;

        device->skip(bytes);

        helper_.parse(data);

        return true;
    }

    const HeadersHelper& RequestHandler::getHeaders() const
    {
        return helper_;
    }
}