#include "responsehandler.hpp"
#include "requesthandler.hpp"

#include <QDebug>

namespace shs
{
    ResponseHandler::ResponseHandler()
    {
    }
    
    void ResponseHandler::importRequest(const RequestHandler& request)
    {
        helper_ = request.getHeaders();
    }

    HeadersHelper& ResponseHandler::getHeaders()
    {
        return helper_;
    }

    QByteArray ResponseHandler::generateRawData(const QByteArray& content) const
    {
        QByteArray result = helper_.generateRawData(content.size());
        if(!result.endsWith("\r\n"))
            result += "\r\n";
        result += "\r\n" + content + "\r\n\r\n";
        return result;
    }
}