#ifndef MESSAGE_H
#define MESSAGE_H

#include <QtGlobal>
#include <QDataStream>
#include <QDebug>

#include "degreeconverter.h"


////Error code parsing function
//QString incorrectValueText(int value)
//{
//    return "Error: incorrect value " + QString::number(value);
//}
template<typename T>
QString incorrectValueText(T mParamValue)
{
    return "Incorrect Value [" + QString::number(mParamValue) + "]!";
}

////Bit accessor function
//Implementation has to be put into .cpp, unlike the template version
//bool getBit(quint8 bitSet,int bitIndex)
//{
//    qDebug() << "Uint8";
//    return (bitSet >> bitIndex) & 0b00000001;
//}
template<typename T>
bool getBit(T bitSet, quint8 bitIndex)
{
    return (bitSet >> bitIndex) & 0b1;
}


#pragma pack(push, 1)
////Incoming messages(from Fire Control System to Optical-Electronic System for Targeting and Detection)

class BaseMessage
{
    virtual int getID() = 0;
//    {
//        return 32;
//    }
};


////Video messages
class Message1
{
public:
    void setData(quint8 rFrequency,
                 quint8 rCompression)
    {
        mFrequency = rFrequency;
        mCompression = rCompression;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mFrequency;
        outStr << mCompression;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mFrequency;
        inStr >> mCompression;
    }

    //private:
    quint8 mFrequency;
    quint8 mCompression;
};


//class Message2
//{

//};

class Message3
{
public:
    Message3(quint16 rFilterSetting)
    {
        mFilterSetting = rFilterSetting;
    }

    void toBytes(QByteArray* payload)
    {
        QDataStream outStr(payload, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mFilterSetting;
    }

private:
    quint16 mFilterSetting;
};


class Message4
{
public:
    void setData(quint16 rMode)
    {
        mMode = rMode;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mMode;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mMode;
    }

    //private:
    quint16 mMode;
};

//class Message5

class Message6
{
public:
    void setData(quint16 rCoordSystem,
                 quint16 rHorAngle,
                 quint16 rVertAngle,
                 qint16 rHorAngularVelocity,
                 qint16 rVertAngularVelocity,
                 quint16 rFocusDistanceTV,
                 quint16 rExpositionTimeTV,
                 quint8 rMatrixAmpTV,
                 quint8 rContrastTV,
                 quint16 rFocusDistanceTHV,
                 quint16 rExpositionTimeTHV,
                 quint8 rMatrixAmpTHV,
                 quint8 rContrastTHV)
    {
        mCoordSystem = rCoordSystem;
        mHorAngle = rHorAngle;
        mVertAngle = rVertAngle;
        mHorAngularVelocity = rHorAngularVelocity;
        mVertAngularVelocity = rVertAngularVelocity;
        mFocusDistanceTV = rFocusDistanceTV;
        mExpositionTimeTV = rExpositionTimeTV;
        mMatrixAmpTV = rMatrixAmpTV;
        mContrastTV = rContrastTV;
        mFocusDistanceTHV = rFocusDistanceTHV;
        mExpositionTimeTHV = rExpositionTimeTHV;
        mMatrixAmpTHV = rMatrixAmpTHV;
        mContrastTHV = rContrastTHV;
    }
    
    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);
        
        outStr << mCoordSystem;
        outStr << mHorAngle;
        outStr << mVertAngle;
        outStr << mHorAngularVelocity;
        outStr << mVertAngularVelocity;
        outStr << mFocusDistanceTV;
        outStr << mExpositionTimeTV;
        outStr << mMatrixAmpTV;
        outStr << mContrastTV;
        outStr << mFocusDistanceTHV;
        outStr << mExpositionTimeTHV;
        outStr << mMatrixAmpTHV;
        outStr << mContrastTHV;
    }
    
    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);
        
        inStr >> mCoordSystem;
        inStr >> mHorAngle;
        inStr >> mVertAngle;
        inStr >> mHorAngularVelocity;
        inStr >> mVertAngularVelocity;
        inStr >> mFocusDistanceTV;
        inStr >> mExpositionTimeTV;
        inStr >> mMatrixAmpTV;
        inStr >> mContrastTV;
        inStr >> mFocusDistanceTHV;
        inStr >> mExpositionTimeTHV;
        inStr >> mMatrixAmpTHV;
        inStr >> mContrastTHV;
    }
    
    //    void print()
    //    {
    //        qDebug() << "mFields:";
    //        qDebug() << mCoordSystem;
    //        qDebug() << mHorAngle;
    //        qDebug() << mVertAngle;
    //        qDebug() << mHorAngularVelocity;
    //        qDebug() << mVertAngularVelocity;
    //        qDebug() << mFocusDistanceTV;
    //        qDebug() << mExpositionTimeTV;
    //        qDebug() << mMatrixAmpTV;
    //        qDebug() << mContrastTV;
    //        qDebug() << mFocusDistanceTHV;
    //        qDebug() << mExpositionTimeTHV;
    //        qDebug() << mMatrixAmpTHV;
    //        qDebug() << mContrastTHV;
    //    }
    
    //private:
    quint16 mCoordSystem;
    quint16 mHorAngle;
    quint16 mVertAngle;
    qint16 mHorAngularVelocity;
    qint16 mVertAngularVelocity;
    quint16 mFocusDistanceTV;
    quint16 mExpositionTimeTV;
    quint8 mMatrixAmpTV;
    quint8 mContrastTV;
    quint16 mFocusDistanceTHV;
    quint16 mExpositionTimeTHV;
    quint8 mMatrixAmpTHV;
    quint8 mContrastTHV;
};


