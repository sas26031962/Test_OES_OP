#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QScrollBar>
#include <QTimer>

#include <qdebug.h>
#include <time.h>

#include "degreeconverter.h"
//========================================================================
//Конструктор
//========================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ////Setting up UI
    ui->setupUi(this);
    setWindowTitle("СУО ОЭС ОП v.1.1.0 [ПИО 46.07501544.67167-1.0.3 95 02]");//ПИО 46.07501544.67166-1.0.2 95 02
    ui->radioButtonCommander->setChecked(true);
    ui->radioButtonTV->setChecked(true);

    // очистка лога
    this->LogString = "Начало записи в журнал...";
    this->LogString += "\n\n";

    this->ui->textBrowserLog->setText(this->LogString);

    ////Setting up tableWidgets for TV/THV message display
    columns = 1;
    maxRows = 1000;

    ////TV
    TVRows = 0;

    ui->TVDisplay->setRowCount(TVRows);
    ui->TVDisplay->setColumnCount(columns);

    ui->TVDisplay->setColumnWidth(0, ui->TVDisplay->width());

//    QTableWidgetItem* hdr = new QTableWidgetItem;
//    hdr->setText("Входящее сообщение ТВ канала");
//    ui->TVDisplay->setHorizontalHeaderItem(0, hdr);

    ui->TVDisplay->setHorizontalHeaderItem(0, new QTableWidgetItem("Входящее сообщение ТВ канала"));

    //ui->TVDisplay->verticalHeader()->hide();
    //ui->TVDisplay->horizontalHeader()->hide();

    ////THV
    THVRows = 0;

    ui->THVDisplay->setRowCount(THVRows);
    ui->THVDisplay->setColumnCount(columns);

    ui->THVDisplay->setColumnWidth(0, ui->THVDisplay->width());

    ui->THVDisplay->setHorizontalHeaderItem(0, new QTableWidgetItem("Входящее сообщение ТПВ канала"));

    //ui->THVDisplay->verticalHeader()->hide();
    //ui->THVDisplay->horizontalHeader()->hide();



    //Загрузка начальных установок
    settingsFileName = "settings.txt";
    loadSettings();

    //get rid of UDPPeer, use QUdpSocket
    FCSPeer     = new UDPPeer(ui->CListenPort->text().toInt());
    FCSPeerTV   = new UDPPeer(ui->TVListenPort->text().toInt());
    FCSPeerTHV  = new UDPPeer(ui->THVListenPort->text().toInt());
    //replace port binding with on_setListenPorts_clicked();

    on_setListenPorts_clicked();

    connect(FCSPeer,    SIGNAL(incDatagram(QByteArray)), this, SLOT(incomingMessage(QByteArray)));
    connect(FCSPeerTV,  SIGNAL(incDatagram(QByteArray)), this, SLOT(incomingMessageTV(QByteArray)));
    connect(FCSPeerTHV, SIGNAL(incDatagram(QByteArray)), this, SLOT(incomingMessageTHV(QByteArray)));



    ////Handling repeated messages
    timer6 = new QTimer(this);
    connect(timer6, SIGNAL(timeout()), this, SLOT(sendMessage6()));

    timer7 = new QTimer(this);
    connect(timer7, SIGNAL(timeout()), this, SLOT(sendMessage7()));


}//End of ctor

//========================================================================
//Деструктор
//========================================================================
MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}




