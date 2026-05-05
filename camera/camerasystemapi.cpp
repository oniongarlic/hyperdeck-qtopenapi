#include "camerasystemapi.h"

CameraSystemApi::CameraSystemApi(QObject *parent)
    : BMCamera::DefaultCameraSystemApi{parent}
{
    auto ops=operations();

    qDebug() << "CSA" << ops;
}
