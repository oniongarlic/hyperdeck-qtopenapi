#ifndef CAMERAAPI_H
#define CAMERAAPI_H

#include <QObject>
#include <QQmlEngine>

#include <QtWebSockets/QtWebSockets>

#include <QDebug>

#include "../../../cameraapi/camera_system_api/client/defaultcamerasystemapi.h"

class CameraAPI : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit CameraAPI(QObject *parent = nullptr);

    Q_INVOKABLE BMCamera::DefaultCameraSystemApi* getSystem() { return &system; }

protected:
    BMCamera::DefaultCameraSystemApi system;

signals:
};

#endif // CAMERAAPI_H