class Message7
{
public:
    void setData(quint16 rCoordSystem,
                 qint16 rHorAngularVelocity,
                 qint16 rVertAngularVelocity,
                 quint16 rFocusDistanceTV,
                 quint16 rExpositionTimeTV,
                 quint8 rMatrixAmpTV,
                 quint8 rContrastTV,
                 quint16 rFocusDistanceTHV,
                 quint16 rExpositionTimeTHV,
                 quint8 rMatrixAmpTHV,
                 quint8 rContrastTHV)
    {
        mCoordSystem = rCoordSystem;
        mHorAngularVelocity = rHorAngularVelocity;
        mVertAngularVelocity = rVertAngularVelocity;
        mFocusDistanceTV = rFocusDistanceTV;
        mExpositionTimeTV = rExpositionTimeTV;
        mMatrixAmpTV = rMatrixAmpTV;
        mContrastTV = rContrastTV;
        mFocusDistanceTHV = rFocusDistanceTHV;
        mExpositionTimeTHV = rExpositionTimeTHV;
        mMatrixAmpTHV = rMatrixAmpTHV;
        mContrastTHV = rContrastTHV;
    }
    
    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);
        
        outStr << mCoordSystem;
        outStr << mHorAngularVelocity;
        outStr << mVertAngularVelocity;
        outStr << mFocusDistanceTV;
        outStr << mExpositionTimeTV;
        outStr << mMatrixAmpTV;
        outStr << mContrastTV;
        outStr << mFocusDistanceTHV;
        outStr << mExpositionTimeTHV;
        outStr << mMatrixAmpTHV;
        outStr << mContrastTHV;
    }
    
    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);
        
        inStr >> mCoordSystem;
        inStr >> mHorAngularVelocity;
        inStr >> mVertAngularVelocity;
        inStr >> mFocusDistanceTV;
        inStr >> mExpositionTimeTV;
        inStr >> mMatrixAmpTV;
        inStr >> mContrastTV;
        inStr >> mFocusDistanceTHV;
        inStr >> mExpositionTimeTHV;
        inStr >> mMatrixAmpTHV;
        inStr >> mContrastTHV;
    }
    
    //private:
    quint16 mCoordSystem;
    qint16 mHorAngularVelocity;
    qint16 mVertAngularVelocity;
    quint16 mFocusDistanceTV;
    quint16 mExpositionTimeTV;
    quint8 mMatrixAmpTV;
    quint8 mContrastTV;
    quint16 mFocusDistanceTHV;
    quint16 mExpositionTimeTHV;
    quint8 mMatrixAmpTHV;
    quint8 mContrastTHV;
};


class Message8
{
public:
    void setData(quint16 rCoordSystem,
                 quint16 rHorAngle,
                 quint16 rVertAngle,
                 quint16 rFocusDistanceTV,
                 quint16 rExpositionTimeTV,
                 quint8 rMatrixAmpTV,
                 quint8 rContrastTV,
                 quint16 rFocusDistanceTHV,
                 quint16 rExpositionTimeTHV,
                 quint8 rMatrixAmpTHV,
                 quint8 rContrastTHV)
    {
        mCoordSystem = rCoordSystem;
        mHorAngle = rHorAngle;
        mVertAngle = rVertAngle;
        mFocusDistanceTV = rFocusDistanceTV;
        mExpositionTimeTV = rExpositionTimeTV;
        mMatrixAmpTV = rMatrixAmpTV;
        mContrastTV = rContrastTV;
        mFocusDistanceTHV = rFocusDistanceTHV;
        mExpositionTimeTHV = rExpositionTimeTHV;
        mMatrixAmpTHV = rMatrixAmpTHV;
        mContrastTHV = rContrastTHV;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mCoordSystem;
        outStr << mHorAngle;
        outStr << mVertAngle;
        outStr << mFocusDistanceTV;
        outStr << mExpositionTimeTV;
        outStr << mMatrixAmpTV;
        outStr << mContrastTV;
        outStr << mFocusDistanceTHV;
        outStr << mExpositionTimeTHV;
        outStr << mMatrixAmpTHV;
        outStr << mContrastTHV;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mCoordSystem;
        inStr >> mHorAngle;
        inStr >> mVertAngle;
        inStr >> mFocusDistanceTV;
        inStr >> mExpositionTimeTV;
        inStr >> mMatrixAmpTV;
        inStr >> mContrastTV;
        inStr >> mFocusDistanceTHV;
        inStr >> mExpositionTimeTHV;
        inStr >> mMatrixAmpTHV;
        inStr >> mContrastTHV;
    }

    //private:
    quint16 mCoordSystem;
    quint16 mHorAngle;
    quint16 mVertAngle;
    quint16 mFocusDistanceTV;
    quint16 mExpositionTimeTV;
    quint8 mMatrixAmpTV;
    quint8 mContrastTV;
    quint16 mFocusDistanceTHV;
    quint16 mExpositionTimeTHV;
    quint8 mMatrixAmpTHV;
    quint8 mContrastTHV;
};

//class Message9

class Message10
{
public:
    void setData(quint8 rViewFieldTV,
                 quint8 rViewFieldTHV)
    {
        mViewFieldTV = rViewFieldTV;
        mViewFieldTHV = rViewFieldTHV;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mViewFieldTV;
        outStr << mViewFieldTHV;
    }

    /*
    QByteArray& toBytes()
    {
        QByteArray sequence;
        QDataStream outStr(&sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mViewFieldTV;
        outStr << mViewFieldTHV;

        return sequence;
    }
    */

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mViewFieldTV;
        inStr >> mViewFieldTHV;
    }

    //private:
    quint8 mViewFieldTV;
    quint8 mViewFieldTHV;
};

class Message11
{
public:
    void setData(quint8 rMaxTargetAmount,
                 quint16 rMinDistanceStrobe,
                 quint16 rMaxDistanceStrobe)
    {
        mMaxTargetAmount = rMaxTargetAmount;
        mMinDistanceStrobe = rMinDistanceStrobe;
        mMaxDistanceStrobe = rMaxDistanceStrobe;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mMaxTargetAmount;
        outStr << mMinDistanceStrobe;
        outStr << mMaxDistanceStrobe;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mMaxTargetAmount;
        inStr >> mMinDistanceStrobe;
        inStr >> mMaxDistanceStrobe;
    }

    //private:
    quint8 mMaxTargetAmount;
    quint16 mMinDistanceStrobe;
    quint16 mMaxDistanceStrobe;
};


class Message12
{
public:
    Message12(quint16 rHeatingTime)
    {
        mHeatingTime = rHeatingTime;
    }

    void toBytes(QByteArray* payload)
    {
        QDataStream outStr(payload, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mHeatingTime;
    }

private:
    quint16 mHeatingTime;
};

//class Message13
//class Message14
//class Message15
//class Message16
//class Message17


class Message18
{
public:
    void setData(quint32 rParamIndex,
                 quint32 rParamValue)
    {
        mParamIndex = rParamIndex;
        mParamValue = rParamValue;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mParamIndex;
        outStr << mParamValue;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mParamIndex;
        inStr >> mParamValue;
    }

