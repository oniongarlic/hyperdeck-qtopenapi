#pragma once

#include <QObject>
#include <QQmlEngine>

#include "../bminterface.h"
#include "defaultcameralensapi.h"

class CameraLensApi : public BMCamera::DefaultCameraLensApi, public BMInterface
{
    Q_OBJECT
    QML_ELEMENT

    // Normalized values, use getter for other
    Q_PROPERTY(double zoom READ getZoom NOTIFY zoomChanged FINAL)
    Q_PROPERTY(double iris READ getIris NOTIFY irisChanged FINAL)
    Q_PROPERTY(double focus READ getFocus NOTIFY focusChanged FINAL)

public:
    explicit CameraLensApi(QObject *parent = nullptr);

    Q_INVOKABLE void setZoom(double zoom);
    Q_INVOKABLE void setFocus(double focus);

    Q_INVOKABLE double getZoom() const { return m_zoom; }
    Q_INVOKABLE uint getFocal() const { return m_focal; }
    Q_INVOKABLE double getIris() const { return m_iris; }
    Q_INVOKABLE uint getAperture() const { return m_aperture; }
    Q_INVOKABLE double getFocus() const { return m_focus; }

    bool onPropertyChange(QString property, QJsonValue value);

signals:
    void focusChanged();
    void zoomChanged();
    void irisChanged();

protected:
    double m_focus=0;
    double m_iris=0;
    double m_aperture=0;
    double m_zoom=0;
    uint m_focal=0;
};

