#include "cameralensapi.h"

CameraLensApi::CameraLensApi(QObject *parent)
    : BMCamera::DefaultCameraLensApi{parent}
{

}

void CameraLensApi::setZoom(double zoom)
{
    BMCamera::_lens_zoom_get_200_response z;

    z.setNormalised(std::clamp(zoom, 0.0, 1.0));

    lensZoomPut(z);
}

