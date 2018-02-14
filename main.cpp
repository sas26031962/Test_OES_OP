#include "mainwindow.h"
#include <QApplication>

#ifdef __linux__
#include <QTextCodec>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef __linux__
    //Fixing Borders(Ubuntu issue)
    QApplication::setStyle("plastique");

    //Enabling Cyrillic
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");

    QTextCodec::setCodecForLocale(codec);// Строка для версии Qt 5.5.1
    //QTextCodec::setCodecForCStrings(codec); // Строка для версии Qt 4.8.6
    //qDebug() << "Heya, Linux! =D";
#endif

    MainWindow w;
    w.show();


    return a.exec();
}
