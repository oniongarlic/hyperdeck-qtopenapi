#pragma once

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

};
