#ifndef HYPERDECKAPI_H
#define HYPERDECKAPI_H

#include <QObject>
#include <QQmlEngine>

#include <QtWebSockets/QtWebSockets>

#include <QDebug>

#include "audiohyperdeckapi.h"
#include "clipshyperdeckapi.h"
#include "eventhyperdeckapi.h"
#include "externalmediahyperdeckapi.h"
#include "inputhyperdeckapi.h"
#include "mediahyperdeckapi.h"
#include "monitoringhyperdeckapi.h"
#include "systemhyperdeckapi.h"
#include "mediahyperdeckapi.h"
#include "nashyperdeckapi.h"
#include "playrangehyperdeckapi.h"
#include "recordcachehyperdeckapi.h"
#include "spillhyperdeckapi.h"
#include "timelinehyperdeckapi.h"
#include "transporthyperdeckapi.h"

#include "clipmodel.h"

class HyperdeckApi : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(BMHyperdeck::SystemHyperdeckApi* system READ getSystem FINAL CONSTANT)
    Q_PROPERTY(BMHyperdeck::TransportHyperdeckApi* transport READ getTransport FINAL CONSTANT)
    Q_PROPERTY(BMHyperdeck::TimelineHyperdeckApi* timeline READ getTimeline FINAL CONSTANT)
    Q_PROPERTY(BMHyperdeck::MediaHyperdeckApi* media READ getMedia FINAL CONSTANT)
    Q_PROPERTY(BMHyperdeck::AudioHyperdeckApi* audio READ getAudio FINAL CONSTANT)
    Q_PROPERTY(BMHyperdeck::ClipsHyperdeckApi* clips READ getClips FINAL CONSTANT)
    Q_PROPERTY(BMHyperdeck::EventHyperdeckApi* event READ getEvent FINAL CONSTANT)
    Q_PROPERTY(BMHyperdeck::ExternalMediaHyperdeckApi* externalmedia READ getExternalMedia FINAL CONSTANT)
    Q_PROPERTY(BMHyperdeck::InputHyperdeckApi* input READ getInput FINAL CONSTANT)
    Q_PROPERTY(BMHyperdeck::MonitoringHyperdeckApi* monitoring READ getMonitoring FINAL CONSTANT)
    Q_PROPERTY(BMHyperdeck::NASHyperdeckApi* nas READ getNas FINAL CONSTANT)
    Q_PROPERTY(BMHyperdeck::PlayRangeHyperdeckApi* playrange READ getPlayRange FINAL CONSTANT)
    Q_PROPERTY(BMHyperdeck::RecordCacheHyperdeckApi* recordcache READ getRecordCache FINAL CONSTANT)
    Q_PROPERTY(BMHyperdeck::SpillHyperdeckApi* spill READ getSpill FINAL CONSTANT)

public:
    explicit HyperdeckApi(QObject *parent = nullptr);
    ~HyperdeckApi();

    Q_INVOKABLE void setServer(QString hostname, QString protocol);    
    Q_INVOKABLE void setApiServer(QtOpenApiCommon::QOAIBaseApi *api);
    Q_INVOKABLE void open();
    Q_INVOKABLE void close();

    Q_INVOKABLE BMHyperdeck::TransportHyperdeckApi* getTransport() { return &transport; }
    Q_INVOKABLE BMHyperdeck::SystemHyperdeckApi* getSystem() { return &system; }
    Q_INVOKABLE BMHyperdeck::TimelineHyperdeckApi* getTimeline() { return &timeline; }
    Q_INVOKABLE BMHyperdeck::MediaHyperdeckApi* getMedia() { return &media; }
    Q_INVOKABLE BMHyperdeck::AudioHyperdeckApi* getAudio() { return &audio; }
    Q_INVOKABLE BMHyperdeck::ClipsHyperdeckApi* getClips() { return &clips; }
    Q_INVOKABLE BMHyperdeck::EventHyperdeckApi* getEvent() { return &event; }
    Q_INVOKABLE BMHyperdeck::ExternalMediaHyperdeckApi* getExternalMedia() { return &externalmedia; }
    Q_INVOKABLE BMHyperdeck::InputHyperdeckApi* getInput() { return &input; }
    Q_INVOKABLE BMHyperdeck::MonitoringHyperdeckApi* getMonitoring() { return &monitoring; }
    Q_INVOKABLE BMHyperdeck::NASHyperdeckApi* getNas() { return &nas; }
    Q_INVOKABLE BMHyperdeck::PlayRangeHyperdeckApi* getPlayRange() { return &playrange; }
    Q_INVOKABLE BMHyperdeck::RecordCacheHyperdeckApi* getRecordCache() { return &recordcache; }
    Q_INVOKABLE BMHyperdeck::SpillHyperdeckApi* getSpill() { return &spill; }

    Q_INVOKABLE ClipModel* getClipsModel() { return &m_clip_model; }

signals:
    void connectionError();

protected:
    BMHyperdeck::SystemHyperdeckApi system;
    BMHyperdeck::TransportHyperdeckApi transport;
    BMHyperdeck::TimelineHyperdeckApi timeline;
    BMHyperdeck::MediaHyperdeckApi media;
    BMHyperdeck::AudioHyperdeckApi audio;
    BMHyperdeck::ClipsHyperdeckApi clips;
    BMHyperdeck::EventHyperdeckApi event;
    BMHyperdeck::ExternalMediaHyperdeckApi externalmedia;
    BMHyperdeck::InputHyperdeckApi input;
    BMHyperdeck::MonitoringHyperdeckApi monitoring;
    BMHyperdeck::NASHyperdeckApi nas;
    BMHyperdeck::PlayRangeHyperdeckApi playrange;
    BMHyperdeck::RecordCacheHyperdeckApi recordcache;
    BMHyperdeck::SpillHyperdeckApi spill;

protected slots:
    void onWsConnected();
    void onWsDisconnected();
    void onWsTextMessageReceived(QString message);
    void onWsErrorOccurred(QAbstractSocket::SocketError error);

private:
    QString m_hostname;
    QString m_protocol;    
    QWebSocket m_ws;

    QString m_device;
    QString m_product;
    QString m_version;

    ClipModel m_clip_model;
};

#endif // HYPERDECKAPI_H
