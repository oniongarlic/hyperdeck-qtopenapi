
#include "hyperdecktransport.h"

HyperdeckTransport::HyperdeckTransport(QObject *parent) : BMHyperdeck::TransportHyperdeckApi{parent}
{

}

bool HyperdeckTransport::onPropertyChange(QString property, QJsonValue value)
{

    if (property=="/transports/0" && value.isObject()) {
        auto m=value.toObject().value("mode").toString();
    }

    if (property=="/transports/0/timecode" && value.isObject()) {
        auto sdisplay=value.toObject().value("display").toString();
        auto stimeline=value.toObject().value("timeline").toString();
        m_display=QTime::fromString(sdisplay, "hh:mm:ss:zz");
        m_timeline=QTime::fromString(stimeline, "hh:mm:ss:zz");

        emit timecodeChanged();

        return true;
    }

    if (property=="/transports/0/stop" && value.isBool()) {
        m_stopped=value.toBool();
    }

    if (property=="/transports/0/play" && value.isBool()) {
        m_playing=value.toBool();
    }

    if (property=="/transports/0/playback" && value.isObject()) {

    }

    if (property=="/transports/0/record" && value.isObject()) {

    }

    if (property=="/transports/0/clipIndex" && value.isObject()) {

    }

    if (property=="/transports/0/inputVideoSource" && value.isObject()) {

    }

    if (property=="/transports/0/inputVideoFormat" && value.isObject()) {

    }

    if (property=="/transports/0/timecode/source" && value.isObject()) {

    }

    return false;
}
