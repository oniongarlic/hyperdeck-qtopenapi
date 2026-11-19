#pragma once

#include <QObject>
#include <QQmlEngine>

#include "mediahyperdeckapi.h"
#include "mediahyperdeckapi.h"

class HyperdeckMedia : public BMHyperdeck::MediaHyperdeckApi
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit HyperdeckMedia(QObject *parent = nullptr);

};

