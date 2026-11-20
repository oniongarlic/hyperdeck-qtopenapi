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

void CameraLensApi::setIris(double focal)
{
    BMCamera::_lens_iris_put_request i;
    i.setNormalised(focal);

    lensIrisPut(i);
}

void CameraLensApi::setFocus(double focus)
{
    BMCamera::_lens_focus_get_200_response f;

    f.setNormalised(std::clamp(focus, 0.0, 1.0));

    lensFocusPut(f);
}

bool CameraLensApi::onPropertyChange(QString property, QJsonValue value)
{
    qDebug() << "CameraLensApi onPropertyChange" << property << value;

    if (!value.isObject()) {
        qWarning("Not an object ?");
        return false;
    }

    auto o=value.toObject();

    if (property=="/lens/focus") {
        m_focus=o.value("normalised").toDouble();
        emit focusChanged();
        return true;
    }

    if (property=="/lens/zoom") {
        m_zoom=o.value("normalised").toDouble();
        m_focal=o.value("focalLength").toInt();
        emit zoomChanged();
        return true;
    }

    if (property=="/lens/iris") {
        m_iris=o.value("normalised").toDouble();
        m_aperture=o.value("apertureStop").toDouble();
        emit irisChanged();
        return true;
    }

    return false;
}

