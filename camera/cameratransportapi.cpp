#include "cameratransportapi.h"

CameraTransportApi::CameraTransportApi(QObject *parent)
    : BMCamera::DefaultCameraTransportApi{parent}
{
    qDebug() << "TA" << parent;
}

void CameraTransportApi::onPropertyChange(QString property, QJsonValue value)
{

}

