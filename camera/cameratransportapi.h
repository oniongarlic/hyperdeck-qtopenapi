#pragma once

#include <QObject>
#include <QQmlEngine>

#include "client/defaultcameratransportapi.h"

#include "../bminterface.h"

class CameraTransportApi : public BMCamera::DefaultCameraTransportApi, public BMInterface

{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(long timecode READ getTimecode NOTIFY timecodeChanged FINAL)
public:
    explicit CameraTransportApi(QObject *parent = nullptr);

    Q_INVOKABLE long getTimecode() const { return m_timecode; }

    bool onPropertyChange(QString property, QJsonValue value);

protected slots:
    void setTimecode(long tc);

signals:
    void timecodeChanged();

private:
    long m_timecode;
};

