#include "hyperdeckapi.h"

#include <QJsonDocument>
#include <QJsonObject>

HyperdeckApi::HyperdeckApi(QObject *parent)
    : BMBase{parent}
{

}

HyperdeckApi::~HyperdeckApi()
{

}

void HyperdeckApi::onSubscribeHandler(QJsonObject jso)
{
    qDebug() << "Hyperdeck: onSubscribeHandler" << jso;

    if (jso.contains("/system/product")) {
        auto o=jso.value("/system/product").toObject();
        m_device=o.value("deviceName").toString();
        m_product=o.value("productName").toString();
        m_version=o.value("softwareVersion").toString();
    }

    if (jso.contains("/timelines/0")) {
        QVariantList tmp=jso.value("/timelines/0").toObject().value("clips").toArray().toVariantList();
        m_clip_model.setItems(tmp);
    }

    if (jso.contains("/system/supportedVideoFormats")) {
        QVariantList tmp=jso.value("/system/supportedVideoFormats").toObject().value("videoFormats").toArray().toVariantList();
        qDebug() << "Video formats" << tmp;
    }
}

