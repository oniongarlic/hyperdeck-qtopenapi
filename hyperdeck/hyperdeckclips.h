#pragma once

#include <QObject>
#include <QQmlEngine>

#include "clipshyperdeckapi.h"

class HyperdeckClips : public BMHyperdeck::ClipsHyperdeckApi
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit HyperdeckClips(QObject *parent = nullptr);

};

