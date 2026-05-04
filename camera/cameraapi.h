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

    Q_PROPERTY(BMCamera::DefaultCameraSystemApi* system READ getSystem FINAL CONSTANT)
    Q_PROPERTY(BMCamera::DefaultCameraEventApi* event READ getEvent FINAL CONSTANT)
    Q_PROPERTY(BMCamera::DefaultCameraTransportApi* transport READ getTransport FINAL CONSTANT)
    Q_PROPERTY(BMCamera::DefaultCameraVideoApi* video READ getVideo FINAL CONSTANT)

public:
    explicit CameraApi(QObject *parent = nullptr);

    Q_INVOKABLE BMCamera::DefaultCameraSystemApi* getSystem() { return &system; }
    Q_INVOKABLE BMCamera::DefaultCameraEventApi* getEvent() { return &event; }
    Q_INVOKABLE BMCamera::DefaultCameraTransportApi* getTransport() { return &transport; }
    Q_INVOKABLE BMCamera::DefaultCameraVideoApi* getVideo() { return &video; }

protected:
    BMCamera::DefaultCameraSystemApi system;
    BMCamera::DefaultCameraEventApi event;

    BMCamera::DefaultCameraTransportApi transport;
    BMCamera::DefaultCameraVideoApi video;

signals:
};

#endif // CAMERAAPI_H
