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
public:
    explicit BMBase(QObject *parent = nullptr);
    ~BMBase();

    Q_INVOKABLE void setServer(QString hostname, QString protocol);
    Q_INVOKABLE void setApiServer(QtOpenApiCommon::QOAIBaseApi *api);

    Q_INVOKABLE void open();
    Q_INVOKABLE void close();

signals:
    void connectionError();

protected slots:
    void onWsConnected();
    void onWsDisconnected();
    void onWsTextMessageReceived(QString message);
    void onWsErrorOccurred(QAbstractSocket::SocketError error);

protected:
    QString m_hostname;
    QString m_protocol;
    QWebSocket m_ws;

    QList<QtOpenApiCommon::QOAIBaseApi *>m_oac;

    virtual void onSubscribeHandler(QJsonObject jso);
};

#endif // BMBASE_H
