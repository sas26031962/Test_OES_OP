#include "degreeconverter.h"
#include <QDebug>

const int       maxRawValue     = 65536;  //equals 360° = 0° //uint16 max == 65535
const double    maxDegreeValue  = 360;

/*
int result = round(degree/degreeValueMax * rawValueMax);
dtrvTest(result, result);
*/
/*
void dtrvTest(quint16 angle, qint16 angSpeed)
{
    qDebug() << "quint16 angle: " << angle;
    qDebug() << "qint16 angSpeed: " << angSpeed;
}
*/

int degreesToRawValue(double degrees)
{
    /*
    double result = degree/360 * 65536;
    if(result > 0)
    {
        result +=0.5;
    }
    else
        if(result < 0)
        {
            result -= 0.5;
        }

    return result;
    */

    //return round(degree/360 * 65536);

    /*
    int result = round(degree/degreeValueMax * rawValueMax);
    qDebug() << "deg to raw: " << (qint32)result;

    if(returnPositive && result < 0)
    {
        //result += rawValueMax;    //alt way
        result = (quint16)result;
    }
    qDebug() << "actually sent value: " << result;

    return result;
    */

    return round(degrees/maxDegreeValue * maxRawValue);
}

double rawValueToDegrees(int rawValue)
{
    //return rawValue/(double)65536 * 360;
    return (double)rawValue/maxRawValue * maxDegreeValue;
}
