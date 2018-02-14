#ifndef UDPPEER_H
#define UDPPEER_H

#include <QUdpSocket>

class UDPPeer: public QObject
{
    Q_OBJECT

public:
    UDPPeer(quint16 port);//parentWidget?
    void sendDatagram(QByteArray data, QHostAddress IP, quint16 port);

private slots:
    void receiveDatagram();

signals:
    void incDatagram(const QByteArray&/*, UDPPeer**/);

public://private:
    QUdpSocket* mSocket;
};

#endif // UDPPEER_H
