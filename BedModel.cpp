#include "BedModel.h"

BedModel::BedModel(QObject *parent)
        : QAbstractTableModel(parent)
{
    _data.append({"lolek"});
}

BedModel::~BedModel()
{
}

int BedModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return _data.size();
}

int BedModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    if (_data.isEmpty())
    {
        return 0;
    }

    return _data[0].size();
}

QVariant BedModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return _data[index.row()][index.column()];
    }

    return QVariant();
}

QVariant BedModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        return QString("Column %1").arg(section);
    }
    else
    {
        return QString("Row %1").arg(section);
    }
}