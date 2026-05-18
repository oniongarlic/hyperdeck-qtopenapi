#include "clipmodel.h"

ClipModel::ClipModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ClipModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_items.size();
}

QVariant ClipModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_items.size())
        return {};

    const QVariantMap item = m_items.at(index.row()).toMap();

    switch (role) {
    case ClipInRole:
        return item.value("clipIn");
    case ClipUniqueIdRole:
        return item.value("clipUniqueId");
    case DurationTimecodeRole:
        return item.value("durationTimecode");
    case FrameCountRole:
        return item.value("frameCount");
    case InTimecodeRole:
        return item.value("inTimecode");
    case TimelineInRole:
        return item.value("timelineIn");
    case TimelineInTimecodeRole:
        return item.value("timelineInTimecode");
    default:
        return {};
    }
}

QHash<int, QByteArray> ClipModel::roleNames() const
{
    return {
        { ClipInRole, "clipIn" },
        { ClipUniqueIdRole, "clipUniqueId" },
        { DurationTimecodeRole, "durationTimecode" },
        { FrameCountRole, "frameCount" },
        { InTimecodeRole, "inTimecode" },
        { TimelineInRole, "timelineIn" },
        { TimelineInTimecodeRole, "timelineInTimecode" }
    };
}

void ClipModel::setItems(const QVariantList &items)
{
    beginResetModel();
    m_items = items;
    endResetModel();
}