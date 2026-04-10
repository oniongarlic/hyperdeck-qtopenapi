#ifndef HYPERDECKAPI_H
#define HYPERDECKAPI_H

#include <QObject>
#include <QQmlEngine>

#include <QtWebSockets/QtWebSockets>

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

    Q_PROPERTY(QtOpenAPI::SystemApi* system READ getSystem FINAL)
    Q_PROPERTY(QtOpenAPI::TransportApi* transport READ getTransport FINAL)
    Q_PROPERTY(QtOpenAPI::TimelineApi* timeline READ getTimeline FINAL)
    Q_PROPERTY(QtOpenAPI::MediaApi* media READ getMedia FINAL)
    Q_PROPERTY(QtOpenAPI::AudioApi* audio READ getAudio FINAL)
    Q_PROPERTY(QtOpenAPI::ClipsApi* clips READ getClips FINAL)
    Q_PROPERTY(QtOpenAPI::EventApi* event READ getEvent FINAL)
    Q_PROPERTY(QtOpenAPI::ExternalMediaApi* externalmedia READ getExternalMedia FINAL)
    Q_PROPERTY(QtOpenAPI::InputApi* input READ getInput FINAL)
    Q_PROPERTY(QtOpenAPI::MonitoringApi* monitoring READ getMonitoring FINAL)
    Q_PROPERTY(QtOpenAPI::NASApi* nas READ getNas FINAL)
    Q_PROPERTY(QtOpenAPI::PlayRangeApi* playrange READ getPlayRange FINAL)
    Q_PROPERTY(QtOpenAPI::RecordCacheApi* recordcache READ getRecordCache FINAL)
    Q_PROPERTY(QtOpenAPI::SpillApi* spill READ getSpill FINAL)


public:
    explicit HyperdeckApi(QObject *parent = nullptr);
    ~HyperdeckApi();

    Q_INVOKABLE void setServer(QString hostname, QString protocol);    
    Q_INVOKABLE void setApiServer(QtOpenApiCommon::QOAIBaseApi *api);
    Q_INVOKABLE void open();
    Q_INVOKABLE void close();

    Q_INVOKABLE QtOpenAPI::TransportApi* getTransport() { return &transport; }
    Q_INVOKABLE QtOpenAPI::SystemApi* getSystem() { return &system; }
    Q_INVOKABLE QtOpenAPI::TimelineApi* getTimeline() { return &timeline; }
    Q_INVOKABLE QtOpenAPI::MediaApi* getMedia() { return &media; }
    Q_INVOKABLE QtOpenAPI::AudioApi* getAudio() { return &audio; }
    Q_INVOKABLE QtOpenAPI::ClipsApi* getClips() { return &clips; }
    Q_INVOKABLE QtOpenAPI::EventApi* getEvent() { return &event; }
    Q_INVOKABLE QtOpenAPI::ExternalMediaApi* getExternalMedia() { return &externalmedia; }
    Q_INVOKABLE QtOpenAPI::InputApi* getInput() { return &input; }
    Q_INVOKABLE QtOpenAPI::MonitoringApi* getMonitoring() { return &monitoring; }
    Q_INVOKABLE QtOpenAPI::NASApi* getNas() { return &nas; }
    Q_INVOKABLE QtOpenAPI::PlayRangeApi* getPlayRange() { return &playrange; }
    Q_INVOKABLE QtOpenAPI::RecordCacheApi* getRecordCache() { return &recordcache; }
    Q_INVOKABLE QtOpenAPI::SpillApi* getSpill() { return &spill; }

signals:

protected:
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

protected slots:
    void onWsConnected();
    void onWsDisconnected();
    void onWsTextMessageReceived(QString message);
    void onWsErrorOccurred(QAbstractSocket::SocketError error);

private:
    QString m_hostname;
    QString m_protocol;
    QWebSocket m_ws;
};

#endif // HYPERDECKAPI_H
