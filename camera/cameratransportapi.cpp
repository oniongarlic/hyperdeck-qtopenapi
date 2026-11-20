#include "cameratransportapi.h"

CameraTransportApi::CameraTransportApi(QObject *parent)
    : BMCamera::DefaultCameraTransportApi{parent}
{

}

void CameraTransportApi::setTimecode(long tc)
{
    m_timecode=tc;

    emit timecodeChanged();
}

bool CameraTransportApi::onPropertyChange(QString property, QJsonValue value)
{
    auto o=value.toObject();

    if (property=="/transports/0/timecode" && value.isObject()) {
        setTimecode(value.toObject().value("timecode").toInteger());
        return true;
    }

    return false;
}

