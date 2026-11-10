#pragma once

#include <QObject>
#include <QQmlEngine>

#include "client/defaultcameratransportapi.h"

class CameraTransportApi : public BMCamera::DefaultCameraTransportApi

{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit CameraTransportApi(QObject *parent = nullptr);

protected slots:
    void onPropertyChange(QString property, QJsonValue value);
};

