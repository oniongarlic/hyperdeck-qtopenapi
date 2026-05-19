#pragma once

#include <QObject>
#include <QQmlEngine>

#include "defaultwebpresentereventapi.h"

class WebpresenterEvent : public BMWebpresenter::DefaultWebpresenterEventApi
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit WebpresenterEvent(QObject *parent = nullptr);

};

