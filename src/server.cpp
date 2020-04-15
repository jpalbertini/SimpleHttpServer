#include "QtHttpServer/server.hpp"
#include "server_p.hpp"

#include <QThread>
#include <QTcpServer>
#include <QSslSocket>
#include <qcoreapplication.h>
#include <QDebug>

namespace qhs
{
    Server::Server()
        : pImpl(new ServerImpl)
    {
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

    void Server::onNewConnection()
    {
        while (pImpl->currentServer_->hasPendingConnections())
        {
            auto newConnection = pImpl->currentServer_->nextPendingConnection();
            qDebug() << "new connection from " << newConnection->peerAddress().toString() << "(" << newConnection->peerName() << ")";
            QObject::connect(newConnection, &QTcpSocket::readyRead, qApp, [newConnection]() {
                qDebug() << "Data: \n---\n" << newConnection->readAll() << "\n---\n";
                }
            );
        }
    }
}