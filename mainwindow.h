#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

#include <udppeer.h>
#include <message.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    UDPPeer* FCSPeer;
    UDPPeer* FCSPeerTV;
    UDPPeer* FCSPeerTHV;

    QString parsedMessage;
    QString parsedState;
    QString parsedVideoHeader;

    QString LogString;


    ////TableWidget mFields
    int TVRows;
    int THVRows;

    int columns;
    int maxRows;

    ////Periodic message timers
    QTimer* timer6;
    QTimer* timer7;

    ////Periodic message data
    Message6 mMessage6;
    Message7 mMessage7;

    QString settingsFileName;

    enum Settings
    {
        CONTROL_IP,
        CONTROL_PORT,

        VIDEO_IP,
        TV_PORT,
        THV_PORT,

        CONTROL_LISTEN_PORT,
        TV_LISTENPORT,
        THV_LISTENPORT,

        TOTAL_COUNT
    };

    bool controlSocketBound;
    bool tvSocketBound;
    bool thvSocketBound;

    void sendMessage(QByteArray& payload, quint16 descriptor);

    void saveSettings();
    void loadSettings();

private slots:
    ////Setting listen ports
    void on_setListenPorts_clicked();
    void on_unbindButton_clicked();

    ////Handling control messages
    void incomingMessage(const QByteArray& data);

    ////Handling video messages
    void incomingMessageTV(const QByteArray& data);
    void incomingMessageTHV(const QByteArray& data);
    void parseVideoMessage(const QByteArray &data, QTableWidget* tableWidget, int &rows);

    ////Message sending slots
    /// One-shot messages
    void on_sendMessageButton_clicked();
    void on_sendMessageButton_2_clicked();

    void on_sendMessageButton_3_clicked();
    void on_sendMessageButton_4_clicked();
    void on_sendMessageButton_5_clicked();
    void on_sendMessageButton_8_clicked();
    void on_sendMessageButton_9_clicked();
    void on_sendMessageButton_10_clicked();
    void on_sendMessageButton_11_clicked();
    void on_sendMessageButton_12_clicked();
    void on_sendMessageButton_13_clicked();
    void on_sendMessageButton_14_clicked();
    void on_sendMessageButton_15_clicked();
    void on_sendMessageButton_16_clicked();
    void on_sendMessageButton_17_clicked();
    void on_sendMessageButton_18_clicked();
    void on_sendMessageButton_19_clicked();
    void on_sendMessageButton_20_clicked();
    void on_sendMessageButton_21_clicked();
    void on_sendMessageButton_22_clicked();
    void on_sendMessageButton_23_clicked();

    void sendMessage6();
    void sendMessage7();

    /// Repeated messages
    void on_sendMessageButton_6_clicked();
    void on_sendMessageButton_7_clicked();

    void on_repeat6_toggled(bool checked);
    void on_repeat7_toggled(bool checked);

    void on_pushButtonClear_clicked();
    void on_pushButtonSave_clicked();
};


struct timeSpec
{
    qint32 sec;
    qint32 nsec;
};

#endif // MAINWINDOW_H
