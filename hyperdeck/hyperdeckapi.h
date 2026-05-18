#ifndef HYPERDECKAPI_H
#define HYPERDECKAPI_H

#include <QObject>
#include <QQmlEngine>
#include <QtWebSockets/QtWebSockets>
#include <QDebug>

#include "../bmbase.h"

#include "clipmodel.h"

class HyperdeckApi : public BMBase
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit HyperdeckApi(QObject *parent = nullptr);
    ~HyperdeckApi();

    Q_INVOKABLE ClipModel* getClipsModel() { return &m_clip_model; }

protected:    
    void onSubscribeHandler(QJsonObject jso);

private:
    QString m_device;
    QString m_product;
    QString m_version;

    ClipModel m_clip_model;
};

#endif // HYPERDECKAPI_H
