#ifndef OLDDESIGN_BEDMODEL_H
#define OLDDESIGN_BEDMODEL_H

#include <QAbstractTableModel>
#include <QVector>

class BedModel : public QAbstractTableModel
{
Q_OBJECT

public:
    explicit BedModel(QObject *parent = nullptr);
    virtual ~BedModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QVector<QVector<QVariant>> _data;
};

#endif // OLDDESIGN_BEDMODEL_H
