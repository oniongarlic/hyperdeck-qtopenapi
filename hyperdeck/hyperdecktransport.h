#pragma once

#include <QObject>
#include <QQmlEngine>

#include "transporthyperdeckapi.h"

#include "../bminterface.h"

class HyperdeckTransport : public BMHyperdeck::TransportHyperdeckApi, public BMInterface
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged FINAL)
    Q_PROPERTY(bool recording READ recording NOTIFY recordingChanged FINAL)
    Q_PROPERTY(bool stopped READ stopped NOTIFY stoppedChanged FINAL)

public:
    explicit HyperdeckTransport(QObject *parent = nullptr);

    bool onPropertyChange(QString property, QJsonValue value);

    Q_INVOKABLE void play();
    Q_INVOKABLE void record();
    Q_INVOKABLE void stop();

    Q_INVOKABLE QTime getTimelineTime() const { return m_timeline; }
    Q_INVOKABLE QTime getDisplayTime() const { return m_display; }

    bool playing() const;

    bool recording() const;

    bool stopped() const;

signals:
    void timecodeChanged();

    void playingChanged();

    void recordingChanged();

    void stoppedChanged();

protected:
    QTime m_display;
    QTime m_timeline;

    bool m_playing=false;
    bool m_stopped=true;
    bool m_recording=false;

    bool m_loop=false;
    bool m_single=false;
    double m_speed=1;
    qint64 m_position=0;

    int m_clipindex=0;

};

