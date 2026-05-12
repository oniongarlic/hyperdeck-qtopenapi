#ifndef CAMERAAPI_H
#define CAMERAAPI_H

#include <QObject>
#include <QQmlEngine>
#include <QtWebSockets/QtWebSockets>
#include <QDebug>

#include "../bmbase.h"

class CameraApi : public BMBase
{
    Q_OBJECT
    QML_ELEMENT    

    Q_PROPERTY(long timecode READ getTimecode NOTIFY timecodeChanged FINAL)

public:
    explicit CameraApi(QObject *parent = nullptr);

    Q_INVOKABLE long getTimecode() { return m_timecode; }

protected slots:
    void setTimecode(long tc);

signals:
    void timecodeChanged();
    void propertyChange(QString property, QJsonValue value);

protected:
    long m_timecode;
    bool onPropertyChange(QString property, QJsonValue value);
};

#endif // CAMERAAPI_H
