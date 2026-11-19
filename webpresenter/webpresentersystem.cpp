
#include "webpresentersystem.h"

WebpresenterSystem::WebpresenterSystem(QObject *parent) : BMWebpresenter::DefaultWebpresenterSystemApi{parent}
{

}

bool WebpresenterSystem::onPropertyChange(QString property, QJsonValue value)
{

    if (property=="/system/product") {
        auto o=value.toObject();
        m_device=o.value("deviceName").toString();
        m_product=o.value("productName").toString();
        m_version=o.value("softwareVersion").toString();

        emit productInformation();

        return true;
    }

    return false;
}
