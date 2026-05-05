#ifndef CAMERASYSTEMAPI_H
#define CAMERASYSTEMAPI_H

#include <QObject>
#include <QQmlEngine>

#include "client/defaultcamerasystemapi.h"

class CameraSystemApi : public BMCamera::DefaultCameraSystemApi
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit CameraSystemApi(QObject *parent = nullptr);

    void setServer(QString hostname, QString protocol)
    {
        setServerVariable("", 0, "hostname", hostname);
        setServerVariable("", 0, "hostname", hostname);
    }

signals:
};

#endif // CAMERASYSTEMAPI_H
