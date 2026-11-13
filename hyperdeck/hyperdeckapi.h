#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QtWebSockets/QtWebSockets>
#include <QDebug>

#include "../bmbase.h"

#include "clipmodel.h"

class HyperdeckApi : public BMBase
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit HyperdeckApi(QObject *parent = nullptr);
    ~HyperdeckApi();

    Q_INVOKABLE ClipModel* getClipsModel() { return &m_clip_model; }

    Q_INVOKABLE QTime getTimelineTime() const { return m_timeline; }
    Q_INVOKABLE QTime getDisplayTime() const { return m_display; }

signals:
    void timecodeChanged();

protected:    
    void onSubscribeHandler(QJsonObject jso);
    bool onPropertyChange(QString property, QJsonValue value);

private:
    QString m_device;
    QString m_product;
    QString m_version;

    QTime m_display;
    QTime m_timeline;

    ClipModel m_clip_model;
};


