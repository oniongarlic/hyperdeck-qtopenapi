#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QtWebSockets/QtWebSockets>
#include <QDebug>

#include <QtOpenApiCommon/QOAIBaseApi>

class BMBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QObject> endpoints READ endpoints)
    Q_CLASSINFO("DefaultProperty", "endpoints")

    Q_PROPERTY(QString hostname READ hostname WRITE setHostname NOTIFY hostnameChanged FINAL)
    Q_PROPERTY(bool debug READ debug WRITE setDebug NOTIFY debugChanged FINAL)

public:
    explicit BMBase(QObject *parent = nullptr);
    ~BMBase();

    void setApiServer(QtOpenApiCommon::QOAIBaseApi *api);

    Q_INVOKABLE void open();
    Q_INVOKABLE void close();

    QString hostname() const;
    void setHostname(const QString &newHostname);

    bool debug() const;
    void setDebug(bool newDebug);

signals:
    void connectionError(int error);
    void propertyChanged(QString property, QJsonValue value);
    void hostnameChanged();
    void responseError(QString message);

    void debugChanged();

protected slots:
    void onWsConnected();
    void onWsDisconnected();
    void onWsTextMessageReceived(QString message);
    void onWsErrorOccurred(QAbstractSocket::SocketError error);

protected:
    QString m_hostname;
    QString m_protocol="http";
    QWebSocket m_ws;
    bool m_debug=false;

    virtual void onSubscribeHandler(QJsonObject jso);
    virtual bool onPropertyChange(QString property, QJsonValue value);
    virtual void onListProperties(QJsonArray properties);

    QQmlListProperty<QObject> endpoints();    

    void handleResponseMessage(QJsonObject rm);
    void handleEventMessage(QJsonObject em);
};