//
// Обработчик нажатия клавиши ПРИВЯЗКА ПОРТОВ
//
void MainWindow::on_setListenPorts_clicked()
{
    on_unbindButton_clicked();

    controlSocketBound  = FCSPeer->mSocket->bind(ui->CListenPort->text().toInt());
    this->LogString += "Сокет команд привязан к порту ";
    this->LogString += this->ui->CListenPort->text();
    this->LogString += "\n";

    tvSocketBound       = FCSPeerTV->mSocket->bind(ui->TVListenPort->text().toInt());
    this->LogString += "Сокет ТВ привязан к порту ";
    this->LogString += this->ui->TVListenPort->text();
    this->LogString += "\n";

    thvSocketBound      = FCSPeerTHV->mSocket->bind(ui->THVListenPort->text().toInt());
    this->LogString += "Сокет ТПВ привязан к порту ";
    this->LogString += this->ui->THVListenPort->text();
    this->LogString += "\n";



    const QString boundSocketVisuals = "background: rgb(38, 194, 129)"; //green(Jungle Green)

    if(controlSocketBound)
    {
        ui->CListenPort->setStyleSheet(boundSocketVisuals);
    }

    if(tvSocketBound)
    {
        ui->TVListenPort->setStyleSheet(boundSocketVisuals);
    }

    if(thvSocketBound)
    {
        ui->THVListenPort->setStyleSheet(boundSocketVisuals);
    }
    // Вывод результата логгирования
    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_setListenPorts_clicked()

//
// Обработчик нажатия клавишы ОСВОБОЖДЕНИЕ ПОРТОВ
//
void MainWindow::on_unbindButton_clicked()
{
    FCSPeer->mSocket->close();
    this->LogString += "Командный сокет закрыт\n";

    FCSPeerTV->mSocket->close();
    this->LogString += "Сокет ТВ закрыт\n";

    FCSPeerTHV->mSocket->close();
    this->LogString += "Сокет ТПВ закрыт\n";

    controlSocketBound = false;
    tvSocketBound = false;
    thvSocketBound = false;

    const QString unboundSocketVisuals = "background: rgb(189, 195, 199)"; //grey(Silver Sand)

    ui->CListenPort->setStyleSheet(unboundSocketVisuals);
    ui->TVListenPort->setStyleSheet(unboundSocketVisuals);
    ui->THVListenPort->setStyleSheet(unboundSocketVisuals);

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_unbindButton_clicked()


void MainWindow::saveSettings()
{
    QFile outFile(settingsFileName);
    if(outFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&outFile);
        out << "ControlIP: "    << ui->CommanderControlIP->text() <<"\n";
        out << "ControlPort: "  << ui->CommanderCPort->text() <<"\n";

        out << "VideoIP: "      << ui->CommanderVideoIP->text() <<"\n";
        out << "TVPort: "       << ui->CommanderTVPort->text() <<"\n";
        out << "THVPort: "      << ui->CommanderTHVPort->text() <<"\n";

        out << "ControlListenPort: "    << ui->CListenPort->text() <<"\n";
        out << "TVListenPort: "         << ui->TVListenPort->text() <<"\n";
        out << "THVListenPort: "        << ui->THVListenPort->text() <<"\n";

        outFile.close();

        this->LogString += "Сетевые настройки были сохранены";
        this->LogString += "\n";
        // Вывод результата логгирования
        this->ui->textBrowserLog->setText(this->LogString);

    }
}//End of void MainWindow::saveSettings()

void MainWindow::loadSettings()
{

    QFile inFile(settingsFileName);
    if(inFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inFile);

       QString garbage;
       QString parameters[TOTAL_COUNT];

       for(int i = 0; i<TOTAL_COUNT; ++i)
       {
           in >> garbage >> parameters[i];
       }

       inFile.close();


       ui->CommanderControlIP->setText(parameters[CONTROL_IP]);
       ui->CommanderCPort->setText(parameters[CONTROL_PORT]);

       ui->CommanderVideoIP->setText(parameters[VIDEO_IP]);
       ui->CommanderTVPort->setText(parameters[TV_PORT]);
       ui->CommanderTHVPort->setText(parameters[THV_PORT]);

       ui->CListenPort->setText(parameters[CONTROL_LISTEN_PORT]);
       ui->TVListenPort->setText(parameters[TV_LISTENPORT]);
       ui->THVListenPort->setText(parameters[THV_LISTENPORT]);

       this->LogString += ">Загрузка сетевых настроек завершена";
       this->LogString += "\n";
       // Вывод результата логгирования
       this->ui->textBrowserLog->setText(this->LogString);

    }

}//End of void MainWindow::loadSettings()



