#pragma once

#include <QObject>
#include <QQmlEngine>

#include "defaultwebpresentersystemapi.h"

#include "../bminterface.h"

class WebpresenterSystem : public BMWebpresenter::DefaultWebpresenterSystemApi, public BMInterface
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit WebpresenterSystem(QObject *parent = nullptr);

    bool onPropertyChange(QString property, QJsonValue value);

    Q_INVOKABLE QString getVersion() const { return m_version; }
    Q_INVOKABLE QString getDevice() const { return m_device; }
    Q_INVOKABLE QString getProduct() const { return m_product; }

signals:
    void productInformation();

private:
    QString m_device;
    QString m_product;
    QString m_version;

};

