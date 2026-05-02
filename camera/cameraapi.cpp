#include "cameraapi.h"

CameraApi::CameraApi(QObject *parent)
    : BMBase{parent}
{
    m_oac.append(&system);
    m_oac.append(&event);

    m_oac.append(&transport);
    m_oac.append(&video);
}
