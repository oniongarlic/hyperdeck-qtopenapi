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

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("oatest", "Main");

    return QCoreApplication::exec();
}
