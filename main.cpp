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

#include "hyperdeckapi.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setOrganizationName("TalOrg");
    app.setOrganizationDomain("tal.org");
    app.setApplicationName("HyperDeckAPITest");

    QQmlApplicationEngine engine;

    qmlRegisterType<HyperdeckApi>("org.tal.hyperdeck", 1, 0, "HyperDeckDevice");
//    qmlRegisterType<QtOpenAPI::SystemApi>("org.tal.hyperdeck", 1, 0, "HyperDeckSystem");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("oatest", "Main");

    return QCoreApplication::exec();
}
