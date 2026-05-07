#ifndef CAMERAAPI_H
#define CAMERAAPI_H

#include <QObject>
#include <QQmlEngine>

#include <QtWebSockets/QtWebSockets>

#include <QDebug>

#include "../bmbase.h"

#include "client/defaultcameraeventapi.h"
#include "client/defaultcameratransportapi.h"
#include "client/defaultcameravideoapi.h"

#include "camerasystemapi.h"
#include "cameralensapi.h"

class CameraApi : public BMBase
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(CameraSystemApi* system READ getSystem FINAL CONSTANT)
    Q_PROPERTY(BMCamera::DefaultCameraEventApi* event READ getEvent FINAL CONSTANT)
    Q_PROPERTY(BMCamera::DefaultCameraTransportApi* transport READ getTransport FINAL CONSTANT)
    Q_PROPERTY(BMCamera::DefaultCameraVideoApi* video READ getVideo FINAL CONSTANT)

    Q_PROPERTY(long timecode READ getTimecode NOTIFY timecodeChanged FINAL)

public:
    explicit CameraApi(QObject *parent = nullptr);

    Q_INVOKABLE CameraSystemApi* getSystem() { return &system; }
    Q_INVOKABLE BMCamera::DefaultCameraEventApi* getEvent() { return &event; }
    Q_INVOKABLE BMCamera::DefaultCameraTransportApi* getTransport() { return &transport; }
    Q_INVOKABLE BMCamera::DefaultCameraVideoApi* getVideo() { return &video; }

    Q_INVOKABLE long getTimecode() { return m_timecode; }

protected slots:
    void setTimecode(long tc);

protected:
    CameraSystemApi system;
    BMCamera::DefaultCameraEventApi event;

    BMCamera::DefaultCameraTransportApi transport;
    BMCamera::DefaultCameraVideoApi video;

    long m_timecode;

signals:
    void timecodeChanged();
    // BMBase interface
protected:
    bool onPropertyChange(QString property, QJsonValue value);
};

#endif // CAMERAAPI_H
