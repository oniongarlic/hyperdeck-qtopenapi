#include "hyperdeckapi.h"

#include <QJsonDocument>
#include <QJsonObject>

HyperdeckApi::HyperdeckApi(QObject *parent)
    : QObject{parent}
{}

HyperdeckApi::~HyperdeckApi()
{
    m_ws.close();
}

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

void HyperdeckApi::open()
{
    QUrl url;

    url.setHost(m_hostname);
    url.setScheme("ws");
    url.setPath("/control/api/v1/event/websocket");

    connect(&m_ws, &QWebSocket::connected, this, &HyperdeckApi::onWsConnected);
    connect(&m_ws, &QWebSocket::errorOccurred, this, &HyperdeckApi::onWsErrorOccurred);
    connect(&m_ws, &QWebSocket::disconnected, this, &HyperdeckApi::onWsDisconnected);

    m_ws.open(url);
}

void HyperdeckApi::close()
{
    m_ws.close();
    m_ws.disconnect();
}

QString makeJson(QString type, QString action)
{
    QJsonObject o;
    QJsonObject d;

    o.insert("type", type);
    d.insert("action", action);
    o.insert("data", d);

    return QJsonDocument(o).toJson();
}

QString makeJsonArray(QString type, QString action, QString prop, QJsonArray array)
{
    QJsonObject o;
    QJsonObject d;

    o.insert("type", type);
    d.insert("action", action);
    d.insert(prop, array);
    o.insert("data", d);

    return QJsonDocument(o).toJson();
}

void HyperdeckApi::onWsConnected()
{
    qDebug("Websocket connected!");

    connect(&m_ws, &QWebSocket::textMessageReceived, this, &HyperdeckApi::onWsTextMessageReceived);

    m_ws.sendTextMessage(makeJson("request", "listProperties"));
}

void HyperdeckApi::onWsDisconnected()
{
    qDebug("Websocket disconnected");
}

void HyperdeckApi::onWsTextMessageReceived(QString message)
{
    qDebug() << "WS" << message;
    auto j=QJsonDocument::fromJson(message.toUtf8());
    qDebug() << j;

    if (!j.isObject()) {
        qWarning("Not an object ?");
        return;
    }

    auto d=j.object().value("data").toObject();
    auto a=d.value("action");
    if (a.toString()=="listProperties") {
        auto props=d.value("properties").toArray();

        m_ws.sendTextMessage(makeJsonArray("request", "subscribe", "properties", props));
    }

    if (a.toString()=="subscribe") {

    }

    if (a.toString()=="propertyValueChanged") {
        auto prop=d.value("property").toString();
        auto value=d.value("value");

        qDebug() << "Property" << prop << value;
    }
}

void HyperdeckApi::onWsErrorOccurred(QAbstractSocket::SocketError error)
{
    qDebug() << "WSE" << error;
}
