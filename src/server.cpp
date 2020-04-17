#include "SimpleHttpServer/server.hpp"
#include "SimpleHttpServer/queryinformations.hpp"
#include "SimpleHttpServer/types.hpp"

#include "server_p.hpp"
#include "requesthandler.hpp"
#include "responsehandler.hpp"

#include <QThread>
#include <QTcpServer>
#include <QSslSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QElapsedTimer>

namespace shs
{
    Server::Server()
        : pImpl(new ServerImpl)
    {
        pImpl->currentThread_.setObjectName("MainSocketThread");
        pImpl->currentServer_.reset(new QTcpServer);
        pImpl->currentServer_->moveToThread(&pImpl->currentThread_);
        object_.moveToThread(&pImpl->currentThread_);
    }

    Server::~Server()
    {
        stop();
    }

    void Server::setBinding(int port, const QSslConfiguration& sslConfiguration)
    {
        pImpl->port_ = port;
        pImpl->sslConfiguration_ = sslConfiguration;
    }

    bool Server::start()
    {
        QObject::connect(&pImpl->currentThread_, &QThread::started, 
            &object_, [this]() { pImpl->currentServer_->listen(QHostAddress::Any, pImpl->port_); }
        ), Qt::UniqueConnection;

        QObject::connect(&pImpl->currentThread_, &QThread::finished,
            &object_, [this]() { pImpl->currentServer_->close(); }
        ), Qt::UniqueConnection;

        QObject::connect(pImpl->currentServer_.get(), &QTcpServer::newConnection,
            &object_, [this]() { this->onNewConnection(); }
        ), Qt::UniqueConnection;

        if (pImpl->currentThread_.isRunning())
            return true;

        pImpl->currentThread_.start();
        return true;
    }

    bool Server::stop()
    {
        if (!pImpl->currentThread_.isRunning())
            return true;

        pImpl->currentThread_.quit();
        while (pImpl->currentThread_.isRunning())
        {

        }

        return true;
    }

    void Server::attachOnGet(GetFuntion getCallback)
    {
        pImpl->getFuntion_ = getCallback;
    }

    void Server::onNewConnection()
    {
        while (pImpl->currentServer_->hasPendingConnections())
        {
            auto newConnection = pImpl->currentServer_->nextPendingConnection();
            qDebug() << "new connection from " << newConnection->peerAddress().toString() << "(" << newConnection->peerName() << ")";
            QObject::connect(newConnection, &QTcpSocket::readyRead, &object_, [this, newConnection]() { this->handleRequest(newConnection); });
        }
    }

    void Server::handleRequest(QAbstractSocket* device)
    {
        QElapsedTimer timer;
        timer.start();
        RequestHandler request;
        if (!request.parseRequest(device))
            return;

        /*
        qDebug() << "-> Request for " << Enums::requestVerbToString(request.getHeaders().getVerb()) << " -> " << request.getHeaders().getRequest();
        for (const auto& split : request.getHeaders().getHeaders())
            qDebug() << split;
        qDebug() << "---";
        */

        CallbackResponse cbResponse;
        if (pImpl->getFuntion_)
            cbResponse = pImpl->getFuntion_(request.getHeaders().getQueryInformations());

        if (!cbResponse)
            cbResponse = CallbackResponse{ shs::Enums::ResponseCode::NotFound };

        ResponseHandler response;
        response.getHeaders().setProtocol(request.getHeaders().getProtocol());
        response.getHeaders().setProtocolVersion(request.getHeaders().getProtocolVersion());
        response.getHeaders().setCode(cbResponse->responseCode);

        qInfo() << "create response after " << timer.elapsed() << " ms";

        auto count = device->write(response.generateRawData(cbResponse->responseData));
        qInfo() << "Wrote " << count << " bytes after " << timer.elapsed() << " ms";
        device->flush();
        device->close();
        qInfo() << "Close after writing " << count << " bytes after " << timer.elapsed() << " ms";
    }
}