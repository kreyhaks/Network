#include "Common.h"
#include "Server.h"

#include "Connection/Connection.h"


namespace net
{

    Server::Server(QObject* parent)
        : QObject(parent)
    {
        connect(&_listener, &QTcpServer::newConnection, this, &Server::onNewConnection);
    }

    bool Server::listen(const QHostAddress& address, quint16 port)
    {
        if (_listener.isListening())
            _listener.close();

        const auto result = _listener.listen(address, port);
        return result;
    }

    Connection* Server::nextPendingConnection()
    {
        QMutexLocker lock(&_locker);

        if (_freeConnections.isEmpty())
            return nullptr;

        auto connection = _freeConnections.takeFirst();
        disconnect(connection, &QObject::destroyed, this, &Server::onConnectionDestroyed);
        disconnect(connection, &Connection::disconnected, this, &Server::onConnectionDestroyed);

        return connection;
    }

    void Server::onNewConnection()
    {
        auto areNewConnections = 0;
        while (_listener.hasPendingConnections())
        {
            auto socket = _listener.nextPendingConnection();
            auto connection = createConnection(socket);
            if (connection != nullptr)
                areNewConnections++;
        }

        if (areNewConnections != 0)
            emit newConnection();
    }

    void Server::onConnectionDestroyed()
    {
        auto connection = qobject_cast<Connection *>( sender() );
        Q_ASSERT( connection != nullptr );
        _freeConnections.removeOne( connection );
    }

    Connection* Server::createConnection(QTcpSocket* socket)
    {
        if (socket == nullptr)
            return nullptr;

        auto connection = new Connection(socket);
        connect(connection, &QObject::destroyed, this, &Server::onConnectionDestroyed);
        connect(connection, &Connection::disconnected, this, &Server::onConnectionDestroyed);

        QMutexLocker lock(&_locker);
        _freeConnections << connection;

        return connection;
    }

}
