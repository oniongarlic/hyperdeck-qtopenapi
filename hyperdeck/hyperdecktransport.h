#pragma once

#include <QObject>
#include <QQmlEngine>

#include "transporthyperdeckapi.h"

#include "../bminterface.h"

class HyperdeckTransport : public BMHyperdeck::TransportHyperdeckApi, public BMInterface
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit HyperdeckTransport(QObject *parent = nullptr);

    bool onPropertyChange(QString property, QJsonValue value);

    Q_INVOKABLE QTime getTimelineTime() const { return m_timeline; }
    Q_INVOKABLE QTime getDisplayTime() const { return m_display; }

signals:
    void timecodeChanged();

protected:
    QTime m_display;
    QTime m_timeline;

};