    //private:
    quint32 mParamIndex;
    quint32 mParamValue;
};


class Message19
{
public:
    void setData(quint32 rReqParamIndex)
    {
        mReqParamIndex = rReqParamIndex;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mReqParamIndex;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mReqParamIndex;
    }

    //private:
    quint32 mReqParamIndex;
};


//class Message20
//class Message21


//class Message22
//{
//public:
//    void setData(quint16 rLGShellCommand,
//                 quint16 rCommandParam)
//    {
//        mLGShellCommand = rLGShellCommand;
//        mCommandParam = rCommandParam;
//    }

//    void toBytes(QByteArray* sequence)
//    {
//        QDataStream outStr(sequence, QIODevice::WriteOnly);
//        outStr.setByteOrder(QDataStream::LittleEndian);

//        outStr << mLGShellCommand;
//        outStr << mCommandParam;
//    }

//    void fromBytes(QByteArray* sequence)
//    {
//        QDataStream inStr(sequence, QIODevice::ReadOnly);
//        inStr.setByteOrder(QDataStream::LittleEndian);

//        inStr >> mLGShellCommand;
//        inStr >> mCommandParam;
//    }

//    //private:
//    quint16 mLGShellCommand;
//    quint16 mCommandParam;
//};


class Message22
{
public:
    Message22(quint8 rLGShellControlCommand,
              quint8 rSlowDownTime1,
              quint8 rSlowDownTime2,
              quint16 rHorLeadAngle,
              quint16 rVertLeadAngle,
              quint8 rHorAngle,
              quint8 rVertAngle)
    {
        mLGShellControlCommand = rLGShellControlCommand;
        mSlowDownTime1 = rSlowDownTime1;
        mSlowDownTime2 = rSlowDownTime2;
        mHorLeadAngle = rHorLeadAngle;
        mVertLeadAngle = rVertLeadAngle;
        mHorAngle = rHorAngle;
        mVertAngle = rVertAngle;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mLGShellControlCommand;
        outStr << mSlowDownTime1;
        outStr << mSlowDownTime2;
        outStr << mHorLeadAngle;
        outStr << mVertLeadAngle;
        outStr << mHorAngle;
        outStr << mVertAngle;
    }

private:
    quint8 mLGShellControlCommand;
    quint8 mSlowDownTime1;
    quint8 mSlowDownTime2;
    quint16 mHorLeadAngle;
    quint16 mVertLeadAngle;
    quint8 mHorAngle;
    quint8 mVertAngle;
};


//class Message23


////Outcoming messages(from Optical-Electronic System for Targeting and Detection to Fire Control System)

////Video messages
class Message101
{
public:
    void setData(quint16 rFrameNumber,
                 qint32 rTimeSec,
                 qint32 rTimeNsec,
                 quint16 rHorAngle,
                 quint16 rVertAngle,
                 qint16 rHorAngularVelocity,
                 qint16 rVertAngularVelocity,
                 quint16 rTDeviceMode,
                 quint8 rLoSMovementMode,
                 quint8 rViewField,
                 quint16 rFocusDistance,
                 quint16 rExpositionTime,
                 quint8 rMatrixAmp,
                 quint8 rContrast)
    {
        mFrameNumber = rFrameNumber;
        mTimeSec = rTimeSec;
        mTimeNsec = rTimeNsec;
        mHorAngle = rHorAngle;
        mVertAngle = rVertAngle;
        mHorAngularVelocity = rHorAngularVelocity;
        mVertAngularVelocity = rVertAngularVelocity;
        mTDeviceMode = rTDeviceMode;
        mLoSMovementMode = rLoSMovementMode;
        mViewField = rViewField;
        mFocusDistance = rFocusDistance;
        mExpositionTime = rExpositionTime;
        mMatrixAmp = rMatrixAmp;
        mContrast = rContrast;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mFrameNumber;
        outStr << mTimeSec;
        outStr << mTimeNsec;
        outStr << mHorAngle;
        outStr << mVertAngle;
        outStr << mHorAngularVelocity;
        outStr << mVertAngularVelocity;
        outStr << mTDeviceMode;
        outStr << mLoSMovementMode;
        outStr << mViewField;
        outStr << mFocusDistance;
        outStr << mExpositionTime;
        outStr << mMatrixAmp;
        outStr << mContrast;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mFrameNumber;
        inStr >> mTimeSec;
        inStr >> mTimeNsec;
        inStr >> mHorAngle;
        inStr >> mVertAngle;
        inStr >> mHorAngularVelocity;
        inStr >> mVertAngularVelocity;
        inStr >> mTDeviceMode;
        inStr >> mLoSMovementMode;
        inStr >> mViewField;
        inStr >> mFocusDistance;
        inStr >> mExpositionTime;
        inStr >> mMatrixAmp;
        inStr >> mContrast;
    }

