#pragma once

#include <QObject>
#include <QQmlEngine>

#include "audiohyperdeckapi.h"
#include "clipshyperdeckapi.h"
#include "eventhyperdeckapi.h"
#include "externalmediahyperdeckapi.h"
#include "inputhyperdeckapi.h"
#include "mediahyperdeckapi.h"
#include "monitoringhyperdeckapi.h"
#include "systemhyperdeckapi.h"
#include "mediahyperdeckapi.h"
#include "nashyperdeckapi.h"
#include "playrangehyperdeckapi.h"
#include "recordcachehyperdeckapi.h"
#include "spillhyperdeckapi.h"
#include "timelinehyperdeckapi.h"
#include "transporthyperdeckapi.h"

class HyperdeckEvent : public BMHyperdeck::EventHyperdeckApi
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit HyperdeckEvent(QObject *parent = nullptr);

};

