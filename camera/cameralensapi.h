#pragma once

#include <QObject>
#include <QQmlEngine>

#include "defaultcameralensapi.h"

class CameraLensApi : public BMCamera::DefaultCameraLensApi
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit CameraLensApi(QObject *parent = nullptr);
};