    QString parse()
    {
        QString parsedMessage;
        parsedMessage += "Начало кадра (101)";

        /*
        parsedMessage += "\nНомер кадра: " + QString::number(mFrameNumber);
        parsedMessage += "\nВремя съема: " + QString::number(mTimeSec) + ":" + QString::number(mTimeNsec);
        parsedMessage += "\nУгол поворота прицела /азимут: " + QString::number(mHorAngle);
        parsedMessage += "\nУгол подъёма прицела / угол места: " + QString::number(mVertAngle);
        parsedMessage += "\nУгловая скорость поворота / по азимуту: " + QString::number(mHorAngularVelocity);
        parsedMessage += "\nУгловая скорость подъёма / по углу места: " + QString::number(mVertAngularVelocity);

        parsedMessage += "\nРежим прицела: ";

        parsedMessage += "\nрежим: ";
        switch(mTDeviceMode & 0x03)//0b 0000 0000 0000 0011
        {
        case 0:
            parsedMessage += "дежурный";
            break;
        case 1:
            parsedMessage += "рабочий";
            break;
        case 2:
            parsedMessage += "технологический";
            break;
        default:
            parsedMessage += errIncVal(mTDeviceMode & 0x03);
            break;
        }

        parsedMessage += "\nпривода: ";
        if(mTDeviceMode & 0x04)
        {
            parsedMessage += "вкл";
        }
        else
        {
            parsedMessage += "откл";
        }

        parsedMessage += "\nТВ матрица: ";
        if(mTDeviceMode & 0x08)
        {
            parsedMessage += "вкл";
        }
        else
        {
            parsedMessage += "откл";
        }

        parsedMessage += "\nсостояние ТПВ матрицы: ";
        switch((mTDeviceMode & 0x30) >> 4)//0b 0000 0000 0011 0000
        {
        case 0:
            parsedMessage += "отключена";
            break;
        case 1:
            parsedMessage += "включается";
            break;
        case 2:
            parsedMessage += "включена";
            break;
        case 4:
            parsedMessage += "отключается";
            break;
        }

        parsedMessage += "\nЛД готов: ";
        if((mTDeviceMode & 0x40) >> 4)
        {
            parsedMessage += "да";
        }
        else
        {
            parsedMessage += "нет";
        }

        parsedMessage += "\nЛЛКУ готов: ";
        if((mTDeviceMode & 0x80) >> 4)
        {
            parsedMessage += "да";
        }
        else
        {
            parsedMessage += "нет";
        }

        parsedMessage += "\nпрограмма упр. УАС через ЛЛКУ: ";
        if((mTDeviceMode & 0x100) >> 8)
        {
            parsedMessage += "да";
        }
        else
        {
            parsedMessage += "нет";
        }

        parsedMessage += "\nсистема координат: ";
        if((mTDeviceMode & 0x200) >> 8)
        {
            parsedMessage += "ЛСК";
        }
        else
        {
            parsedMessage += "ЗСК";
        }

        parsedMessage += "\nСпособ движения линии визирования прицела: ";
        switch(mLoSMovementMode)
        {
        case 0:
            parsedMessage += "Стабилизация";
            break;
        case 1:
            parsedMessage += "Сопровождение по координатам и скоростям";
            break;
        case 2:
            parsedMessage += "Сопровождение с заданными скоростями";
            break;
        case 3:
            parsedMessage += "Переброс по координатам";
            break;
        case 4:
            parsedMessage += "Транспортное положение";
            break;
        default:
            parsedMessage += errIncVal(mLoSMovementMode);
            break;
        }

        parsedMessage += "\nПоле зрения прицела: ";
        switch(mViewField)
        {
        case 0:
            parsedMessage += "ОПЗ";
            break;
        case 1:
            parsedMessage += "ШПЗ";
            break;
        case 2:
            parsedMessage += "УПЗ";
            break;
        case 3:
            parsedMessage += "УПЗx2";
            break;
        default:
            parsedMessage += errIncVal(mViewField);
            break;
        }

        parsedMessage += "\nФокусное расстояние: " + QString::number(mFocusDistance);
        if(mFocusDistance)
        {
            parsedMessage += "(ручная фокусировка)";
        }
        else
        {
            parsedMessage += "(автофокусировка)";
        }

        parsedMessage += "\nВремя экспозиции: " + QString::number(mExpositionTime);
        switch(mExpositionTime)
        {
        case 0:
            parsedMessage += "(автоматическое при слежении)";
            break;
        case 1:
            parsedMessage += "(автоматическое при сканировании)";
            break;
        default:
            parsedMessage += "(ручная[от (2) до (65535)])";
            break;
        }

        parsedMessage += "\nУсиление матрицы: " + QString::number(mMatrixAmp);
        switch(mMatrixAmp)
        {
        case 0:
            parsedMessage += "автоматически";
            break;
        default:
            parsedMessage += "ручной[от (1) до (255)]";
            break;
        }

        parsedMessage += "\nКонтрастность: " + QString::number(mContrast);
        switch(mContrast)
        {
        case 0:
            parsedMessage += "(автоматическая)";
            break;
        case 255:
            parsedMessage += "(не изменяется)";
            break;
        default:
            parsedMessage += "(" + errIncVal(mContrast) + ")";
            break;
        }
*/

        return parsedMessage;
    }

private:
    quint16 mFrameNumber;
    qint32 mTimeSec;
    qint32 mTimeNsec;
    quint16 mHorAngle;
    quint16 mVertAngle;
    qint16 mHorAngularVelocity;
    qint16 mVertAngularVelocity;
    quint16 mTDeviceMode;
    quint8 mLoSMovementMode;
    quint8 mViewField;
    quint16 mFocusDistance;
    quint16 mExpositionTime;
    quint8 mMatrixAmp;
    quint8 mContrast;
};


class Message102
{
public:
    void setData(quint16 rFrameNumber,
                 quint16 rPacketAmount,
                 quint16 rCompression,
                 quint16 rColorDepth,
                 quint16 rFrameWidth,
                 quint16 rFrameHeight,
                 quint32 rUncompressedFrameSize,
                 quint32 rCompressedFrameSize)
    {
        mFrameNumber = rFrameNumber;
        mPacketAmount = rPacketAmount;
        mCompression = rCompression;
        mColorDepth = rColorDepth;
        mFrameWidth = rFrameWidth;
        mFrameHeight = rFrameHeight;
        mUncompressedFrameSize = rUncompressedFrameSize;
        mCompressedFrameSize = rCompressedFrameSize;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mFrameNumber;
        outStr << mPacketAmount;
        outStr << mCompression;
        outStr << mColorDepth;
        outStr << mFrameWidth;
        outStr << mFrameHeight;
        outStr << mUncompressedFrameSize;
        outStr << mCompressedFrameSize;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mFrameNumber;
        inStr >> mPacketAmount;
        inStr >> mCompression;
        inStr >> mColorDepth;
        inStr >> mFrameWidth;
        inStr >> mFrameHeight;
        inStr >> mUncompressedFrameSize;
        inStr >> mCompressedFrameSize;
    }

