#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
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

struct HyperDeckAPI {
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

    void setServer(QtOpenApiCommon::QOAIBaseApi *api) {
        auto ops=api->operations();

        foreach (auto op, ops) {
            api->setServerVariable(op, 0, "hostname", "192.168.0.233");
            api->setServerVariable(op, 0, "protocol", "http");
        }
    }
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    struct HyperDeckAPI api;
    api.setServer(&api.system);
    api.setServer(&api.transport);
    api.setServer(&api.timeline);
    api.setServer(&api.media);
    api.setServer(&api.audio);
    api.setServer(&api.clips);
    api.setServer(&api.event);
    api.setServer(&api.externalmedia);
    api.setServer(&api.input);
    api.setServer(&api.monitoring);
    api.setServer(&api.nas);
    api.setServer(&api.playrange);
    api.setServer(&api.recordcache);
    api.setServer(&api.spill);

    engine.rootContext()->setContextProperty("system", &api.system);
    engine.rootContext()->setContextProperty("transport", &api.transport);
    engine.rootContext()->setContextProperty("event", &api.event);
    engine.rootContext()->setContextProperty("nas", &api.nas);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("oatest", "Main");

    return QCoreApplication::exec();
}
