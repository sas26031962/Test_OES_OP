#include <udppeer.h>

UDPPeer::UDPPeer(quint16 port)
{
    mSocket = new QUdpSocket(this);
    mSocket->bind(port);
//    qDebug() << mSocket->bind(port, QUdpSocket::ReuseAddressHint);
//    qDebug() << mSocket->bind(port, QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress);
//    qDebug() << mSocket->bind(port, QUdpSocket::ShareAddress);

    connect(mSocket, SIGNAL(readyRead()), this, SLOT(receiveDatagram()));
}

void UDPPeer::sendDatagram(QByteArray data, QHostAddress IP, quint16 port)
{
    mSocket->writeDatagram(data, IP, port/* QHostAddress("127.0.0.1"), 2425*/);
}

void UDPPeer::receiveDatagram()
{
    while(mSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(mSocket->pendingDatagramSize());
        mSocket->readDatagram(datagram.data(), datagram.size());
        /*
        QHostAddress sender;
        quint16 senderPort;
        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
                                */

        emit incDatagram(datagram/*, this*/);
    }
}



