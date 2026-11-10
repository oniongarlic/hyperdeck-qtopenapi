#pragma once

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

