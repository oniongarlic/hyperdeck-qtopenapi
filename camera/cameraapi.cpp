#include "cameraapi.h"

#include "../bminterface.h"

CameraApi::CameraApi(QObject *parent)
    : BMBase{parent}
{

}

void CameraApi::setTimecode(long tc)
{
    m_timecode=tc;

    emit timecodeChanged();
}

bool CameraApi::onPropertyChange(QString property, QJsonValue value)
{
    auto r=BMBase::onPropertyChange(property, value);
    if (r)
        return true;

    // "/transports/0/timecode" QJsonValue(object, QJsonObject({"clip":0,"timecode":285757700}))
    if (property=="/transports/0/timecode" && value.isObject()) {
        setTimecode(value.toObject().value("timecode").toInteger());
        return true;
    }

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

    if (property=="/lens/focus" && value.isObject()) {
        m_focus=value.toObject().value("normalised").toDouble();
        emit focusChanged();
        return true;
    }

    if (property=="/lens/zoom" && value.isObject()) {
        m_zoom=value.toObject().value("normalised").toDouble();
        m_focal=value.toObject().value("focalLength").toInt();
        emit zoomChanged();
        return true;
    }

    if (property=="/lens/iris" && value.isObject()) {
        m_iris=value.toObject().value("normalised").toDouble();
        m_aperture=value.toObject().value("apertureStop").toDouble();
        emit irisChanged();
        return true;
    }

    qDebug("*** CameraAPI onPropertyChange not handled");

    return false;
}

void CameraApi::onSubscribeHandler(QJsonObject jso)
{
    qDebug() << "CameraAPI: onSubscribeHandler" << jso;
}
