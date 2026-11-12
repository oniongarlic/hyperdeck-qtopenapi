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

bool HyperdeckApi::onPropertyChange(QString property, QJsonValue value)
{
    // "/transports/0/timecode" QJsonValue(object, QJsonObject({"display":"13:20:58:16","timeline":"00:13:44:06"}))
    if (property=="/transports/0/timecode" && value.isObject()) {
        auto sdisplay=value.toObject().value("display").toString();
        auto stimeline=value.toObject().value("timeline").toString();
        auto display=QTime::fromString(sdisplay, "hh:mm:ss:zz");
        auto timeline=QTime::fromString(stimeline, "hh:mm:ss:zz");
        qDebug() << "CameraAPI: " << value.toObject() << display << timeline << sdisplay << stimeline;
        return true;
    }

    qDebug("*** HyperdeckAPI onPropertyChange not handled");

    return false;
}

