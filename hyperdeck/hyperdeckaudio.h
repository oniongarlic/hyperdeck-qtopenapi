#pragma once

#include <QObject>
#include <QQmlEngine>

#include "audiohyperdeckapi.h"

class HyperdeckAudio : public BMHyperdeck::AudioHyperdeckApi
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit HyperdeckAudio(QObject *parent = nullptr);

};

