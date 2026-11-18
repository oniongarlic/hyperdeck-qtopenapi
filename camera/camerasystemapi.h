#pragma once

#include <QObject>
#include <QQmlEngine>

#include "client/defaultcamerasystemapi.h"

class CameraSystemApi : public BMCamera::DefaultCameraSystemApi
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit CameraSystemApi(QObject *parent = nullptr);    

signals:
};

