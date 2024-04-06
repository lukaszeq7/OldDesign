#include "BedModel.h"

BedModel::BedModel(QObject *parent)
        : QAbstractTableModel(parent)
        , _database(new Database(this))
{
    connect(_database, &Database::bedsFetched, this, &BedModel::onBedsFetched);
    initData();
}

BedModel::~BedModel()
{
    qDeleteAll(_beds);
}

int BedModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return _beds.count();
}

int BedModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (_beds.isEmpty())
        return 0;

    return _headerData.count();
}

QVariant BedModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= _beds.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        int row = index.row();
        int column = index.column();

        Bed* bed = _beds.at(row);
        if (!bed)
            return QVariant();

        switch (column)
        {
            case 0:
                return QVariant(bed->id());
            case 1:
                return QVariant(bed->name());
            case 2:
                return QVariant(bed->width());
            case 3:
                return QVariant(bed->length());
            case 4:
                return QVariant(bed->height());
            case 5:
                return QVariant(bed->fabric());
            default:
                return QVariant();
        }
    }

    return QVariant();
}

QVariant BedModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return _headerData[section];

    return QVariant();
}

void BedModel::initData()
{
    _database->connectToDatabase();
    _database->fetchBeds();
    _headerData << "Id" << "Name" << "Width" << "Length" << "Height" << "Fabric";
}

void BedModel::onBedsFetched(QList<Bed*> beds)
{
    _beds = beds;
}

void BedModel::addBed(Bed* bed)
{
    _database->saveBed(bed);
    _beds.append(bed);

    reload();
}

void BedModel::editBed(Bed* bed)
{
    _database->updateBed(bed);

    for(int i = 0; i < _beds.count(); i++)
    {
        if(_beds[i]->id() == bed->id())
        {
            _beds[i] = bed;
            break;
        }
    }

    reload();
}

void BedModel::deleteBed(int bedId)
{
    _database->deleteBed(bedId);

    for(int i = 0; i < _beds.count(); i++)
    {
        if(_beds[i]->id() == bedId)
        {
            _beds.removeAt(i);
            break;
        }
    }

    reload();
}

void BedModel::reload()
{
    QModelIndex topLeft     = index(0, 0);
    QModelIndex bottomRight = index( rowCount() - 1, columnCount() - 1 );

    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
}

Bed* BedModel::getBed(int bedId)
{
    for(int i = 0; i < _beds.count(); i++)
    {
        if(_beds[i]->id() == bedId)
        {
            return _beds[i];
        }
    }

    return nullptr;
}

int BedModel::lastBedId()
{
    if(_beds.isEmpty())
        return -1;
    return _beds.last()->id();
}

void BedModel::displayBeds()
{
    for(Bed* bed : _beds)
    {
        qDebug() << bed->id()
                 << bed->name()
                 << "Width:" << bed->width()
                 << "Length:" << bed->length()
                 << "Height:" << bed->height()
                 << "Fabric" << bed->fabric();
    }
}