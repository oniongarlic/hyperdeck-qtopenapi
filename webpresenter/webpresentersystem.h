#pragma once

#include <QObject>
#include <QQmlEngine>

#include "defaultwebpresentersystemapi.h"

class WebpresenterSystem : public BMWebpresenter::DefaultWebpresenterSystemApi
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit WebpresenterSystem(QObject *parent = nullptr);

};

