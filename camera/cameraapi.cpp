#include "cameraapi.h"

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
    // "/transports/0/timecode" QJsonValue(object, QJsonObject({"clip":0,"timecode":285757700}))
    if (property=="/transports/0/timecode" && value.isObject()) {
        setTimecode(value.toObject().value("timecode").toInteger());
        return true;
    }

    emit propertyChange(property, value);

    return false;
}
