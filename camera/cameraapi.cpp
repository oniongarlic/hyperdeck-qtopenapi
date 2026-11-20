#include "cameraapi.h"

#include "../bminterface.h"

CameraApi::CameraApi(QObject *parent)
    : BMBase{parent}
{

}

bool CameraApi::onPropertyChange(QString property, QJsonValue value)
{
    auto r=BMBase::onPropertyChange(property, value);
    if (r)
        return true;

    if (property=="/video/iso" && value.isObject()) {
        m_iso=value.toObject().value("iso").toInt(0);
        emit isoChanged();
        return true;
    }

    if (property=="/video/gain" && value.isObject()) {
        m_gain=value.toObject().value("gain").toInt(0);
        emit gainChanged();
        return true;
    }

    if (property=="/video/whiteBalance" && value.isObject()) {
        m_whitebalance=value.toObject().value("shutterSpeed").toInt(0);
        emit whiteBalanceChanged();
        return true;
    }

    if (property=="/video/whiteBalanceTint" && value.isObject()) {
        m_tint=value.toObject().value("whiteBalanceTint").toInt();
        emit tintChanged();
        return true;
    }

    if (property=="/video/shutter" && value.isObject()) {
        m_shutter=value.toObject().value("shutterSpeed").toInt();
        emit shutterChanged();
        return true;
    }

    qDebug("*** CameraAPI onPropertyChange not handled");

    return false;
}

void CameraApi::onSubscribeHandler(QJsonObject jso)
{
    qDebug() << "CameraAPI: onSubscribeHandler" << jso;
}