    QString parse()
    {
        QString parsedMessage;
        parsedMessage += "Начало данных видеопотока (102)";

        /*
        parsedMessage += "\nНомер кадра: " + QString::number(mFrameNumber);
        parsedMessage += "\nКоличество пакетов в кадре: " + QString::number(mPacketAmount);
        parsedMessage += "\nСжатие: " + QString::number(mCompression);
        parsedMessage += "\nГлубина цвета : " + QString::number(mColorDepth);
        parsedMessage += "\nГоризонтальный размер изображения: " + QString::number(mFrameWidth);
        parsedMessage += "\nВертикальный размер изображения: " + QString::number(mFrameHeight);
        parsedMessage += "\nРазмер несжатого фрейма: " + QString::number(mUncompressedFrameSize);
        parsedMessage += "\nРазмер сжатого фрейма: " + QString::number(mCompressedFrameSize);
        */

        return parsedMessage;
    }

private:
    quint16 mFrameNumber;
    quint16 mPacketAmount;
    quint16 mCompression;
    quint16 mColorDepth;
    quint16 mFrameWidth;
    quint16 mFrameHeight;
    quint32 mUncompressedFrameSize;
    quint32 mCompressedFrameSize;
};


class Message103
{
public:
    QString parse()
    {
        QString parsedMessage;
        parsedMessage += "Данные кадра видеопотока (103)";

        return parsedMessage;
    }
};


class Message104
{
public:
    QString parse()
    {
        QString parsedMessage;
        parsedMessage += "Окончание кадра видеопотока (104)";

        return parsedMessage;
    }
};


////Control messages
class Message105
{
public:
    void setData(quint16 rHorAngle,
                 quint16 rVertAngle,
                 qint16 rHorAngularVelocity,
                 qint16 rVertAngularVelocity,
                 quint8 rStreamStateTV,
                 quint8 rStreamStateTHV,
                 quint8 rTDeviceMode1,
                 quint8 rTDeviceMode2,
                 quint8 rLoSMovementMode,
                 quint8 rViewFieldTV,
                 quint8 rViewFieldTHV)
    {
        mHorAngle = rHorAngle;
        mVertAngle = rVertAngle;
        mHorAngularVelocity = rHorAngularVelocity;
        mVertAngularVelocity = rVertAngularVelocity;
        mStreamStateTV = rStreamStateTV;
        mStreamStateTHV = rStreamStateTHV;
        mTDeviceMode1 = rTDeviceMode1;
        mTDeviceMode2 = rTDeviceMode2;
        mLoSMovementMode = rLoSMovementMode;
        mViewFieldTV = rViewFieldTV;
        mViewFieldTHV = rViewFieldTHV;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mHorAngle;
        outStr << mVertAngle;
        outStr << mHorAngularVelocity;
        outStr << mVertAngularVelocity;
        outStr << mStreamStateTV;
        outStr << mStreamStateTHV;
        outStr << mTDeviceMode1;
        outStr << mTDeviceMode2;
        outStr << mLoSMovementMode;
        outStr << mViewFieldTV;
        outStr << mViewFieldTHV;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mHorAngle;
        inStr >> mVertAngle;
        inStr >> mHorAngularVelocity;
        inStr >> mVertAngularVelocity;
        inStr >> mStreamStateTV;
        inStr >> mStreamStateTHV;
        inStr >> mTDeviceMode1;
        inStr >> mTDeviceMode2;
        inStr >> mLoSMovementMode;
        inStr >> mViewFieldTV;
        inStr >> mViewFieldTHV;
    }

    QString parse()
    {
        QString parsedMessage;
        parsedMessage += "Состояние прицела (105)";

        char format = 'f';
        int precision = 3;

        parsedMessage += "\nГор. угол: " + //"\nУгол поворота прицела/азимут: " +
                QString::number(rawValueToDegrees(mHorAngle), format, precision)
                + "°";

        parsedMessage += "\nВерт. угол: " + //"\nУгол подъёма прицела/угол места: " +
                QString::number(rawValueToDegrees(mVertAngle), format, precision)
                + "°";

        parsedMessage += "\nГор. угл. скорость: " + //"\nУгл. скорость поворота/по азимуту: " +
                QString::number(rawValueToDegrees(mHorAngularVelocity), format, precision)
                + "°/с";

        parsedMessage += "\nВерт. угл. скорость: " + //"\nУгл. скорость подъёма/по углу места: " +
                QString::number(rawValueToDegrees(mVertAngularVelocity), format, precision)
                + "°/с";

        parsedMessage += "\nСостояние ТВ потока:  ";
        switch(mStreamStateTV)
        {
        case 0:
            parsedMessage += "включен";
            break;
        case 1:
            parsedMessage += "отключен";
            break;
        default:
            parsedMessage += incorrectValueText(mStreamStateTV);
            break;
        }

        parsedMessage += "\nСостояние ТПВ потока: ";
        switch(mStreamStateTHV)
        {
        case 0:
            parsedMessage += "включен";
            break;
        case 1:
            parsedMessage += "отключен";
            break;
        default:
            parsedMessage += incorrectValueText(mStreamStateTHV);
            break;
        }
        parsedMessage += "\n";

        parsedMessage += "\nРежим: ";
        switch(mTDeviceMode1 & 0x03)//0b 0000 0000 0000 0011
        {
        case 0:
            parsedMessage += "дежурный";
            break;
        case 1:
            parsedMessage += "рабочий";
            break;
        case 2:
            parsedMessage += "технологический";
            break;
        default:
            parsedMessage += incorrectValueText(mTDeviceMode1 & 0x03);
            break;
        }

        parsedMessage += "\nПривода: ";
        if(getBit(mTDeviceMode1, 2))
        {
            parsedMessage += "включены";
        }
        else
        {
            parsedMessage += "отключены";
        }

        parsedMessage += "\nТВ матрица: ";
        if(getBit(mTDeviceMode1, 3))
        {
            parsedMessage += "включена";
        }
        else
        {
            parsedMessage += "отключена";
        }

        parsedMessage += "\nТПВ матрица: ";
        switch((mTDeviceMode1 & 0x30) >> 4)//0b 0000 0000 0011 0000
        {
        case 0:
            parsedMessage += "отключена";
            break;
        case 1:
            parsedMessage += "включается";
            break;
        case 2:
            parsedMessage += "включена";
            break;
        case 4:
            parsedMessage += "отключается";
            break;
        }

        parsedMessage += "\nЛД готов: ";
        if(getBit(mTDeviceMode1, 6))
        {
            parsedMessage += "да";
        }
        else
        {
            parsedMessage += "нет";
        }

        parsedMessage += "\nЛЛКУ готов: ";
        if(getBit(mTDeviceMode1, 7))
        {
            parsedMessage += "да";
        }
        else
        {
            parsedMessage += "нет";
        }

        parsedMessage += "\nПрограмма упр. УАС через ЛЛКУ: ";
        if(getBit(mTDeviceMode2, 0))
        {
            parsedMessage += "1";//"да";
        }
        else
        {
            parsedMessage += "0";//"нет";
        }

        parsedMessage += "\nСистема координат: ";
        if(getBit(mTDeviceMode2, 1))
        {
            parsedMessage += "ЗСК";
        }
        else
        {
            parsedMessage += "ЛСК";
        }

        quint8 opticFilter = (getBit(mTDeviceMode2, 3) << 1) + getBit(mTDeviceMode2, 2);
        parsedMessage += "\nОптический фильтр ТВ канала: ";
        switch(opticFilter)
        {
        case 0:
            parsedMessage += "нет фильтра";
            break;
        case 1:
            parsedMessage += "1-й фильтр";
            break;
        case 2:
            parsedMessage += "2-й фильтр";
            break;
        case 3:
            parsedMessage += "3-й фильтр";
            break;
        }

        parsedMessage += "\nОбогрев стекла: ";
        if(getBit(mTDeviceMode2, 4))
        {
            parsedMessage += "включен";
        }
        else
        {
            parsedMessage += "отключен";
        }

        parsedMessage += "\n\nСпособ движения линии визирования: ";
        switch(mLoSMovementMode)
        {
        case 0:
            parsedMessage += "Стабилизация";
            break;
        case 1:
            parsedMessage += "Сопровождение по координатам и скоростям";
            break;
        case 2:
            parsedMessage += "Сопровождение с заданными скоростями";
            break;
        case 3:
            parsedMessage += "Переброс по координатам";
            break;
        case 4:
            parsedMessage += "Транспортное положение";
            break;
        default:
            parsedMessage += incorrectValueText(mLoSMovementMode);
            break;
        }
        parsedMessage += "\n";

        parsedMessage += "\nПоле зрения ТВ: ";
        switch(mViewFieldTV)
        {
        case 0:
            parsedMessage += "ОПЗ";
            break;
        case 1:
            parsedMessage += "ШПЗ";
            break;
        case 2:
            parsedMessage += "УПЗ";
            break;
        case 3:
            parsedMessage += "УПЗx2";
            break;
        default:
            parsedMessage += incorrectValueText(mViewFieldTV);
            break;
        }

        parsedMessage += "\nПоле зрения ТПВ: ";
        switch(mViewFieldTHV)
        {
        case 0:
            parsedMessage += "ОПЗ";
            break;
        case 1:
            parsedMessage += "ШПЗ";
            break;
        case 2:
            parsedMessage += "УПЗ";
            break;
        case 3:
            parsedMessage += "УПЗx2";
            break;
        default:
            parsedMessage += incorrectValueText(mViewFieldTHV);
            break;
        }

        return parsedMessage;
    }

