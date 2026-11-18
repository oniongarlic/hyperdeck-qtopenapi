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

QQmlListProperty<QObject> BMBase::endpoints()
{
    return QQmlListProperty<QObject>(this, this, [](QQmlListProperty<QObject>* prop, QObject* obj) {
                                         auto self = static_cast<BMBase*>(prop->data);
                                         obj->setParent(self);

                                         if (auto sub = qobject_cast<QtOpenApiCommon::QOAIBaseApi*>(obj)) {
                                             qDebug() << "OAPI" << self->m_hostname << self->m_protocol << obj << sub->operations();
                                             self->setApiServer(sub);                                             

                                             //QObject::connect(self, &BMBase::serverChanged, sub, &BMBase::setServer);
                                         }
                                     },
                                     nullptr, nullptr, nullptr);
}

void BMBase::handleResponseMessage(QJsonObject rm)
{
    auto a=rm.value("action").toString();

    if (a=="listProperties") {
        auto props=rm.value("properties").toArray();

        // We could do this, but if there is an error (for example camera with no media) the response will be just the error and no values
        // m_ws.sendTextMessage(makeJsonArray("request", "subscribe", "properties", props));
        for (const auto &oa : std::as_const(props)) {
            QJsonArray a;
            a.append(oa);
            m_ws.sendTextMessage(makeJsonArray("request", "subscribe", "properties", a));
        }

        onListProperties(props);

        return;
    }

    if (a=="subscribe") {
        auto props=rm.value("properties").toArray();
        auto values=rm.value("values").toObject();
        for (const auto &oa : std::as_const(props)) {
            auto prop=oa.toString();
            auto value=values.value(prop);

            if (onPropertyChange(prop, value)==false) {
                qDebug() << "Unhandled property" << prop << value;

                emit propertyChanged(prop, value);
            }
        }

        onSubscribeHandler(values);

        return;
    }
}

void BMBase::handleEventMessage(QJsonObject em)
{
    auto s=em.value("success").toBool();
    if (s==false && em.contains("errorMessage")) {
        auto er=em.value("errorMessage").toString();
        qDebug() << "Error:" << er;
        emit responseError(er);
        return;
    }

    auto a=em.value("action").toString();

    if (a=="propertyValueChanged") {
        auto prop=em.value("property").toString();
        auto value=em.value("value");

        if (onPropertyChange(prop, value)==false) {
            qDebug() << "Unhandled property" << prop << value << value.isObject() << value.isArray() << value.isString() << value.isBool();

            emit propertyChanged(prop, value);
        }

        return;
    }

    if (a=="websocketOpened") {
        qDebug() << "websocketOpened" << m_hostname;
        return;
    }

}

void BMBase::setApiServer(QtOpenApiCommon::QOAIBaseApi *api) {
    auto ops=api->operations();

    for (const auto &op : std::as_const(ops)) {
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
    qDebug() << "Websocket connected!" << m_hostname;
    connect(&m_ws, &QWebSocket::textMessageReceived, this, &BMBase::onWsTextMessageReceived);
    m_ws.sendTextMessage(makeJson("request", "listProperties"));
}

void BMBase::onWsDisconnected()
{
    qDebug() << "Websocket disconnected" << m_hostname;
}

void BMBase::onWsTextMessageReceived(QString message)
{    
    auto j=QJsonDocument::fromJson(message.toUtf8());    

    if (!j.isObject()) {
        qWarning("Not an object ?");
        emit connectionError(255);
        return;
    }

    if (m_debug)
        qDebug().noquote() << "*** WS-MESSAGE:"<< j.toJson();

    auto d=j.object().value("data").toObject();    
    auto t=j.object().value("type").toString();

    if (t=="response") {
        handleResponseMessage(d);
        return;
    } else if (t=="event") {
        handleEventMessage(d);
        return;
    }

    qDebug().noquote() << "Unhandled WS message:" << j;
}

void BMBase::onWsErrorOccurred(QAbstractSocket::SocketError error)
{
    qDebug() << "WSE" << error;

    emit connectionError(error);
}

void BMBase::onSubscribeHandler(QJsonObject jso)
{

}

bool BMBase::onPropertyChange(QString property, QJsonValue value)
{
    return false;
}

void BMBase::onListProperties(QJsonArray properties)
{

}

QString BMBase::hostname() const
{
    return m_hostname;
}

void BMBase::setHostname(const QString &newHostname)
{
    if (m_hostname == newHostname)
        return;
    m_hostname = newHostname;
    emit hostnameChanged();
}

bool BMBase::debug() const
{
    return m_debug;
}

void BMBase::setDebug(bool newDebug)
{
    if (m_debug == newDebug)
        return;
    m_debug = newDebug;
    emit debugChanged();
}
