
#include "hyperdecktransport.h"

HyperdeckTransport::HyperdeckTransport(QObject *parent) : BMHyperdeck::TransportHyperdeckApi{parent}
{

}

bool HyperdeckTransport::onPropertyChange(QString property, QJsonValue value)
{
    auto o=value.toObject();

    if (property=="/transports/0") {
        auto m=o.value("mode").toString();

        // InputPreview, InputRecord
        // emit ...

        return true;
    }

    if (property=="/transports/0/timecode" && value.isObject()) {
        auto sdisplay=o.value("display").toString();
        auto stimeline=o.value("timeline").toString();
        m_display=QTime::fromString(sdisplay, "hh:mm:ss:zz");
        m_timeline=QTime::fromString(stimeline, "hh:mm:ss:zz");

        emit timecodeChanged();

        return true;
    }

    if (property=="/transports/0/stop" && value.isBool()) {
        m_stopped=value.toBool();
        emit stoppedChanged();
        return true;
    }

    if (property=="/transports/0/play" && value.isBool()) {
        m_playing=value.toBool();
        emit playingChanged();
        return true;
    }

    if (property=="/transports/0/playback") {
        m_loop=o.value("loop").toBool();
        m_single=o.value("singleClip").toBool();
        m_speed=o.value("speed").toDouble();
        m_position=o.value("position").toInteger();
        auto t=o.value("type").toString();

        // emit ...

        return true;
    }

    if (property=="/transports/0/record") {
        m_recording=o.value("recording").toBool();
        emit recordingChanged();
        return true;
    }

    if (property=="/transports/0/clipIndex") {
        m_clipindex=o.value("clipIndex").toInt();

        // emit ...

        return true;
    }

    if (property=="/transports/0/inputVideoSource") {

    }

    if (property=="/transports/0/inputVideoFormat") {

    }

    if (property=="/transports/0/timecode/source") {

    }

    return false;
}

void HyperdeckTransport::play()
{
    transports0PlayPost();
}

void HyperdeckTransport::record()
{
    transports0RecordPost();
}

void HyperdeckTransport::stop()
{
    transports0StopPost();
}

bool HyperdeckTransport::playing() const
{
    return m_playing;
}

bool HyperdeckTransport::recording() const
{
    return m_recording;
}

bool HyperdeckTransport::stopped() const
{
    return m_stopped;
}
