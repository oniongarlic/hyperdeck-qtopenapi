#pragma once

#include <QObject>
#include <QQmlEngine>

#include "livestreamwebpresenterlivestreamapi.h"

class WebpresenterLiveStream : public BMWebpresenter::LivestreamWebpresenterLivestreamApi
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit WebpresenterLiveStream(QObject *parent = nullptr);

};