//
//Разборка входящих сообщений
//
void MainWindow::incomingMessage(const QByteArray &data)
{
    ////Splitting the header from payload
    QByteArray c(data);
    QDataStream inStr(&c, QIODevice::ReadOnly);
    inStr.setByteOrder(QDataStream::LittleEndian);

    quint16 descriptor;
    quint16 messageNumber;
    timeSpec trTime;

    // Извлечение параметров базового протокола

    inStr >> descriptor;
    inStr >> messageNumber;
    inStr >> trTime.sec;
    inStr >> trTime.nsec;

    QString sDescriptor;
    QString sMessageNumber;
    QString sTimeSec;
    QString sTimeNsec;

    sDescriptor.setNum(descriptor);
    sMessageNumber.setNum(messageNumber);
    sTimeSec.setNum(trTime.sec);
    sTimeNsec.setNum(trTime.nsec);

    QByteArray payload;
    quint8 payloadSize = c.size() - (sizeof(descriptor) + sizeof(messageNumber) + sizeof(trTime));
    payload.resize(payloadSize);

    inStr.readRawData(payload.data(), payloadSize);


    ////Parsing the header
    ////Time Conversion
    ////Setting time sample to the received total amount of seconds(int)
    time_t timeSample = int(trTime.sec);  //received time
    //time_t timeSample = time(0);            //current system time

    ////Creating & initializing time storing object with received data & extracting the mFields
    /*struct */tm tmStruct;
    tmStruct = *localtime(&timeSample);

    QString parsedHeader;

    parsedHeader += "#" + QString::number(messageNumber) + " @";
    parsedHeader += QString::number(tmStruct.tm_hour) + ":";
    parsedHeader += QString::number(tmStruct.tm_min) + ":";
    parsedHeader += QString::number(tmStruct.tm_sec) + ".";
    parsedHeader += QString::number(quint32(trTime.nsec)) + "\n";

    if(descriptor != 105)
    {
        parsedMessage += parsedHeader;
    }
    else
    {
        parsedState = parsedHeader;
    }

    QString stringDescriptor;

    ////Parsing the payload
    switch(descriptor)
    {
    case 105:
    {
        Message105 m;
        m.fromBytes(&payload);
        if(payloadSize == sizeof(m))
        {
            parsedState += m.parse();
            //---Sink frame decoding---

            //this->LogString += "Sink datagram:\n";
            //this->LogString += "-descriptor=";
            //this->LogString += stringDescriptor.setNum(descriptor);
            //this->LogString += "\n";

            //this->ui->textBrowserLog->setText(this->LogString);
            //-------------------------
        }
        else
        {
            parsedState += "Message length[" + QString::number(payloadSize) +
                    "] doesn't match[" + QString::number(sizeof(m)) +
                    "]. Descriptor [" + QString::number(descriptor) + "]";
        }

        ui->stateDisplay->setText(parsedState);
    }//End of case 105
        break;
    case 106:
    {
        Message106 m;
        m.fromBytes(&payload);
        //---Sink frame decoding---
        this->LogString += "<Принята датаграмма:\n";
        this->LogString += m.parse();
        this->LogString += "\n";

        this->ui->textBrowserLog->setText(this->LogString);
        //-------------------------

        if(payloadSize == sizeof(m))
        {
            parsedMessage += m.parse();
        }
        else
        {
            parsedMessage += "Message length[" + QString::number(payloadSize) +
                    "] doesn't match[" + QString::number(sizeof(m)) +
                    "]. Descriptor [" + QString::number(descriptor) + "]";
        }
    }//End of case 106
        break;
    case 107:
    {
        Message107 m;
        m.fromBytes(&payload);
        //---Sink frame decoding---
        this->LogString += "<Принята датаграмма:\n";
        this->LogString += m.parse();
        this->LogString += "\n";

        this->ui->textBrowserLog->setText(this->LogString);
        //-------------------------

        if(payloadSize == sizeof(m))
        {
            parsedMessage += m.parse();
        }
        else
        {
            parsedMessage += "Message length[" + QString::number(payloadSize) +
                    "] doesn't match[" + QString::number(sizeof(m)) +
                    "]. Descriptor [" + QString::number(descriptor) + "]";
        }
    }//End of case 107
        break;
    case 108:
    {
        Message108 m;
        m.fromBytes(&payload);
        //---Sink frame decoding---
        this->LogString += "<Принята датаграмма:\n";
        this->LogString += m.parse();
        this->LogString += "\n";

        this->ui->textBrowserLog->setText(this->LogString);
        //-------------------------

        if(payloadSize == sizeof(m))
        {
            parsedMessage += m.parse();
        }
        else
        {
            parsedMessage += "Message length[" + QString::number(payloadSize) +
                    "] doesn't match[" + QString::number(sizeof(m)) +
                    "]. Descriptor [" + QString::number(descriptor) + "]";
        }
    }//End of case 108
        break;
    case 109:
    {
        Message109 m;
        m.fromBytes(&payload);
        //---Sink frame decoding---
        this->LogString += "<Принята датаграмма:\n";
        this->LogString += m.parse();
        this->LogString += "\n";

        this->ui->textBrowserLog->setText(this->LogString);
        //-------------------------

        if(payloadSize == sizeof(m))
        {
            parsedMessage += m.parse();
        }
        else
        {
            parsedMessage += "Message length[" + QString::number(payloadSize) +
                    "] doesn't match[" + QString::number(sizeof(m)) +
                    "]. Descriptor [" + QString::number(descriptor) + "]";
        }
    }//End of case 109
        break;
    case 110:
    {
        Message110 m;
        m.fromBytes(&payload);
        //---Sink frame decoding---
        this->LogString += "<Принята датаграмма:\n";
        this->LogString += m.parse();
        this->LogString += "\n";

        this->ui->textBrowserLog->setText(this->LogString);
        //-------------------------

        if(payloadSize < 14)
        {
            parsedMessage += m.parse();
        }
        else
        {
            parsedMessage += "Message length[" + QString::number(payloadSize) +
                    "] doesn't match the min[" + QString::number(14) +
                    "]. Descriptor [" + QString::number(descriptor) + "]";
        }
    }//End of case 110
        break;
    case 111:
    {
        Message111 m;
        //---Sink frame decoding---
        this->LogString += "<Принята датаграмма:\n";
        this->LogString += m.parse();
        this->LogString += "\n";

        this->ui->textBrowserLog->setText(this->LogString);
        //-------------------------

        if(payloadSize == 0)
        {
            parsedMessage += m.parse();
        }
        else
        {
            parsedMessage += "Message length[" + QString::number(payloadSize) +
                    "] doesn't match[" + QString::number(0) +
                    "]. Descriptor [" + QString::number(descriptor) + "]";
        }
    }//End of case 111
        break;
    case 112:
    {
        Message112 m;
        //---Sink frame decoding---
        this->LogString += "<Принята датаграмма:\n";
        this->LogString += m.parse();
        this->LogString += "\n";

        this->ui->textBrowserLog->setText(this->LogString);
        //-------------------------
        m.fromBytes(&payload);

        if(payloadSize == sizeof(m))
        {
            parsedMessage += m.parse();
        }
        else
        {
            parsedMessage += "Message length[" + QString::number(payloadSize) +
                    "] doesn't match[" + QString::number(sizeof(m)) +
                    "]. Descriptor [" + QString::number(descriptor) + "]";
        }
    }//End of case 112
        break;
    case 113:
    {
        Message113 m;
        //---Sink frame decoding---
        this->LogString += "<Принята датаграмма:\n";
        this->LogString += m.parse();
        this->LogString += "\n";

        this->ui->textBrowserLog->setText(this->LogString);
        //-------------------------
        m.fromBytes(&payload);

        if(payloadSize == sizeof(m))
        {
            parsedMessage += m.parse();
        }
        else
        {
            parsedMessage += "Message length[" + QString::number(payloadSize) +
                    "] doesn't match[" + QString::number(sizeof(m)) +
                    "]. Descriptor [" + QString::number(descriptor) + "]";
        }
    }//End of case 113
        break;
    default:
        parsedMessage += "Неизвестный дескриптор:" + QString::number(descriptor);
        break;
    }//End of switch(descriptor)


    ////Adding an offset for next message, displaying the result & adjusting the view
    if(descriptor != 105)
    {
        parsedMessage += "\n\n";
        ui->textBrowser->setText(parsedMessage);

        QScrollBar* sb = ui->textBrowser->verticalScrollBar();
        sb->setValue(sb->maximum());
    }
}//End of void MainWindow::incomingMessage(const QByteArray &data)




