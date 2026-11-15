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

        emit productInformation();

        return;
    }

    if (jso.contains("/system/supportedVideoFormats")) {
        QVariantList tmp=jso.value("/system/supportedVideoFormats").toObject().value("videoFormats").toArray().toVariantList();
        qDebug() << "Video formats" << tmp;
    }
}

bool WebpresenterApi::onPropertyChange(QString property, QJsonValue value)
{
    if (property=="/livestreams/0") {

        m_bitrate=value.toObject().value("bitrate").toInteger(0);
        m_cache=value.toObject().value("cache").toInteger(0);

        emit bitrateChanged();

        m_videoformat=value.toObject().value("effectiveVideoFormat").toString();
        m_status=value.toObject().value("status").toString();

        emit streamInfo();

        return true;
    }

    if (property=="/livestreams/0/activePlatform") {
        qDebug() << value;
    }

    qDebug("*** WebpresenterAPI onPropertyChange not handled");

    return false;
}

