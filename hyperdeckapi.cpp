#include "hyperdeckapi.h"

HyperdeckApi::HyperdeckApi(QObject *parent)
    : QObject{parent}
{}

void HyperdeckApi::setServer(QString hostname, QString protocol)
{
    m_hostname=hostname;
    m_protocol=protocol;

    setApiServer(&system);
    setApiServer(&transport);
    setApiServer(&timeline);
    setApiServer(&media);
    setApiServer(&audio);
    setApiServer(&clips);
    setApiServer(&event);
    setApiServer(&externalmedia);
    setApiServer(&input);
    setApiServer(&monitoring);
    setApiServer(&nas);
    setApiServer(&playrange);
    setApiServer(&recordcache);
    setApiServer(&spill);
}

void HyperdeckApi::setApiServer(QtOpenApiCommon::QOAIBaseApi *api) {
    auto ops=api->operations();

    foreach (auto op, ops) {
        api->setServerVariable(op, 0, "hostname", m_hostname);
        api->setServerVariable(op, 0, "protocol", m_protocol);
    }
}
