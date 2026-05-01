#include "bmbase.h"

static QString makeJson(QString type, QString action)
{
    QJsonObject o;
    QJsonObject d;

    o.insert("type", type);
    d.insert("action", action);
    o.insert("data", d);

    return QJsonDocument(o).toJson();
}

static QString makeJsonArray(QString type, QString action, QString prop, QJsonArray array)
{
    QJsonObject o;
    QJsonObject d;

    o.insert("type", type);
    d.insert("action", action);
    d.insert(prop, array);
    o.insert("data", d);

    return QJsonDocument(o).toJson();
}

BMBase::BMBase(QObject *parent)
    : QObject{parent}
{

}

BMBase::~BMBase()
{
    m_ws.close();
}

void BMBase::setServer(QString hostname, QString protocol)
{
    m_hostname=hostname;
    m_protocol=protocol;

    foreach (auto oa, m_oac) {
        setApiServer(oa);
    }
}

void BMBase::setApiServer(QtOpenApiCommon::QOAIBaseApi *api) {
    auto ops=api->operations();

    foreach (auto op, ops) {
        api->setServerVariable(op, 0, "hostname", m_hostname);
        api->setServerVariable(op, 0, "protocol", m_protocol);
    }
}

void BMBase::open()
{
    QUrl url;

    url.setHost(m_hostname);
    url.setScheme("ws");
    url.setPath("/control/api/v1/event/websocket");

    connect(&m_ws, &QWebSocket::connected, this, &BMBase::onWsConnected);
    connect(&m_ws, &QWebSocket::errorOccurred, this, &BMBase::onWsErrorOccurred);
    connect(&m_ws, &QWebSocket::disconnected, this, &BMBase::onWsDisconnected);

    m_ws.open(url);
}

void BMBase::close()
{
    m_ws.close();
    m_ws.disconnect();
}

void BMBase::onWsConnected()
{
    qDebug("Websocket connected!");
    connect(&m_ws, &QWebSocket::textMessageReceived, this, &BMBase::onWsTextMessageReceived);
    m_ws.sendTextMessage(makeJson("request", "listProperties"));
}

void BMBase::onWsDisconnected()
{
    qDebug("Websocket disconnected");
}


void BMBase::onWsTextMessageReceived(QString message)
{
    qDebug() << "WS" << message;
    auto j=QJsonDocument::fromJson(message.toUtf8());
    qDebug() << j;

    if (!j.isObject()) {
        qWarning("Not an object ?");
        emit connectionError();
        return;
    }

    auto d=j.object().value("data").toObject();
    auto a=d.value("action");
    if (a.toString()=="listProperties") {
        auto props=d.value("properties").toArray();

        m_ws.sendTextMessage(makeJsonArray("request", "subscribe", "properties", props));
    }

    if (a.toString()=="subscribe") {
        auto v=d.value("values").toObject();

        onSubscribeHandler(v);
    }

    if (a.toString()=="propertyValueChanged") {
        auto prop=d.value("property").toString();
        auto value=d.value("value");

        qDebug() << "Property" << prop << value;
    }
}

void BMBase::onWsErrorOccurred(QAbstractSocket::SocketError error)
{
    qDebug() << "WSE" << error;

    emit connectionError();
}

void BMBase::onSubscribeHandler(QJsonObject jso)
{

}
