#pragma once

#include <QObject>
#include <QQmlEngine>

#include "timelinehyperdeckapi.h"

#include "../bminterface.h"

#include "clipmodel.h"

class HyperdeckTimeline : public BMHyperdeck::TimelineHyperdeckApi, public BMInterface
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit HyperdeckTimeline(QObject *parent = nullptr);

    Q_INVOKABLE ClipModel* getClipsModel() { return &m_clip_model; }
    Q_INVOKABLE QVariantMap getFormat() const { return m_format; }

    bool onPropertyChange(QString property, QJsonValue value);

signals:
    void timelineUpdated();
    void formatChanged();

protected:
    ClipModel m_clip_model;
    QVariantMap m_format;
};

