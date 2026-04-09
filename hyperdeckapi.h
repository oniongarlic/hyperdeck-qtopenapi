#ifndef HYPERDECKAPI_H
#define HYPERDECKAPI_H

#include <QObject>
#include <QQmlEngine>

#include <QDebug>

#include "audioapi.h"
#include "clipsapi.h"
#include "eventapi.h"
#include "externalmediaapi.h"
#include "inputapi.h"
#include "mediaapi.h"
#include "monitoringapi.h"
#include "systemapi.h"
#include "mediaapi.h"
#include "nasapi.h"
#include "playrangeapi.h"
#include "recordcacheapi.h"
#include "spillapi.h"
#include "timelineapi.h"
#include "transportapi.h"

class HyperdeckApi : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit HyperdeckApi(QObject *parent = nullptr);

    QtOpenAPI::SystemApi system;
    QtOpenAPI::TransportApi transport;
    QtOpenAPI::TimelineApi timeline;
    QtOpenAPI::MediaApi media;
    QtOpenAPI::AudioApi audio;
    QtOpenAPI::ClipsApi clips;
    QtOpenAPI::EventApi event;
    QtOpenAPI::ExternalMediaApi externalmedia;
    QtOpenAPI::InputApi input;
    QtOpenAPI::MonitoringApi monitoring;
    QtOpenAPI::NASApi nas;
    QtOpenAPI::PlayRangeApi playrange;
    QtOpenAPI::RecordCacheApi recordcache;
    QtOpenAPI::SpillApi spill;

    Q_INVOKABLE void setServer(QString hostname, QString protocol);

    Q_INVOKABLE QtOpenAPI::TransportApi* getTransport() { return &transport; }

private:
    void setApiServer(QtOpenApiCommon::QOAIBaseApi *api);

signals:

private:
    QString m_hostname;
    QString m_protocol;
};

#endif // HYPERDECKAPI_H