    //private:
    quint16 mHorAngle;
    quint16 mVertAngle;
    qint16 mHorAngularVelocity;
    qint16 mVertAngularVelocity;
    quint8 mStreamStateTV;
    quint8 mStreamStateTHV;
    quint8 mTDeviceMode1;
    quint8 mTDeviceMode2;
    quint8 mLoSMovementMode;
    quint8 mViewFieldTV;
    quint8 mViewFieldTHV;
};


class Message106
{
public:
    void setData(quint16 rExecutedCommandID)
    {
        mExecutedCommandID = rExecutedCommandID;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mExecutedCommandID;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mExecutedCommandID;
    }

    QString parse()
    {
        QString parsedMessage;
        parsedMessage += "Команда исполнена (106)";
        parsedMessage += "\nИсполненная команда: " + QString::number(mExecutedCommandID);

        return parsedMessage;
    }

    //private:
    quint16 mExecutedCommandID;
};


class Message107//bit set!
{
public:
    void setData(quint32 rErrorCode)
    {
        mErrorCode = rErrorCode;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mErrorCode;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mErrorCode;
    }


    QString parse()
    {
        QString parsedMessage;

        const quint8 bitAmount = 16;

        quint8 stateBits[bitAmount];
        for(int i = 0; i < bitAmount; ++i)
        {
            stateBits[i] = ((mErrorCode >> i) & 0x1);
        }


        QString errorCodes[bitAmount];
        errorCodes[0] = "готовность БУ";
        errorCodes[1] = "готовность ТВ";
        errorCodes[2] = "готовность ТПВ";
        errorCodes[3] = "готовность ЛЛКУ";
        errorCodes[4] = "готовность ЛД";
        errorCodes[5] = "резерв";
        errorCodes[6] = "резерв";
        errorCodes[7] = "готовность привода";
        errorCodes[8] = "неисправность БУ";
        errorCodes[9] = "неисправность ТВ";
        errorCodes[10] = "неисправность ТПВ";
        errorCodes[11] = "неисправность ЛЛКУ";
        errorCodes[12] = "неисправность ЛД";
        errorCodes[13] = "резерв";
        errorCodes[14] = "резерв";
        errorCodes[15] = "неисправность приводов";


        parsedMessage += "Код ошибки (107): ";
        for(int i = 0; i < bitAmount; ++i)
        {
            parsedMessage +=
                    "\n" + errorCodes[i] + ": " + QString::number(stateBits[i]);
        }

        return parsedMessage;
    }

    //private:
    quint32 mErrorCode;
};


class Message108
{
public:
    void setData(quint32 rCycleAmount)
    {
        mCycleAmount = rCycleAmount;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mCycleAmount;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mCycleAmount;
    }

    QString parse()
    {
        QString parsedMessage;
        parsedMessage += "Наработка ЛЛКУ (108)";

        parsedMessage += "\nКоличество циклов: " + QString::number(mCycleAmount);

        return parsedMessage;
    }

    //private:
    quint32 mCycleAmount;
};


class Message109
{
public:
    void setData(quint32 rCycleAmount)
    {
        mCycleAmount = rCycleAmount;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mCycleAmount;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mCycleAmount;
    }

    QString parse()
    {
        QString parsedMessage;
        parsedMessage += "Наработка ЛД (109)";

        parsedMessage += "\nКоличество циклов: " + QString::number(mCycleAmount);

        return parsedMessage;
    }

