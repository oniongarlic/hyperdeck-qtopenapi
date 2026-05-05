#ifndef BMBASE_H
#define BMBASE_H

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

public:
    explicit BMBase(QObject *parent = nullptr);
    ~BMBase();

    Q_INVOKABLE void setServer(QString hostname, QString protocol);
    Q_INVOKABLE void setApiServer(QtOpenApiCommon::QOAIBaseApi *api);

    Q_INVOKABLE void open();
    Q_INVOKABLE void close();

    QString hostname() const;
    void setHostname(const QString &newHostname);

signals:
    void connectionError();
    void propertyChanged(QString property, QJsonValue value);

    void hostnameChanged();

protected slots:
    void onWsConnected();
    void onWsDisconnected();
    void onWsTextMessageReceived(QString message);
    void onWsErrorOccurred(QAbstractSocket::SocketError error);

protected:
    QString m_hostname;
    QString m_protocol="http";
    QWebSocket m_ws;

    QList<QtOpenApiCommon::QOAIBaseApi *>m_oac;

    virtual void onSubscribeHandler(QJsonObject jso);
    virtual bool onPropertyChange(QString property, QJsonValue value);
    virtual void onListProperties(QJsonArray properties);
    QQmlListProperty<QObject> endpoints();
};

#endif // BMBASE_H
