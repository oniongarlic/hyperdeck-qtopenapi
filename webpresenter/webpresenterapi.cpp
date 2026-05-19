#include "webpresenterapi.h"

#include <QJsonDocument>
#include <QJsonObject>

WebpresenterApi::WebpresenterApi(QObject *parent)
    : BMBase{parent}
{

}

WebpresenterApi::~WebpresenterApi()
{

}

void WebpresenterApi::onSubscribeHandler(QJsonObject jso)
{
    if (jso.contains("/system/product")) {
        auto o=jso.value("/system/product").toObject();
        m_device=o.value("deviceName").toString();
        m_product=o.value("productName").toString();
        m_version=o.value("softwareVersion").toString();
    }

    if (jso.contains("/system/supportedVideoFormats")) {
        QVariantList tmp=jso.value("/system/supportedVideoFormats").toObject().value("videoFormats").toArray().toVariantList();
        qDebug() << "Video formats" << tmp;
    }
}

