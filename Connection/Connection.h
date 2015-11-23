#pragma once


namespace net
{

    class Connection
        : public QObject
    {
        Q_OBJECT

    signals:
        void disconnected();
        void readyRead();

    public:
        explicit Connection(QTcpSocket *socket);
        ~Connection();

        qintptr id() const;
        QIODevice *device() const;
        void close();

    private:
        QSharedPointer<QTcpSocket> _socket;
        const qintptr _id;
    };

}
