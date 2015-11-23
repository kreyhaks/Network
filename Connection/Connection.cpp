#include "Common.h"
#include "Connection.h"


namespace net
{

    Connection::Connection(QTcpSocket *socket)
        : QObject(nullptr)
        , _socket(socket)
        , _id(socket != nullptr ? socket->socketDescriptor() : 0)
    {
        Q_ASSERT(socket != nullptr);
        socket->setParent(nullptr);

        connect(_socket.data(), &QAbstractSocket::disconnected, this, &Connection::disconnected);
        connect(_socket.data(), &QIODevice::readyRead, this, &Connection::readyRead);
    }

    Connection::~Connection()
    {
    }

    qintptr Connection::id() const
    {
        return _id;
    }

    QIODevice* Connection::device() const
    {
        return _socket.data();
    }

    void Connection::close()
    {
        _socket->close();
    }

}