////Handling video messages
void MainWindow::parseVideoMessage(const QByteArray &data, QTableWidget* tableWidget, int& rows)
{

    QByteArray c(data);
    QDataStream inStr(&c, QIODevice::ReadOnly);
    inStr.setByteOrder(QDataStream::LittleEndian);

    quint16 descriptor;
    quint16 messageNumber;
    quint64 trTime;

    inStr >> descriptor;
    inStr >> messageNumber;
    inStr >> trTime;

    QByteArray payload;
    quint8 payloadSize = c.size() - (sizeof(descriptor) + sizeof(messageNumber) + sizeof(trTime));
    payload.resize(payloadSize);

    inStr.readRawData(payload.data(), payloadSize);


    QString parsedMessage;

    switch(descriptor)
    {
    case 101:
    {
        Message101 m;
        parsedMessage = m.parse();
    }
        break;
    case 102:
    {
        Message102 m;
        parsedMessage = m.parse();
    }
        break;
    case 103:
    {
        Message103 m;
        parsedMessage = m.parse();
    }
        break;
    case 104:
    {
        Message104 m;
        parsedMessage = m.parse();
    }
        break;
    default:
        parsedMessage += "Неизвестный дескриптор:" + QString::number(descriptor);
        break;
    }

    if(rows < maxRows)
    {
        ++rows;
    }
    else
    {
        rows = 1;
    }

    tableWidget->setRowCount(rows);
    tableWidget->setItem(rows-1, columns-1, new QTableWidgetItem(parsedMessage));
    //tableWidget->resizeRowToContents(rows-1);

    QScrollBar* sb = tableWidget->verticalScrollBar();
    sb->setValue(sb->maximum());
}


void MainWindow::incomingMessageTV(const QByteArray &data)
{
    if(ui->checkBoxHaltTV->isChecked())
    {
        return;
    }
    parseVideoMessage(data, ui->TVDisplay, TVRows);
}


void MainWindow::incomingMessageTHV(const QByteArray &data)
{
    if(ui->checkBoxHaltTHV->isChecked())
    {
        return;
    }
    parseVideoMessage(data, ui->THVDisplay, THVRows);
}



////Message sending method
void MainWindow::sendMessage(QByteArray &payload, quint16 descriptor)
{
    if(!controlSocketBound)
    {
        qDebug() << "socket unbound!";
        return;
    }
    QByteArray completeDatagram;
    QDataStream str(&completeDatagram, QIODevice::WriteOnly);
    str.setByteOrder(QDataStream::LittleEndian);

    quint16 messageNumber = 0;
    quint64 trTime = 0;

    str << descriptor;
    str << messageNumber;
    str << trTime;
    //str << payload.data();
    //str.writeRawData(payload.constData(), payload.size());
    completeDatagram.append(payload);


    QHostAddress IP;
    quint16 port;

    //switch(descriptor)
    if(ui->radioButtonCommander->isChecked())
    {
        if(descriptor < 3)
        {
            IP.setAddress(ui->CommanderVideoIP->text());

            if(ui->radioButtonTV->isChecked())
            {
                port = ui->CommanderTVPort->text().toInt();
            }
            if(ui->radioButtonTHV->isChecked())
            {
                port = ui->CommanderTHVPort->text().toInt();
            }
        }
        else
        {
            IP.setAddress(ui->CommanderControlIP->text());

            port = ui->CommanderCPort->text().toInt();

            parsedMessage = "";
            ui->textBrowser->setText(parsedMessage);
        }
    }
    else if(ui->radioButtonAimer->isChecked())
    {
        if(descriptor < 3)
        {
            IP.setAddress(ui->AimerVideoIP->text());

            if(ui->radioButtonTV->isChecked())
            {
                port = ui->AimerTVPort->text().toInt();;
            }
            if(ui->radioButtonTHV->isChecked())
            {
                port = ui->AimerTHVPort->text().toInt();
            }
        }
        else
        {
            IP.setAddress(ui->AimerControlIP->text());

            port = ui->AimerCPort->text().toInt();

            parsedMessage = "";
            ui->textBrowser->setText(parsedMessage);
        }
    }

//    IP.setAddress("127.0.0.1");
//    port = 2425;

//    IP.setAddress(ui->AimerControlIP->text());
//    port = ui->AimerCPort->text().toInt();

    FCSPeer->sendDatagram(completeDatagram, IP, port);
}



//===========================================================
//Обработчики нажатия на кнопки команд
//===========================================================

void MainWindow::on_sendMessageButton_clicked()
{
    int descriptor = 1;
    Message1 c;
    c.setData(ui->lineEdit1->text().toInt(),
              ui->lineEdit1_2->text().toInt());

    QByteArray payload;
    c.toBytes(&payload);

    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда ОТКРЫТЬ ВИДЕОПОТОК\n";
    this->LogString += "с параметрами: \n";
    this->LogString += "-частота кадров=";
    this->LogString += ui->lineEdit1->text();
    this->LogString += "\n";
    this->LogString += "-сжатие=";
    this->LogString += ui->lineEdit1_2->text();
    this->LogString += "\n";

    this->ui->textBrowserLog->setText(this->LogString);


}//End of void MainWindow::on_sendMessageButton_clicked()

