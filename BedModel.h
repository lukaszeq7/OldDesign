#ifndef OLDDESIGN_BEDMODEL_H
#define OLDDESIGN_BEDMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QItemSelection>
#include "Bed.h"
#include "Database.h"

class BedModel : public QAbstractTableModel
{
Q_OBJECT

public:
    explicit BedModel(QObject *parent = nullptr);
    ~BedModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addBed(Bed *bed);
    void editBed(Bed* bed);
    void deleteBed(int bedId);
    Bed* getBed(int bedId);

private slots:
    void onBedsFetched(QList<Bed*> beds);

private:
    Database* _database;
    QList<Bed*> _beds;
    QStringList _headerData;

    void initData();
    void reload();
    void displayBeds();
};

#endif // OLDDESIGN_BEDMODEL_H
