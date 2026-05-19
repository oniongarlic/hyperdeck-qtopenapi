#ifndef WEBPRESENTERAPI_H
#define WEBPRESENTERAPI_H

#include <QObject>
#include <QQmlEngine>
#include <QtWebSockets/QtWebSockets>
#include <QDebug>

#include "../bmbase.h"

class WebpresenterApi : public BMBase
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit WebpresenterApi(QObject *parent = nullptr);
    ~WebpresenterApi();    

protected:
    void onSubscribeHandler(QJsonObject jso);

private:
    QString m_device;
    QString m_product;
    QString m_version;
};

#endif