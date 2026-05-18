#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

//#include "hyperdeckapi.h"
//#include "cameraapi.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setOrganizationName("TalOrg");
    app.setOrganizationDomain("tal.org");
    app.setApplicationName("CuteBMOAPI");

    QQmlApplicationEngine engine;

    //qmlRegisterType<HyperdeckApi>("org.tal.hyperdeck", 1, 0, "HyperDeckDevice");
    //qmlRegisterUncreatableType<QtOpenAPI::SystemApi>("org.tal.hyperdeck", 1, 0, "HyperDeckSystem", "Nope");
    //qmlRegisterUncreatableType<QtOpenAPI::TransportApi>("org.tal.hyperdeck", 1, 0, "HyperDeckTransport", "Nope");

    //qmlRegisterType<CameraAPI>("org.tal.bmcamera", 1, 0, "CameraDevice");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("oatest", "Main");

    return QCoreApplication::exec();
}
