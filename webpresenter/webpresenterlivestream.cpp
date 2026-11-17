
#include "webpresenterlivestream.h"

WebpresenterLiveStream::WebpresenterLiveStream(QObject *parent) : BMWebpresenter::LivestreamWebpresenterLivestreamApi{parent}
{

}

void WebpresenterLiveStream::start()
{
    livestreams0StartPut();
}

void WebpresenterLiveStream::stop()
{
    livestreams0StopPut();
}
