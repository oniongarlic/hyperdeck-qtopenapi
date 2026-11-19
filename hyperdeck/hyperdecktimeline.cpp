
#include "hyperdecktimeline.h"

HyperdeckTimeline::HyperdeckTimeline(QObject *parent) : BMHyperdeck::TimelineHyperdeckApi{parent}
{

}

bool HyperdeckTimeline::onPropertyChange(QString property, QJsonValue value)
{
    if (property=="/timelines/0") {
        QVariantList tmp=value.toObject().value("clips").toArray().toVariantList();
        m_clip_model.setItems(tmp);

        emit timelineUpdated();

        return true;
    }

    if (property=="/timelines/0/videoFormat") {
        m_format=value.toObject().value("videoFormat").toObject().toVariantMap();

        emit formatChanged();

        return true;
    }

    return false;
}
