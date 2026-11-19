
#include "webpresenterlivestream.h"

WebpresenterLiveStream::WebpresenterLiveStream(QObject *parent) : BMWebpresenter::LivestreamWebpresenterLivestreamApi{parent}
{

}

bool WebpresenterLiveStream::onPropertyChange(QString property, QJsonValue value)
{
    if (property=="/livestreams/platforms") {
        m_platforms=value.toArray().toVariantList();
        emit platforms();
        return true;
    }

    if (property=="/livestreams/0/activePlatform") {
        qDebug() << value;
    }

    if (property=="/livestreams/0") {

        m_bitrate=value.toObject().value("bitrate").toInteger(0);
        m_cache=value.toObject().value("cache").toInteger(0);

        emit bitrateChanged();

        m_videoformat=value.toObject().value("effectiveVideoFormat").toString();
        m_status=value.toObject().value("status").toString();

        emit streamInfo();

        return true;
    }

    return false;
}

void WebpresenterLiveStream::start()
{
    livestreams0StartPut();
}

void WebpresenterLiveStream::stop()
{
    livestreams0StopPut();
}
