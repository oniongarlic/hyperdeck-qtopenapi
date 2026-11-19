
#include "hyperdecktransport.h"

HyperdeckTransport::HyperdeckTransport(QObject *parent) : BMHyperdeck::TransportHyperdeckApi{parent}
{

}

bool HyperdeckTransport::onPropertyChange(QString property, QJsonValue value)
{
    if (property=="/transports/0/timecode" && value.isObject()) {
        auto sdisplay=value.toObject().value("display").toString();
        auto stimeline=value.toObject().value("timeline").toString();
        m_display=QTime::fromString(sdisplay, "hh:mm:ss:zz");
        m_timeline=QTime::fromString(stimeline, "hh:mm:ss:zz");

        emit timecodeChanged();

        return true;
    }

    return false;
}
