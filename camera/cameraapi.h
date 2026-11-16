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

    Q_PROPERTY(long timecode READ getTimecode NOTIFY timecodeChanged FINAL)
    Q_PROPERTY(uint iso READ getISO NOTIFY isoChanged FINAL)
    Q_PROPERTY(int gain READ getGain NOTIFY gainChanged FINAL)

    Q_PROPERTY(uint whiteBalance READ getWhiteBalance NOTIFY whiteBalanceChanged FINAL)
    Q_PROPERTY(int tint READ getTint NOTIFY tintChanged FINAL)

    Q_PROPERTY(int shutter READ getShutter NOTIFY shutterChanged FINAL)

    // Normalized values, use getter for other
    Q_PROPERTY(double zoom READ getZoom NOTIFY zoomChanged FINAL)
    Q_PROPERTY(double iris READ getIris NOTIFY irisChanged FINAL)
    Q_PROPERTY(double focus READ getFocus NOTIFY focusChanged FINAL)

public:
    explicit CameraApi(QObject *parent = nullptr);

    Q_INVOKABLE long getTimecode() const { return m_timecode; }
    Q_INVOKABLE uint getISO() const { return m_iso; }
    Q_INVOKABLE int getGain() const { return m_gain; }

    Q_INVOKABLE uint getWhiteBalance() const { return m_whitebalance; }
    Q_INVOKABLE int getTint() const { return m_tint; }

    Q_INVOKABLE int getShutter() const { return m_shutter; }

    Q_INVOKABLE double getZoom() const { return m_zoom; }
    Q_INVOKABLE uint getFocal() const { return m_focal; }
    Q_INVOKABLE double getIris() const { return m_iris; }
    Q_INVOKABLE uint getAperture() const { return m_aperture; }
    Q_INVOKABLE double getFocus() const { return m_focus; }

protected slots:
    void setTimecode(long tc);

signals:
    void timecodeChanged();
    void isoChanged();
    void gainChanged();
    void whiteBalanceChanged();
    void tintChanged();
    void shutterChanged();
    void formatChanged();
    void timelineChanged();
    void focusChanged();
    void zoomChanged();
    void irisChanged();
    void propertyChange(QString property, QJsonValue value);

protected:
    long m_timecode;
    bool onPropertyChange(QString property, QJsonValue value);
    void onSubscribeHandler(QJsonObject jso);

private:
    uint m_iso=0;
    int m_gain=0;
    uint m_shutter=0;
    int m_tint=0;
    uint m_whitebalance=0;
    double m_focus=0;
    double m_iris=0;
    double m_aperture=0;
    double m_zoom=0;
    uint m_focal=0;
};
