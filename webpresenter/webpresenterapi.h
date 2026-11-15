#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QtWebSockets/QtWebSockets>
#include <QDebug>

#include "../bmbase.h"

class WebpresenterApi : public BMBase
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(uint64_t bitrate READ getBitrate NOTIFY bitrateChanged FINAL)

public:
    explicit WebpresenterApi(QObject *parent = nullptr);
    ~WebpresenterApi();

    Q_INVOKABLE QString getVersion() const { return m_version; }
    Q_INVOKABLE QString getDevice() const { return m_device; }
    Q_INVOKABLE QString getProduct() const { return m_product; }

    Q_INVOKABLE uint32_t getBitrate() const { return m_bitrate; }
    Q_INVOKABLE uint32_t getCache() const { return m_cache; }

    Q_INVOKABLE QString getStatus() const { return m_status; }
    Q_INVOKABLE QString getFormat() const { return m_videoformat; }

signals:
    void productInformation();
    void streamInfo();
    void bitrateChanged();

protected:
    void onSubscribeHandler(QJsonObject jso);
    bool onPropertyChange(QString property, QJsonValue value);

private:
    QString m_device;
    QString m_product;
    QString m_version;

    uint32_t m_bitrate;
    uint32_t m_cache;
    QString m_videoformat;
    QString m_status;
};
