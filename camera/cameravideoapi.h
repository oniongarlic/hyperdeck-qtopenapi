#ifndef DEFAULTCAMERAVIDEOAPI_H
#define DEFAULTCAMERAVIDEOAPI_H

#include <QObject>
#include <QQmlEngine>

#include "client/defaultcameravideoapi.h"

class CameraVideoApi : public BMCamera::DefaultCameraVideoApi

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit CameraVideoApi(QObject *parent = nullptr);
};

#endif