    //private:
    quint32 mCycleAmount;
};


class Message110
{
public:
    void setData(quint32 rTimeSec,
                 quint32 rTimeNsec,
                 quint16 rMeasureAmount,
                 quint16 rDistanceToTarget
                 /*QVector<quint16> rDistanceToTarget*/)
    {
        mTimeSec = rTimeSec;
        mTimeNsec = rTimeNsec;
        mMeasureAmount = rMeasureAmount;

        mDistanceToTarget.resize(rMeasureAmount);

        for(int i = 0; i < mMeasureAmount; ++i)
        {
            //mDistanceToTarget[i] = rDistanceToTarget[i];
            mDistanceToTarget[i] = rDistanceToTarget;
        }
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mTimeSec;
        outStr << mTimeNsec;
        outStr << mMeasureAmount;

        for(int i = 0; i < mMeasureAmount; ++i)
        {
            outStr << mDistanceToTarget[i];
        }
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mTimeSec;
        inStr >> mTimeNsec;
        inStr >> mMeasureAmount;

        mDistanceToTarget.resize(mMeasureAmount);
        for(int i = 0; i < mMeasureAmount; ++i)
        {
            inStr >> mDistanceToTarget[i];
        }
    }

    QString parse()
    {
        QString parsedMessage;
        parsedMessage += "Измеренная дальность (110)";

        parsedMessage += "\nВремя измерения: " + QString::number(mTimeSec);
        parsedMessage += "\nВремя измерения: " + QString::number(mTimeNsec);
        parsedMessage += "\nКоличество целей: " + QString::number(mMeasureAmount);

        for(int i = 0; i < mMeasureAmount; ++i)
        {
            parsedMessage += "\nРасстояние до цели: "
                    + QString::number(i + 1)
                    + QString::number(mDistanceToTarget[i]);
        }

        return parsedMessage;
    }

    //private:
    quint32 mTimeSec;
    quint32 mTimeNsec;
    quint16 mMeasureAmount;
    QVector<quint16> mDistanceToTarget;
};


class Message111
{
public:
    QString parse()
    {
        QString parsedMessage;
        parsedMessage += "Диагностика (111)";

        return parsedMessage;
    }
};


class Message112
{
public:
    void setData(quint32 rParamIndex,
                 qint32 rParamValue)
    {
        mParamIndex = rParamIndex;
        mParamValue = rParamValue;
    }

    void toBytes(QByteArray* sequence)
    {
        QDataStream outStr(sequence, QIODevice::WriteOnly);
        outStr.setByteOrder(QDataStream::LittleEndian);

        outStr << mParamIndex;
        outStr << mParamValue;
    }

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> mParamIndex;
        inStr >> mParamValue;
    }



    QString parse()
    {
        QString parsedMessage;
        parsedMessage += "Значение параметра (112)";
        parsedMessage += "\nНомер передаваемого параметра: " + QString::number(mParamIndex);
        parsedMessage += "\nЗначение передаваемого параметра: " + QString::number(mParamValue);

        parsedMessage += "\n\n";

        switch(mParamIndex)
        {
        case 0:
            parsedMessage += "Код ошибки";
            break;
        case 256:
            parsedMessage += "Юстировочный угол δψ";
            break;
        case 257:
            parsedMessage += "Юстировочный угол δθ";
            break;
        case 258:
            parsedMessage += "Юстировочный угол δγ";
            break;
        case 259:
            parsedMessage += "Компенсация собственного дрейфа гироскопа ОЭС ОП по вертикали (Увод ВН)";
            break;
        case 300:
            parsedMessage += "Компенсация собственного дрейфа гироскопа ОЭС ОП по горизонту (Увод ГН)";
            break;
        case 301:
            parsedMessage += "Система координат ОЭС ОП";
            break;
        case 302:
            parsedMessage += "Нулевое положение ОЭС ОП по ВН (Ноль ОЭС ОП ВН)";
            break;
        case 303:
            parsedMessage += "Нулевое положение ОЭС ОП по ГН (Ноль ОЭС ОП ГН)";
            break;
        default:
            if(mParamIndex >= 1 && mParamIndex <= 255)
            {
                parsedMessage += "Кнопка АРМ[скан-код: " + QString::number(mParamIndex) + "]";
            }
            else
            {
                parsedMessage += incorrectValueText(mParamIndex);
            }
            break;
        }

        parsedMessage += ": ";

        switch(mParamIndex)
        {
        case 0:
        {
            parsedMessage += QString::number(mParamValue);

            break;
        }

        case 256:
        case 257:
        case 258:
        case 302:
        case 303:
        {
            char format = 'f';
            int precision = 3;

            parsedMessage += QString::number(
                        rawValueToDegrees(mParamValue), format, precision
                        ) + "°";
            break;
        }

        case 259:
        case 300:
            union
            {
                quint32 val;
                float fVal;
            };
            val = mParamValue;

            parsedMessage += QString::number(fVal) + "°";
            break;

        case 301:
        {
            switch(mParamValue)
            {
            case 0:
                parsedMessage += "ЛСК";
                break;
            case 1:
                parsedMessage += "ЗСК";
                break;
            default:
                parsedMessage += incorrectValueText(mParamValue);
            }

            break;
        }

        default:
            if(mParamIndex >= 1 && mParamIndex <= 255)
            {
                switch(mParamValue)
                {
                case 1:
                    parsedMessage += "кнопка нажата";
                    break;
                case 2:
                    parsedMessage += "кнопка отжата";
                    break;
                default:
                    parsedMessage += incorrectValueText(mParamValue);
                }
            }
            else
            {
                parsedMessage += incorrectValueText(mParamValue);
            }
            break;
        }

        return parsedMessage;
    }

    //private:
    quint32 mParamIndex;
    qint32 mParamValue;
};


struct LoSCoord
{
    qint16 mNarrVFx2Y;//zoomed
    qint16 mNarrVFx2X;
    qint16 mNarrVFY;
    qint16 mNarrVFX;
    qint16 mBroadVFY;
    qint16 mBroadVFX;
    qint16 mObsVFY;
    qint16 mObsVFX;
};

class Message113
{
public:

