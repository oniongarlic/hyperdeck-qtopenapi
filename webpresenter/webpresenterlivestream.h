#pragma once

#include <QObject>
#include <QQmlEngine>

#include "livestreamwebpresenterlivestreamapi.h"

#include "../bminterface.h"

class WebpresenterLiveStream : public BMWebpresenter::LivestreamWebpresenterLivestreamApi, public BMInterface
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(uint32_t bitrate READ getBitrate NOTIFY bitrateChanged FINAL)
    Q_PROPERTY(uint32_t cache READ getCache NOTIFY cacheChanged FINAL)

public:
    explicit WebpresenterLiveStream(QObject *parent = nullptr);

    bool onPropertyChange(QString property, QJsonValue value);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    Q_INVOKABLE uint32_t getBitrate() const { return m_bitrate; }
    Q_INVOKABLE uint32_t getCache() const { return m_cache; }

    Q_INVOKABLE QString getStatus() const { return m_status; }
    Q_INVOKABLE QString getFormat() const { return m_videoformat; }

    Q_INVOKABLE QVariantList getPlatsforms() const { return m_platforms; }

signals:
    void streamInfo();
    void bitrateChanged();
    void cacheChanged();
    void platforms();

protected:
    bool m_live=false;
    uint32_t m_bitrate=0;
    uint32_t m_cache=0;
    QString m_videoformat;
    QVariantList m_platforms;
    QString m_status;
};

