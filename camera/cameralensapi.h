#ifndef DEFAULTCAMERALENSAPI_H
#define DEFAULTCAMERALENSAPI_H

#include <QObject>
#include <QQmlEngine>

#include "client/defaultcameralensapi.h"

class CameraLensApi : public BMCamera::DefaultCameraLensApi

{
    Q_OBJECT
    QML_ELEMENT
public:
    CameraLensApi(QObject *parent);
};

#endif // DEFAULTCAMERALENSAPI_H