    void fromBytes(QByteArray* sequence)
    {
        QDataStream inStr(sequence, QIODevice::ReadOnly);
        inStr.setByteOrder(QDataStream::LittleEndian);

        inStr >> TVLoS.mNarrVFx2Y;
        inStr >> TVLoS.mNarrVFx2X;
        inStr >> TVLoS.mNarrVFY;
        inStr >> TVLoS.mNarrVFX;
        inStr >> TVLoS.mBroadVFY;
        inStr >> TVLoS.mBroadVFX;
        inStr >> TVLoS.mObsVFY;
        inStr >> TVLoS.mObsVFX;

        inStr >> THVLoS.mNarrVFx2Y;
        inStr >> THVLoS.mNarrVFx2X;
        inStr >> THVLoS.mNarrVFY;
        inStr >> THVLoS.mNarrVFX;
        inStr >> THVLoS.mBroadVFY;
        inStr >> THVLoS.mBroadVFX;
        inStr >> THVLoS.mObsVFY;
        inStr >> THVLoS.mObsVFX;
    }

    QString parse()
    {
        QString parsedMessage;
        parsedMessage += "Координаты визирной оси (113)";

        parsedMessage += "\n\n ТВ Канал:";
        parsedMessage += "\nВертикальная координата УПЗx2: " + QString::number(TVLoS.mNarrVFx2Y);
        parsedMessage += "\nГоризонтальная координата УПЗx2: " + QString::number(TVLoS.mNarrVFx2X);
        parsedMessage += "\nВертикальная координата УПЗ: " + QString::number(TVLoS.mNarrVFY);
        parsedMessage += "\nГоризонтальная координата УПЗ: " + QString::number(TVLoS.mNarrVFX);
        parsedMessage += "\nВертикальная координата ШПЗ: " + QString::number(TVLoS.mBroadVFY);
        parsedMessage += "\nГоризонтальная координата ШПЗ: " + QString::number(TVLoS.mBroadVFX);
        parsedMessage += "\nВертикальная координата ОПЗ: " + QString::number(TVLoS.mObsVFY);
        parsedMessage += "\nГоризонтальная координата ОПЗ: " + QString::number(TVLoS.mObsVFX);

        parsedMessage += "\n\n ТПВ Канал:";
        parsedMessage += "\nВертикальная координата УПЗx2: " + QString::number(THVLoS.mNarrVFx2Y);
        parsedMessage += "\nГоризонтальная координата УПЗx2: " + QString::number(THVLoS.mNarrVFx2X);
        parsedMessage += "\nВертикальная координата УПЗ: " + QString::number(THVLoS.mNarrVFY);
        parsedMessage += "\nГоризонтальная координата УПЗ: " + QString::number(THVLoS.mNarrVFX);
        parsedMessage += "\nВертикальная координата ШПЗ: " + QString::number(THVLoS.mBroadVFY);
        parsedMessage += "\nГоризонтальная координата ШПЗ: " + QString::number(THVLoS.mBroadVFX);
        parsedMessage += "\nВертикальная координата ОПЗ: " + QString::number(THVLoS.mObsVFY);
        parsedMessage += "\nГоризонтальная координата ОПЗ: " + QString::number(THVLoS.mObsVFX);

        return parsedMessage;
    }

    //private:
    LoSCoord TVLoS;
    LoSCoord THVLoS;
};

//class Message113
//{
//public:
//    void setData(qint16 rNarrVFx2Y,
//                 qint16 rNarrVFx2X,
//                 qint16 rNarrVFY,
//                 qint16 rNarrVFX,
//                 qint16 rBroadVFY,
//                 qint16 rBroadVFX,
//                 qint16 rObsVFY,
//                 qint16 rObsVFX)
//    {
//        mNarrVFx2Y = rNarrVFx2Y;
//        mNarrVFx2X = rNarrVFx2X;
//        mNarrVFY = rNarrVFY;
//        mNarrVFX = rNarrVFX;
//        mBroadVFY = rBroadVFY;
//        mBroadVFX = rBroadVFX;
//        mObsVFY = rObsVFY;
//        mObsVFX = rObsVFX;
//    }

//    void toBytes(QByteArray* sequence)
//    {
//        QDataStream outStr(sequence, QIODevice::WriteOnly);
//        outStr.setByteOrder(QDataStream::LittleEndian);

//        outStr << mNarrVFx2Y;
//        outStr << mNarrVFx2X;
//        outStr << mNarrVFY;
//        outStr << mNarrVFX;
//        outStr << mBroadVFY;
//        outStr << mBroadVFX;
//        outStr << mObsVFY;
//        outStr << mObsVFX;
//    }

//    void fromBytes(QByteArray* sequence)
//    {
//        QDataStream inStr(sequence, QIODevice::ReadOnly);
//        inStr.setByteOrder(QDataStream::LittleEndian);

//        inStr >> mNarrVFx2Y;
//        inStr >> mNarrVFx2X;
//        inStr >> mNarrVFY;
//        inStr >> mNarrVFX;
//        inStr >> mBroadVFY;
//        inStr >> mBroadVFX;
//        inStr >> mObsVFY;
//        inStr >> mObsVFX;
//    }

//    QString parse()
//    {
//        QString parsedMessage;
//        parsedMessage += "Координаты визирной оси (113)";
//        parsedMessage += "\nВертикальная координата для УПЗx2: " + QString::number(mNarrVFx2Y);
//        parsedMessage += "\nГоризонтальная координата для УПЗx2: " + QString::number(mNarrVFx2X);
//        parsedMessage += "\nВертикальная координата для УПЗ: " + QString::number(mNarrVFY);
//        parsedMessage += "\nГоризонтальная координата для УПЗ: " + QString::number(mNarrVFX);
//        parsedMessage += "\nВертикальная координата для ШПЗ: " + QString::number(mBroadVFY);
//        parsedMessage += "\nГоризонтальная координата для ШПЗ: " + QString::number(mBroadVFX);
//        parsedMessage += "\nВертикальная координата для ОПЗ: " + QString::number(mObsVFY);
//        parsedMessage += "\nГоризонтальная координата для ОПЗ: " + QString::number(mObsVFX);

//        return parsedMessage;
//    }

//    //private:
//    qint16 mNarrVFx2Y;//zoomed
//    qint16 mNarrVFx2X;
//    qint16 mNarrVFY;
//    qint16 mNarrVFX;
//    qint16 mBroadVFY;
//    qint16 mBroadVFX;
//    qint16 mObsVFY;
//    qint16 mObsVFX;
//};

#pragma pack(pop)
#endif // MESSAGE_H