void MainWindow::on_sendMessageButton_2_clicked()
{
    QByteArray payload;
    int descriptor = 2;
    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда ЗАКРЫТЬ ВИДЕОПОТОК\n";

    this->ui->textBrowserLog->setText(this->LogString);


}//End of void MainWindow::on_sendMessageButton_2_clicked()


void MainWindow::on_sendMessageButton_3_clicked()
{
    int descriptor = 3;
    Message3 message(ui->lineEdit3->text().toInt());

    QByteArray payload;
    message.toBytes(&payload);

    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда УСТАНОВИТЬ ОПТИЧЕСКИЙ ФИЛЬТР\n";
    this->LogString += "с параметрами: \n";
    this->LogString += "-тип фильтра=";
    this->LogString += ui->lineEdit3->text();
    this->LogString += "\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_3_clicked()

void MainWindow::on_sendMessageButton_4_clicked()
{
    int descriptor = 4;
    QString mode;

    Message4 c;
    c.setData(ui->comboBox4->currentIndex());

    QByteArray payload;
    c.toBytes(&payload);

    sendMessage(payload, descriptor);

    mode.setNum(ui->comboBox4->currentIndex());

    this->LogString += ">Выполнена команда ИЗМЕНИТЬ РЕЖИМ РАБОТЫ\n";
    this->LogString += "с параметрами: \n";
    this->LogString += "-режим=";
    this->LogString += mode;
    this->LogString += "\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_4_clicked()

void MainWindow::on_sendMessageButton_5_clicked()
{
    int descriptor = 5;
    ui->repeat6->setChecked(false);
    ui->repeat7->setChecked(false);

    QByteArray payload;

    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда ПЕРЕЙТИ В СТАБИЛИЗАЦИЮ\n";
    //this->LogString += "с параметрами: \n";
    //this->LogString += "-режим=";
    //this->LogString += mode;
    //this->LogString += "\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_5_clicked()

void MainWindow::on_sendMessageButton_6_clicked()
{

    ui->repeat7->setChecked(false);


    mMessage6.setData(ui->comboBoxCoordSystem->currentIndex(),

                      degreesToRawValue(ui->doubleSpinBoxHorAngle->value()),
                      degreesToRawValue(ui->doubleSpinBoxVertAngle->value()),
                      degreesToRawValue(ui->doubleSpinBoxHorAngularVelocity->value()),
                      degreesToRawValue(ui->doubleSpinBoxVertAngularVelocity->value()),

                      ui->lineEditFocusDistanceTV->text().toInt(),
                      ui->lineEditExpositionTimeTV->text().toInt(),
                      ui->lineEditAmpTV->text().toInt(),
                      ui->lineEditContrastTV->text().toInt(),
                      ui->lineEditFocusDistanceTHV->text().toInt(),
                      ui->lineEditExpositionTimeTHV->text().toInt(),
                      ui->lineEditAmpTHV->text().toInt(),
                      ui->lineEditContrastTHV->text().toInt());

    if(ui->repeat6->isChecked())
    {
        timer6->start(ui->repeatPeriod6->cleanText().toInt());
    }
    else
    {
        sendMessage6();
    }
    QString hAngle;
    QString vAngle;
    QString hAngularVelocity;
    QString vAngularVelocity;

    this->LogString += ">Выполнена команда СОПРОВОЖДЕНИЕ ПО УГЛАМ И СКОРОСТЯМ\n";
    this->LogString += "с параметрами: \n";
    this->LogString += "-угол горизонтального наведения=";
    this->LogString += hAngle.setNum(ui->doubleSpinBoxHorAngle->value());
    this->LogString += "\n";
    this->LogString += "-угол вертикального наведения=";
    this->LogString += vAngle.setNum(ui->doubleSpinBoxVertAngle->value());
    this->LogString += "\n";
    this->LogString += "-угловая скорость горизонтального наведения=";
    this->LogString += hAngularVelocity.setNum(ui->doubleSpinBoxHorAngularVelocity->value());
    this->LogString += "\n";
    this->LogString += "-угловая скорость вертикального наведения=";
    this->LogString += vAngularVelocity.setNum(ui->doubleSpinBoxVertAngularVelocity->value());
    this->LogString += "\n";
    this->LogString += "-фокусное расстояние ТВ=";
    this->LogString += ui->lineEditFocusDistanceTV->text();
    this->LogString += "\n";
    this->LogString += "-экспозиция ТВ=";
    this->LogString += ui->lineEditExpositionTimeTV->text();
    this->LogString += "\n";
    this->LogString += "-коэффициент усиления матрицы ТВ=";
    this->LogString += ui->lineEditAmpTV->text();
    this->LogString += "\n";
    this->LogString += "-контрастность ТВ=";
    this->LogString += ui->lineEditContrastTV->text();
    this->LogString += "\n";
    this->LogString += "-фокусное расстояние ТПВ=";
    this->LogString += ui->lineEditFocusDistanceTHV->text();
    this->LogString += "\n";
    this->LogString += "-экспозиция ТПВ=";
    this->LogString += ui->lineEditExpositionTimeTHV->text();
    this->LogString += "\n";
    this->LogString += "-коэффициент усиления матрицы ТПВ=";
    this->LogString += ui->lineEditAmpTV->text();
    this->LogString += "\n";
    this->LogString += "-контрастность ТПВ=";
    this->LogString += ui->lineEditContrastTHV->text();
    this->LogString += "\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_6_clicked()


void MainWindow::on_sendMessageButton_7_clicked()
{
    ui->repeat6->setChecked(false);

    mMessage7.setData(ui->comboBoxCoordSystem->currentIndex(),

                      degreesToRawValue(ui->doubleSpinBoxHorAngularVelocity->value()),
                      degreesToRawValue(ui->doubleSpinBoxVertAngularVelocity->value()),

                      ui->lineEditFocusDistanceTV->text().toInt(),
                      ui->lineEditExpositionTimeTV->text().toInt(),
                      ui->lineEditAmpTV->text().toInt(),
                      ui->lineEditContrastTV->text().toInt(),
                      ui->lineEditFocusDistanceTHV->text().toInt(),
                      ui->lineEditExpositionTimeTHV->text().toInt(),
                      ui->lineEditAmpTHV->text().toInt(),
                      ui->lineEditContrastTHV->text().toInt());

    if(ui->repeat7->isChecked())
    {
        timer7->start(ui->repeatPeriod7->cleanText().toInt());
    }
    else
    {
        sendMessage7();
    }

    QString hAngularVelocity;
    QString vAngularVelocity;

    this->LogString += ">Выполнена команда СОПРОВОЖДЕНИЕ ПО СКОРОСТЯМ\n";
    this->LogString += "с параметрами: \n";
    this->LogString += "-угловая скорость горизонтального наведения=";
    this->LogString += hAngularVelocity.setNum(ui->doubleSpinBoxHorAngularVelocity->value());
    this->LogString += "\n";
    this->LogString += "-угловая скорость вертикального наведения=";
    this->LogString += vAngularVelocity.setNum(ui->doubleSpinBoxVertAngularVelocity->value());
    this->LogString += "\n";
    this->LogString += "-фокусное расстояние ТВ=";
    this->LogString += ui->lineEditFocusDistanceTV->text();
    this->LogString += "\n";
    this->LogString += "-экспозиция ТВ=";
    this->LogString += ui->lineEditExpositionTimeTV->text();
    this->LogString += "\n";
    this->LogString += "-коэффициент усиления матрицы ТВ=";
    this->LogString += ui->lineEditAmpTV->text();
    this->LogString += "\n";
    this->LogString += "-контрастность ТВ=";
    this->LogString += ui->lineEditContrastTV->text();
    this->LogString += "\n";
    this->LogString += "-фокусное расстояние ТПВ=";
    this->LogString += ui->lineEditFocusDistanceTHV->text();
    this->LogString += "\n";
    this->LogString += "-экспозиция ТПВ=";
    this->LogString += ui->lineEditExpositionTimeTHV->text();
    this->LogString += "\n";
    this->LogString += "-коэффициент усиления матрицы ТПВ=";
    this->LogString += ui->lineEditAmpTV->text();
    this->LogString += "\n";
    this->LogString += "-контрастность ТПВ=";
    this->LogString += ui->lineEditContrastTHV->text();
    this->LogString += "\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_7_clicked()

void MainWindow::on_sendMessageButton_8_clicked()
{
    int descriptor = 8;
    ui->repeat6->setChecked(false);
    ui->repeat7->setChecked(false);

    Message8 c;
    c.setData(ui->comboBoxCoordSystem->currentIndex(),

              degreesToRawValue(ui->doubleSpinBoxHorAngle->value()),
              degreesToRawValue(ui->doubleSpinBoxVertAngle->value()),

              ui->lineEditFocusDistanceTV->text().toInt(),
              ui->lineEditExpositionTimeTV->text().toInt(),
              ui->lineEditAmpTV->text().toInt(),
              ui->lineEditContrastTV->text().toInt(),
              ui->lineEditFocusDistanceTHV->text().toInt(),
              ui->lineEditExpositionTimeTHV->text().toInt(),
              ui->lineEditAmpTHV->text().toInt(),
              ui->lineEditContrastTHV->text().toInt());

    QByteArray payload;
    c.toBytes(&payload);

    sendMessage(payload, descriptor);

    QString hAngle;
    QString vAngle;

    this->LogString += ">Выполнена команда ПЕРЕБРОС ПО ЗАДАННЫМ УГЛАМ\n";
    this->LogString += "с параметрами: \n";
    this->LogString += "-угол горизонтального наведения=";
    this->LogString += hAngle.setNum(ui->doubleSpinBoxHorAngle->value());
    this->LogString += "\n";
    this->LogString += "-угол вертикального наведения=";
    this->LogString += vAngle.setNum(ui->doubleSpinBoxVertAngle->value());
    this->LogString += "\n";
    this->LogString += "-фокусное расстояние ТВ=";
    this->LogString += ui->lineEditFocusDistanceTV->text();
    this->LogString += "\n";
    this->LogString += "-экспозиция ТВ=";
    this->LogString += ui->lineEditExpositionTimeTV->text();
    this->LogString += "\n";
    this->LogString += "-коэффициент усиления матрицы ТВ=";
    this->LogString += ui->lineEditAmpTV->text();
    this->LogString += "\n";
    this->LogString += "-контрастность ТВ=";
    this->LogString += ui->lineEditContrastTV->text();
    this->LogString += "\n";
    this->LogString += "-фокусное расстояние ТПВ=";
    this->LogString += ui->lineEditFocusDistanceTHV->text();
    this->LogString += "\n";
    this->LogString += "-экспозиция ТПВ=";
    this->LogString += ui->lineEditExpositionTimeTHV->text();
    this->LogString += "\n";
    this->LogString += "-коэффициент усиления матрицы ТПВ=";
    this->LogString += ui->lineEditAmpTV->text();
    this->LogString += "\n";
    this->LogString += "-контрастность ТПВ=";
    this->LogString += ui->lineEditContrastTHV->text();
    this->LogString += "\n";

    this->ui->textBrowserLog->setText(this->LogString);

}// End of void MainWindow::on_sendMessageButton_8_clicked()

void MainWindow::on_sendMessageButton_9_clicked()
{
    int descriptor = 9;
    QByteArray payload;

    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда ЗАПРОС ДИАГНОСТИКИ\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_9_clicked()

void MainWindow::on_sendMessageButton_10_clicked()
{
    int descriptor = 10;
    Message10 c;
    c.setData(ui->comboBox10->currentIndex(),
              ui->comboBox10_2->currentIndex());

    QByteArray payload;
    c.toBytes(&payload);

    sendMessage(payload, descriptor);
    QString tvEyeShoot;
    QString tpvEyeShoot;

    this->LogString += ">Выполнена команда СМЕНИТЬ ПОЛЕ ЗРЕНИЯ\n";
    this->LogString += "с параметрами: \n";
    this->LogString += "-поле зрения ТВ=";
    this->LogString += tvEyeShoot.setNum(ui->comboBox10->currentIndex());
    this->LogString += "\n";
    this->LogString += "-поле зрения ТПВ=";
    this->LogString += tpvEyeShoot.setNum(ui->comboBox10_2->currentIndex());
    this->LogString += "\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_10_clicked()

void MainWindow::on_sendMessageButton_11_clicked()
{
    int descriptor = 11;
    Message11 c;
    c.setData(ui->lineEdit11->text().toInt(),
              ui->lineEdit11_2->text().toInt(),
              ui->lineEdit11_3->text().toInt());

    QByteArray payload;
    c.toBytes(&payload);

    sendMessage(payload, descriptor);

    QString nTarget = ui->lineEdit11->text();
    QString minStrob = ui->lineEdit11_2->text();
    QString maxStrob = ui->lineEdit11_3->text();

    this->LogString += ">Выполнена команда ИЗМЕРИТЬ ДАЛЬНОСТЬ\n";
    this->LogString += "с параметрами: \n";
    this->LogString += "-количество целей=";
    this->LogString += nTarget;
    this->LogString += "\n";
    this->LogString += "-строб минимальной дальности=";
    this->LogString += minStrob;
    this->LogString += "\n";
    this->LogString += "-строб максимальной дальности=";
    this->LogString += maxStrob;
    this->LogString += "\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_11_clicked()

void MainWindow::on_sendMessageButton_12_clicked()
{
    int descriptor = 12;
    Message12 message(ui->lineEdit12->text().toInt());

    QByteArray payload;
    message.toBytes(&payload);

    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда ВКЛЮЧИТЬ ОБОГРЕВ СТЕКЛА\n";
    this->LogString += "с параметрами: \n";
    this->LogString += "-время обогрева=";
    this->LogString += ui->lineEdit12->text();
    this->LogString += "\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_12_clicked()

void MainWindow::on_sendMessageButton_13_clicked()
{
    int descriptor = 13;
    QByteArray payload;

    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда ЗАПРОСИТЬ НАРАБОТКУ ЛЛКУ\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_13_clicked()

void MainWindow::on_sendMessageButton_14_clicked()
{
    int descriptor = 14;
    QByteArray payload;

    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда ЗАПРОСИТЬ НАРАБОТКУ ЛД\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_14_clicked()


void MainWindow::on_sendMessageButton_15_clicked()
{
    int descriptor = 15;
    QByteArray payload;

    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда ЗАПРОСИТЬ СОСТОЯНИЕ ПРИЦЕЛА\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_15_clicked()

void MainWindow::on_sendMessageButton_16_clicked()
{
    int descriptor = 16;
    QByteArray payload;

    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда КАЛИБРОВКА ТПВ МАТРИЦЫ\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_16_clicked()

void MainWindow::on_sendMessageButton_17_clicked()
{
    int descriptor = 17;
    ui->repeat6->setChecked(false);
    ui->repeat7->setChecked(false);

    QByteArray payload;

    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда ПЕРЕВЕСТИ В ТРАНСПОРТНОЕ ПОЛОЖЕНИЕ\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_17_clicked()

void MainWindow::on_sendMessageButton_18_clicked()
{
    int descriptor = 18;
    Message18 c;
    c.setData(ui->lineEdit18->text().toInt(),
              ui->lineEdit18_2->text().toInt());

    QByteArray payload;
    c.toBytes(&payload);

    sendMessage(payload, descriptor);
    QString numParameter = ui->lineEdit18->text();
    QString valParameter = ui->lineEdit18_2->text();

    this->LogString += ">Выполнена команда УСТАНОВИТЬ ПАРАМЕТР\n";
    this->LogString += "с параметрами: \n";
    this->LogString += "-номер параметра=";
    this->LogString += numParameter;
    this->LogString += "\n";
    this->LogString += "-значение параметра=";
    this->LogString += valParameter;
    this->LogString += "\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_18_clicked()

void MainWindow::on_sendMessageButton_19_clicked()
{
    int descriptor = 19;
    Message19 c;
    c.setData(ui->lineEdit19->text().toInt());

    QByteArray payload;
    c.toBytes(&payload);

    sendMessage(payload, descriptor);

    QString numParameter = ui->lineEdit19->text();

    this->LogString += ">Выполнена команда ЗАПРОСИТЬ ПАРАМЕТР\n";
    this->LogString += "с параметрами: \n";
    this->LogString += "-номер параметра=";
    this->LogString += numParameter;
    this->LogString += "\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_19_clicked()

void MainWindow::on_sendMessageButton_20_clicked()
{
    int descriptor = 20;
    QByteArray payload;

    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда ВКЛЮЧИТЬ ТПВ МАТРИЦУ\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_20_clicked()

void MainWindow::on_sendMessageButton_21_clicked()
{
    QByteArray payload;

    int descriptor = 21;
    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда ВЫКЛЮЧИТЬ ТПВ МАТРИЦУ\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_21_clicked()

void MainWindow::on_sendMessageButton_22_clicked()
{
    int descriptor = 22;
    quint8 LGShellControlCommand = 0;
    quint8 commandBits[5];
    commandBits[0] = ui->checkBox22_1_0->isChecked();
    commandBits[1] = ui->checkBox22_1_1->isChecked();
    commandBits[2] = ui->checkBox22_1_2->isChecked();
    commandBits[3] = ui->checkBox22_1_3->isChecked();
    commandBits[4] = ui->checkBox22_1_4->isChecked();

    for(int i = 0; i < 5; ++i)
    {
        LGShellControlCommand += (commandBits[i] << i);
    }

    //qDebug() << LGShellControlCommand;

    Message22 message(LGShellControlCommand,
                      ui->lineEdit22_slTime1->text().toInt(),
                      ui->lineEdit22_slTime2->text().toInt(),
                      degreesToRawValue(ui->doubleSpinBox22_HorLeadAngle->value()),
                      degreesToRawValue(ui->doubleSpinBox22_VertLeadAngle->value()),
                      ui->lineEdit22_HorAngle->text().toInt(),
                      ui->lineEdit22_VertAngle->text().toInt());

    QByteArray payload;
    message.toBytes(&payload);

    sendMessage(payload, descriptor);

    QString codeCommand;
    QString timeKOD1 = ui->lineEdit22_slTime1->text();
    QString timeKOD2 = ui->lineEdit22_slTime2->text();
    QString angleAzimuth;
    QString angleElevation;

    this->LogString += ">Выполнена команда УПРАВЛЕНИЕ УАС\n";
    this->LogString += "с параметрами: \n";
    this->LogString += "-код команды=";
    this->LogString += codeCommand.setNum(LGShellControlCommand);
    this->LogString += "\n";
    this->LogString += "-время замедления КОД1=";
    this->LogString += timeKOD1;
    this->LogString += "\n";
    this->LogString += "-время замедления КОД2=";
    this->LogString += timeKOD2;
    this->LogString += "\n";
    this->LogString += "-угол упреждения по азимуту=";
    this->LogString += angleAzimuth.setNum(ui->doubleSpinBox22_HorLeadAngle->value());
    this->LogString += "\n";
    this->LogString += "-угол упреждения по углу места=";
    this->LogString += angleAzimuth.setNum(ui->doubleSpinBox22_VertLeadAngle->value());
    this->LogString += "\n";
    this->LogString += "-КДО по азимуту=";
    this->LogString += ui->lineEdit22_HorAngle->text();
    this->LogString += "\n";
    this->LogString += "-КДО по углу места=";
    this->LogString += ui->lineEdit22_VertAngle->text();
    this->LogString += "\n";

    this->ui->textBrowserLog->setText(this->LogString);


}//End of void MainWindow::on_sendMessageButton_22_clicked()

void MainWindow::on_sendMessageButton_23_clicked()
{
    int descriptor = 23;
    QByteArray payload;

    sendMessage(payload, descriptor);

    this->LogString += ">Выполнена команда ЗАПРОСИТЬ КООРДИНАТЫ ВИЗИРНОЙ ОСИ\n";

    this->ui->textBrowserLog->setText(this->LogString);

}//End of void MainWindow::on_sendMessageButton_23_clicked()


//
// Периодические сообщения
//
void MainWindow::sendMessage6()
{
    int descriptor = 6;
    QByteArray payload;
    mMessage6.toBytes(&payload);
    sendMessage(payload, descriptor);
}

void MainWindow::sendMessage7()
{
    int descriptor = 7;
    QByteArray payload;
    mMessage7.toBytes(&payload);
    sendMessage(payload, descriptor);
}

//
// Управление таймерами генерации периодических сообщений
//

void MainWindow::on_repeat6_toggled(bool checked)
{
    if(!checked)
    {
        timer6->stop();
    }
}

void MainWindow::on_repeat7_toggled(bool checked)
{
    if(!checked)
    {
        timer7->stop();
    }
}
//
// Обработчик нажатия кнопки ОЧИСТИТЬ
//
void MainWindow::on_pushButtonClear_clicked()
{
    this->LogString = "Выполнена операция ОЧИСТИТЬ ЖУРНАЛ\n";
    this->ui->textBrowserLog->setText(this->LogString);
}

//
// Обработчик нажатия кнопки СОХРАНИТЬ
//
void MainWindow::on_pushButtonSave_clicked()
{
    this->LogString += "Нажата кнопка СОХРАНИТЬ ЖУРНАЛ\n";
    this->ui->textBrowserLog->setText(this->LogString);

    static const char* const FILE_NAME = "Log.txt";
    QFile out(FILE_NAME);
    if(out.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&out);
        stream.setCodec("UTF-8");
        //stream << QObject::trUtf8("this->LogString");
        stream << this->LogString.toUtf8();
        out.close();
    }

}//End of void MainWindow::on_pushButtonSave_clicked()
