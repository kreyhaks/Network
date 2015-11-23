#pragma once


namespace net
{

    class Packet
    {
    public:
        Packet() = default;
        virtual ~Packet() = default;

        virtual bool serialize(QByteArray& to) const = 0;
        virtual bool deserialize(const QByteArray& from) = 0;
    };

}
