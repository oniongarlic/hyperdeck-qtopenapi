#include "hyperdeckapi.h"

#include <QJsonDocument>
#include <QJsonObject>

HyperdeckApi::HyperdeckApi(QObject *parent)
    : BMBase{parent}
{
    m_oac.append(&system);
    m_oac.append(&transport);
    m_oac.append(&timeline);
    m_oac.append(&media);
    m_oac.append(&audio);
    m_oac.append(&clips);
    m_oac.append(&event);
    m_oac.append(&externalmedia);
    m_oac.append(&input);
    m_oac.append(&monitoring);
    m_oac.append(&nas);
    m_oac.append(&playrange);
    m_oac.append(&recordcache);
    m_oac.append(&spill);
}

HyperdeckApi::~HyperdeckApi()
{

}

void HyperdeckApi::onSubscribeHandler(QJsonObject jso)
{
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

