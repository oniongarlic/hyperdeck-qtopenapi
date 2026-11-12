#include "cameravideoapi.h"

CameraVideoApi::CameraVideoApi(QObject *parent)
    : BMCamera::DefaultCameraVideoApi{parent}
{

}

void CameraVideoApi::setIso(uint iso)
{
    BMCamera::_video_iso_put_request req;
    req.setIso(iso);
    videoIsoPut(req);
}

