#ifndef CLIPMODEL_H
#define CLIPMODEL_H

#include <QObject>

#pragma once

#include <QAbstractListModel>
#include <QVariantList>

class ClipModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ClipModel(QObject *parent = nullptr);

    enum Roles {
        ClipInRole = Qt::UserRole + 1,
        ClipUniqueIdRole,
        DurationTimecodeRole,
        FrameCountRole,
        InTimecodeRole,
        TimelineInRole,
        TimelineInTimecodeRole
    };
    Q_ENUM(Roles)

    // Core overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Data setup (read-only externally)
    void setItems(const QVariantList &items);

private:
    QVariantList m_items;
};

#endif // CLIPMODEL_H
