#include "cameravideoapi.h"

CameraVideoApi::CameraVideoApi(QObject *parent)
    : BMCamera::DefaultCameraVideoApi{parent}
{

}

void CameraVideoApi::setIso(uint iso)
{
    BMCamera::_video_iso_put_request req;
    req.setIso(iso);
    videoIsoPut(req);
}

bool CameraVideoApi::onPropertyChange(QString property, QJsonValue value)
{
    auto o=value.toObject();

    if (property=="/video/iso") {
        m_iso=o.value("iso").toInt(0);
        emit isoChanged();
        return true;
    }

    if (property=="/video/gain") {
        m_gain=o.value("gain").toInt(0);
        emit gainChanged();
        return true;
    }

    if (property=="/video/whiteBalance") {
        m_whitebalance=o.value("shutterSpeed").toInt(0);
        emit whiteBalanceChanged();
        return true;
    }

    if (property=="/video/whiteBalanceTint") {
        m_tint=o.value("whiteBalanceTint").toInt();
        emit tintChanged();
        return true;
    }

    if (property=="/video/shutter") {
        m_shutter=o.value("shutterSpeed").toInt();
        emit shutterChanged();
        return true;
    }

    return false;
}

