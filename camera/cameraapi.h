#ifndef CAMERAAPI_H
#define CAMERAAPI_H

#include <QObject>
#include <QQmlEngine>

#include <QtWebSockets/QtWebSockets>

#include <QDebug>

#include "../bmbase.h"

#include "client/defaultcamerasystemapi.h"
#include "client/defaultcameraeventapi.h"
#include "client/defaultcameratransportapi.h"
#include "client/defaultcameravideoapi.h"

class CameraApi : public BMBase
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit CameraApi(QObject *parent = nullptr);

    Q_INVOKABLE BMCamera::DefaultCameraSystemApi* getSystem() { return &system; }
    Q_INVOKABLE BMCamera::DefaultCameraEventApi* getEvent() { return &event; }

protected:
    BMCamera::DefaultCameraSystemApi system;
    BMCamera::DefaultCameraEventApi event;

    BMCamera::DefaultCameraTransportApi transport;
    BMCamera::DefaultCameraVideoApi video;

signals:
};

#endif // CAMERAAPI_H
