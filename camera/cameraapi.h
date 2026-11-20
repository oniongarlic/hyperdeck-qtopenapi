#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QtWebSockets/QtWebSockets>
#include <QDebug>

#include "../bmbase.h"

class CameraApi : public BMBase
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(uint iso READ getISO NOTIFY isoChanged FINAL)
    Q_PROPERTY(int gain READ getGain NOTIFY gainChanged FINAL)

    Q_PROPERTY(uint whiteBalance READ getWhiteBalance NOTIFY whiteBalanceChanged FINAL)
    Q_PROPERTY(int tint READ getTint NOTIFY tintChanged FINAL)

    Q_PROPERTY(int shutter READ getShutter NOTIFY shutterChanged FINAL)

public:
    explicit CameraApi(QObject *parent = nullptr);

    Q_INVOKABLE uint getISO() const { return m_iso; }
    Q_INVOKABLE int getGain() const { return m_gain; }

    Q_INVOKABLE uint getWhiteBalance() const { return m_whitebalance; }
    Q_INVOKABLE int getTint() const { return m_tint; }

    Q_INVOKABLE int getShutter() const { return m_shutter; }

signals: 
    void isoChanged();
    void gainChanged();
    void whiteBalanceChanged();
    void tintChanged();
    void shutterChanged();
    void formatChanged();
    void timelineChanged();    
    void propertyChange(QString property, QJsonValue value);

protected:    
    bool onPropertyChange(QString property, QJsonValue value);
    void onSubscribeHandler(QJsonObject jso);

private:
    uint m_iso=0;
    int m_gain=0;
    uint m_shutter=0;
    int m_tint=0;
    uint m_whitebalance=0;    
};
